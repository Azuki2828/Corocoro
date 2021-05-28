#include "stdafx.h"
#include "Key.h"
#include "Player.h"
#include "Background.h"
#include "ResultScene.h"
#include "GameLevel2D.h"
#include "MainCamera.h"
#include "Game.h"

bool Key::Start() {

	m_player = FindGO<Player>("player");

	
	//鍵があったら座標を登録。
	if (m_skinModelRender_Key != nullptr) {

		m_skinModelRender_Key->SetPosition(m_keyPos);
		m_skinModelRender_Key->SetScale(m_keyScale);
		m_skinModelRender_Key->UpdateWorldMatrix();
		//m_physicsStaticObject.CreateFromModel(
		//	*m_skinModelRender_Key->GetModel(),
		//	m_skinModelRender_Key->GetModel()->GetWorldMatrix()
		//);
	}

	//ドアがあったら座標を登録+当たり判定を付ける。
	if (m_skinModelRender_Door != nullptr) {
		m_skinModelRender_Door->SetPosition(m_doorPos);
		m_skinModelRender_Door->SetScale(m_Doorscale);
		m_skinModelRender_Door->UpdateWorldMatrix();
		m_physicsStaticObject.CreateFromModel(
			*m_skinModelRender_Door->GetModel(),
			m_skinModelRender_Door->GetModel()->GetWorldMatrix()
		);
	}


	return true;
}

Key::~Key() {
	DeleteGO(m_skinModelRender_Key);
	DeleteGO(m_skinModelRender_Door);
}

void Key::InitKey(const char* name) {

	char filePathtkm[256];

	sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
	m_skinModelRender_Key = NewGO<SkinModelRender>(0);
	m_skinModelRender_Key->SetFileNametkm(filePathtkm);
	m_skinModelRender_Key->SetShadowReceiverFlag(true);
	m_skinModelRender_Key->SetZprepassFlag(true);
	m_skinModelRender_Key->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_ligKeyData.m_directionLigData[0].Dir.Set(1, -1, 1);
	m_ligKeyData.m_directionLigData[0].Dir.Normalize();
	m_ligKeyData.m_directionLigData[0].Col.Set(20.0f, 20.0f, 0.0f, 1.0f);

	m_ligKeyData.m_directionLigData[1].Dir.Set(1, 1, 1);
	m_ligKeyData.m_directionLigData[1].Dir.Normalize();
	m_ligKeyData.m_directionLigData[1].Col.Set(10.0f, 10.0f, 0.0f, 1.0f);

	m_ligKeyData.metaric = 1.0f;
	m_ligKeyData.smooth = 0.6f;
	m_ligKeyData.ambient.Set(0.2f, 0.2f, 0.2f);
	m_ligKeyData.edge = Edge_1;
	m_ligKeyData.powValue = 0.7f;
	m_skinModelRender_Key->SetUserLigData(&m_ligKeyData);
	m_skinModelRender_Key->Init(true, false);

	Vector3 ghostPos = m_keyPos;
	ghostPos.x += 300.0f;
	ghostPos.y += 300.0f;
	ghostPos.z -= 300.0f;
	m_ghostBox.CreateBox(
		ghostPos,	//第一引数は座標。
		Quaternion::Identity,		//第二引数は回転クォータニオン。
		{ 100.0f, 200.0f, 100.0f }	//第三引数はボックスのサイズ。
	);
}

void Key::InitDoor(const char* name) {

	char filePathtkm[256];

	sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
	m_skinModelRender_Door = NewGO<SkinModelRender>(0);
	m_skinModelRender_Door->SetFileNametkm(filePathtkm);
	m_skinModelRender_Door->SetShadowReceiverFlag(true);
	//m_skinModelRender_Door->SetZprepassFlag(true);
	m_ligDoorData.m_directionLigData[0].Dir.Set(-1, -1, -1);
	m_ligDoorData.m_directionLigData[0].Dir.Normalize();
	m_ligDoorData.m_directionLigData[0].Col.Set(10.0f, 10.0f, 10.0f, 1.0f);

	m_ligDoorData.ambient.Set(0.8f, 0.8f, 0.8f);
	m_ligDoorData.metaric = 1.0f;
	m_ligDoorData.smooth = 0.35f;
	//m_ligDoorData.edge = Edge_1;
	//m_ligDoorData.powValue = 10.0f;
	m_skinModelRender_Door->SetUserLigData(&m_ligDoorData);
	//m_skinModelRender->SetExpandShaderResourceView_2(&RenderTarget::GetZPrepassRenderTarget()->GetRenderTargetTexture());
	m_skinModelRender_Door->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

	auto mainCamera = FindGO<MainCamera>("maincamera");
	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, -2.0f);
		m_rotZ.Apply(m_ligKeyData.m_directionLigData[0].Dir);
		m_rotZ.Apply(m_ligDoorData.m_directionLigData[0].Dir);
	});

	m_skinModelRender_Door->SetUserLigData(&m_ligDoorData);
	m_skinModelRender_Door->Init(true, false);
}

void Key::Update() {

	static float keyTime = 0.0f;

	if (m_skinModelRender_Key != nullptr) {
		
		keyTime += GameTime::GameTimeFunc().GetFrameDeltaTime();
		static Quaternion rot;
		rot.SetRotationDeg(Vector3::AxisY, 180.0f * keyTime);
		m_skinModelRender_Key->SetRotation(rot);
		if (keyTime >= 4.0f) {
			keyTime = 0.0f;
		}
	}

	////3m以内なら鍵取得。
	//Vector3 keyLength;
	//
	//keyLength = m_player->GetPosition() - m_keyPos;
	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

		if (m_ghostBox.IsSelf(contactObject) == true && !m_player->GetKeyFlg()) {

			//鍵を消去して取得効果音を再生。
			DeleteGO(m_skinModelRender_Key);

			//MainCameraクラスのフラグ。ステージの回転をカメラと重力を回転させることで実装する。
			//クラスにアクセスし、情報をもらう。
			maincamera = FindGO<MainCamera>("maincamera");
			//MainCameraクラスのRotFlg変数をtrueに。
			maincamera->RotFlg = true;


			if (KeyGetSoundFlag == true) {

				//通常BGMを削除。
				Background* background = FindGO<Background>("background");
				SoundManager::GetInstance()->Release(BGM_Game);

				//エフェクト再生
				Effect* ChangeState = nullptr;
				ChangeState = NewGO<Effect>(0);
				ChangeState->Init(u"Assets/effect/KeyGet.efk");
				ChangeState->SetScale({ 200.0f,200.0f,200.0f });
				Vector3 effPos = m_keyPos;
				effPos.y += 150.0f;
				ChangeState->SetPosition(effPos);
				ChangeState->Play();


				//GameScreen_NoGetKey.casl��폜���AGameScreen_YesGetKey.casl��ĂԂ��ƂŌ��擾��UI��쐬����B

				//GameLevel2DクラスのNoGetKeyFlagをfalseに変更。
				//※余裕があったら、NoGetKeyFlagをprivateにして関数で変更してください。
				GameLevel2D* gamescreenlevel2d = FindGO<GameLevel2D>("gamescreenlevel2d");
				gamescreenlevel2d->NoGetKeyFlag = false;
				////�O�̌���Q�b�g���Ă��Ȃ��Ƃ���UI��폜�B
				//DeleteGO(gamescreenlevel2d->m_sprite);

				//���擾���̌�ʉ��Đ��B

				SoundManager::GetInstance()->Play(SE_KeyGet);

				//falseにして抜ける。
				KeyGetSoundFlag = false;
			}

			//鍵取得フラグをtrueに。
			m_player->SetKeyFlg(true);

		}
		});
	//if (keyLength.Length() <= 100.0f && !m_player->GetKeyFlg()) {

	//	//鍵を消去して取得効果音を再生。
	//	DeleteGO(m_skinModelRender_Key);

	//	//MainCameraクラスのフラグ。ステージの回転をカメラと重力を回転させることで実装する。
	//	//クラスにアクセスし、情報をもらう。
	//	maincamera = FindGO<MainCamera>("maincamera");
	//	//MainCameraクラスのRotFlg変数をtrueに。
	//	maincamera->RotFlg = true;


	//	if (KeyGetSoundFlag == true) {

	//		//通常BGMを削除。
	//		Background* background = FindGO<Background>("background");
	//		SoundManager::GetInstance()->Release(BGM_Game);

	//		//エフェクト再生
	//		Effect* ChangeState = nullptr;
	//		ChangeState = NewGO<Effect>(0);
	//		ChangeState->Init(u"Assets/effect/KeyGet.efk");
	//		ChangeState->SetScale({ 200.0f,200.0f,200.0f });
	//		Vector3 effPos = m_keyPos;
	//		effPos.y += 150.0f;
	//		ChangeState->SetPosition(effPos);
	//		ChangeState->Play();


	//		//GameScreen_NoGetKey.casl��폜���AGameScreen_YesGetKey.casl��ĂԂ��ƂŌ��擾��UI��쐬����B

	//		//GameLevel2DクラスのNoGetKeyFlagをfalseに変更。
	//		//※余裕があったら、NoGetKeyFlagをprivateにして関数で変更してください。
	//		GameLevel2D* gamescreenlevel2d = FindGO<GameLevel2D>("gamescreenlevel2d");
	//		gamescreenlevel2d->NoGetKeyFlag = false;
	//		////�O�̌���Q�b�g���Ă��Ȃ��Ƃ���UI��폜�B
	//		//DeleteGO(gamescreenlevel2d->m_sprite);

	//		//���擾���̌�ʉ��Đ��B

	//		SoundManager::GetInstance()->Play(SE_KeyGet);

	//		//falseにして抜ける。
	//		KeyGetSoundFlag = false;
	//	}

	//	//鍵取得フラグをtrueに。
	//	m_player->SetKeyFlg(true);
	//}

	//KeyGetSoundFlagがfalseになったら、
	if(KeyGetSoundFlag ==false) {
		GetDelay++;
	}

	if (GetDelay == 120) {
		//通常BGMのアップテンポ版を再生し変化をつけ、焦らす演出。
		SoundManager::GetInstance()->Play(BGM_GameUpTempo);
	}

	//鍵を取得しているうえでドアとの距離が3m以内ならドアを破壊。

		if (m_player->GetTreasureFlg()) {

			if (GameClearSoundFlag == true) {

				

				//falseにして抜ける。
				GameClearSoundFlag = false;
			}

			//Clear文字表示
			//m_fontRender = NewGO<FontRender>(2);
			//m_fontRender->Init(L"Clear!!", { 50.0),25.0f });

			//ドアのモデルデータを削除。
			//DeleteGO(m_skinModelRender_Door);

			//ドアの当たり判定を削除。
			//m_physicsStaticObject.Release();
		}
}