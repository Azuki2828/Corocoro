#include "stdafx.h"
#include "Player.h"
#include "Key.h"
#include "DirectionLight.h"
#include "MainCamera.h"
#include "Background.h"
#include "Game.h"

bool Player::Start()
{
	m_ligData[enPlayer_0].m_directionLigData[0].Dir.Set(0, -1, 1);
	m_ligData[enPlayer_0].m_directionLigData[0].Dir.Normalize();
	//m_ligData[enPlayer_0].m_directionLigData[0].Col.Set(50.0f, 50.0f, 50.0f, 1.0f);
	m_ligData[enPlayer_0].m_directionLigData[0].Col.Set(25.0f, 25.0f, 25.0f, 1.0f);
	m_ligData[enPlayer_0].ambient.Set(0.8f, 0.8f, 0.8f);
	m_ligData[enPlayer_0].metaric = 1.0f;
	m_ligData[enPlayer_0].smooth = 0.35f;
	//m_ligData[enPlayer_0].edge = Edge_1;
	m_ligData[enPlayer_0].powValue = 2.0f;

	m_ligData[enPlayer_1].m_directionLigData[0].Dir.Set(0, -1, 1);
	m_ligData[enPlayer_1].m_directionLigData[0].Dir.Normalize();
	//m_ligData[enPlayer_1].m_directionLigData[0].Col.Set(50.0f, 50.0f, 110.0f, 1.0f);
	m_ligData[enPlayer_1].m_directionLigData[0].Col.Set(25.0f, 25.0f, 55.0f, 1.0f);
	m_ligData[enPlayer_1].ambient.Set(0.8f, 0.8f, 0.8f);
	m_ligData[enPlayer_1].metaric = 1.0f;
	m_ligData[enPlayer_1].smooth = 0.35f;
	//m_ligData[enPlayer_1].edge = Edge_1;
	m_ligData[enPlayer_1].powValue = 2.0f;

	m_game = FindGO<Game>("game");

	auto mainCamera = FindGO<MainCamera>("maincamera");

	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, -2.0f);
		m_rotZ.Apply(m_ligData[enPlayer_0].m_directionLigData[0].Dir);
		m_rotZ.Apply(m_ligData[enPlayer_1].m_directionLigData[0].Dir);
	});

	////アニメーションクリップをロードする。
	//m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	//m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	//m_animationClips[enAnimClip_Run].Load("Assets/animData/walk.tka");
	//m_animationClips[enAnimClip_Run].SetLoopFlag(true);

	//キャラコンの初期化。
	//m_charaCon.Init(50.0f, 100.0f, m_pos);

	//プレイヤーのtkmとtksをロードする種。
	const char* tkmFilePaths[] = {
		"Assets/modelData/tkm/Player_N50.tkm",
		"Assets/modelData/tkm/Player_S50.tkm"
	};
	const char* tksFilePaths[] = {
		"Assets/modelData/tkm/Player_N50.tks",
		"Assets/modelData/tkm/Player_S50.tks"
	};


	//プレイヤーの初期化。
	for (int i = 0; i < enPlayer_Num; i++) {
		//SkinModelRenderをNewGO。
		m_skinModelRender[i] = NewGO<SkinModelRender>(1);
		//tkmファイルをロード。
		m_skinModelRender[i]->SetFileNametkm(tkmFilePaths[i]);
		//tksファイルをロード。
		m_skinModelRender[i]->SetFileNametks(tksFilePaths[i]);
		m_skinModelRender[i]->SetShadowReceiverFlag(true);
		m_skinModelRender[i]->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);
		m_skinModelRender[i]->SetUserLigData(&m_ligData[i]);
		m_skinModelRender[i]->SetZprepassFlag(true);
		m_skinModelRender[i]->Init(true, false);
		if (i == enPlayer_1 || i == enPlayer_0) {
			//プレイヤー1は最初は非アクティブ。
			m_skinModelRender[i]->Deactivate();
		}
	}

	{
		//エフェクト設定
		m_NCahgeState = NewGO<Effect>(0);
		m_NCahgeState->Init(u"Assets/effect/State_N2.efk");
		m_NCahgeState->SetScale({ 95.0f,95.0f,95.0f });
	}
	
	{
		//エフェクト再生
		m_SCahgeState = NewGO<Effect>(0);
		m_SCahgeState->Init(u"Assets/effect/State_S2.efk");
		m_SCahgeState->SetScale({ 95.0f,95.0f,95.0f });
	}
	

	//アニメーションを設定。
	//m_skinModelRender->InitAnimation(m_animationClips, enAnimClip_Num);

	//コライダーを初期化。
	m_sphereCollider.Create(50.0f);

	//剛体を初期化。
	RigidBodyInitData rbInitData;
	//質量を設定する。
	rbInitData.mass = 1.0f;
	rbInitData.collider = &m_sphereCollider;
	//rbInitData.pos.y = 100.0f;
	rbInitData.pos = m_pos;
	//回転のしやすさを設定する。0～1
	rbInitData.localInteria.Set(
		0.5f,
		0.5f,
		0.5f
	);
	m_rigidBody.Init(rbInitData);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	//m_rigidBody.GetBody()->setIgnoreCollisionCheck(m_game->m_ghostBox.GetGhostObject(), true);

	//摩擦力を設定する。0～10
	m_rigidBody.SetFriction(10.0f);
	//線形移動する要素を設定する。
	//0を指定した軸は移動しない。
	m_rigidBody.SetLinearFactor(1.0f, 1.0f, 0.0f);


	//座標を登録。
	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	return true;
}

Player::~Player()
{
	for (int i = 0; i < enPlayer_Num; i++) {
		DeleteGO(m_skinModelRender[i]);
	}
}


void Player::Update()
{

	for (auto& ligData : m_ligData) {
		ligData.eyePos = g_camera3D->GetPosition();
	}

		m_rigidBody.SetLinearFactor(1.0f, 1.0f, 0.0f);
		if (m_backGround == nullptr) {
			m_backGround = FindGO<Background>("background");
		}

		//z方向には動かない。
		m_movePower.z = 0.0f;

		float deathPosY = -1000.0f;
		if (m_backGround != nullptr) {
			deathPosY = m_backGround->GetDeathPosY();
		}

		//剛体の座標と回転を取得。
		Vector3 pos;
		Quaternion rot;
		m_rigidBody.GetPositionAndRotation(pos, rot);
		//剛体の座標と回転をモデルに反映。
		if (m_key == nullptr) {
			m_key = FindGO<Key>("key");

		}
		if (m_treasureBox == nullptr) {
			m_treasureBox = FindGO<TreasureBox>("treasureBox");
		}

		for (int i = 0; i < enPlayer_Num; i++) {
			m_pos = pos;
			m_rot = rot;
			if (m_pos.y < deathPosY) {

				//if (getKeyFlg) {
				//	m_pos = m_key->GetKeyPos();
				//}
				//else {
				//	m_pos = m_startPos;	//<変更>yが500以下になったら初期位置に戻るようにif文追加
				//}
				//m_rigidBody.SetPositionAndRotation(m_pos, m_rot);
				m_game->SetHitPlayer(true);
			}
			//m_skinModelRender[i]->UpdateWorldMatrix(pos, rot, Vector3::One);
			m_skinModelRender[i]->SetPosition(m_pos);
			m_skinModelRender[i]->SetRotation(m_rot);
		}
		//m_model.UpdateWorldMatrix(pos, rot, g_vec3One);
		//剛体に力を加える。
		Vector3 force;
		force.x = g_pad[0]->GetLStickXF() * 500.0f;
		force.z = g_pad[0]->GetLStickYF() * 500.0f;
		//力を加える
		m_rigidBody.AddForce(
			m_movePower,		//力
			g_vec3Zero	//力を加える剛体の相対位置
		);
		m_movePower = { 0.0f,0.0f,0.0f };

		//プレイヤーの位置に合わせる。
		m_SCahgeState->SetPosition(m_pos);
		m_NCahgeState->SetPosition(m_pos);


		if (m_game->m_timer >= m_game->GetGameStartTime()) {
				//Aボタンでプレイヤーの磁力を反転させる
			if (m_deathFlag == false) { //死んでいる場合、処理を動かさない。
				if (g_pad[0]->IsTrigger(enButtonA) && !m_treasureBox->GetTreasureFlg()) {
					ChangeState();

					//NとSを切り替えるときの効果音再生。


					SoundManager::GetInstance()->Play(SE_NSChange);

					//アクティブフラグを更新。
					for (int i = 0; i < enPlayer_Num; i++) {
						if (m_skinModelRender[i]->IsActive() == true) {
							m_skinModelRender[i]->Deactivate();
						}
						else {
							m_skinModelRender[i]->Activate();
						}
					}

				}
			}
			

			Vector3 m_lightCameraTar = m_pos;

			Vector3 m_lightCameraPos = m_lightCameraTar;
			//m_lightCameraPos.z += 5.0f;
			if (getKeyFlg) {
				m_lightCameraPos.y -= 500.0f;
			}
			else {
				m_lightCameraPos.y += 500.0f;
			}

			//Vector3 Cpos = { 300.0f,400.0f,0.0f };
			//Vector3 CTar = { 300.0f,300.0f,0.0f };

			Camera::GetLightCamera()->SetPosition(m_lightCameraPos);
			Camera::GetLightCamera()->SetTarget(m_lightCameraTar);

			//Vector3 toCamere = g_camera3D->GetPosition() - g_camera3D->GetTarget();
			//g_camera3D->SetTarget(pos);
			//toCamere.y = 100.0f;
			//toCamere.z = -2500.0f;
			//g_camera3D->SetPosition(pos + toCamere);



			Key* key = FindGO<Key>("key");

			//ゲームクリアしてから5秒たったら、
			if (key->GameOverCount > 300) {
				//クラスを削除。
				DeleteGO(this);
			}
		}

		//pStateの極とモデルの極が違う場合、モデルの極をpStateの極に合わせる。
		if (m_deathFlag == false) { //死んでいる場合、処理を動かさない。
			if (pState == State_N && m_skinModelRender[enPlayer_0]->IsActive() == true)
			{

			}
			else if (pState == State_S && m_skinModelRender[enPlayer_1]->IsActive() == true)
			{

			}
			else {
				for (int i = 0; i < enPlayer_Num; i++) {
					m_skinModelRender[i]->Deactivate();
				}

				m_skinModelRender[pState]->Activate();
			}
		}
}

void Player::FreeUpdate() {
	
	m_rigidBody.SetPositionAndRotation(m_pos, m_rot);
}

void Player::ChangeState() {
	if (pState == State_N) {
		pState = State_S;
	
		Vector3 effPos = m_pos;
		m_SCahgeState->SetPosition(effPos);
		m_SCahgeState->Play();
	}
	else {
		pState = State_N;
	
		Vector3 effPos = m_pos;
		m_NCahgeState->SetPosition(effPos);
		m_NCahgeState->Play();
		
	}
}

void Player::Render(RenderContext& rc) {

	if (RenderContext::Render_Mode::RenderMode_Normal) {
		wchar_t numtext[5][64];

		swprintf_s(numtext[0], L"State:%d", pState);
		//swprintf_s(numtext[1], L"vit+%d", m_plus_vit);

		m_font.Begin(rc);

		m_font.Draw(
			numtext[0],
			{ 120.0f, 10.0f },
			{ 0.55f,0.0f,0.0f,1.0f },
			0.0f,
			0.4f,
			{ 0.5f,0.5f }
		);

		m_font.End(rc);
	}
}