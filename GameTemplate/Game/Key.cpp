#include "stdafx.h"
#include "Key.h"
#include "Player.h"
#include "Background.h"
#include "ResultScene.h"
#include "GameLevel2D.h"
#include "MainCamera.h"
#include "Game.h"

bool Key::Start() {

	m_player = FindGO<Player>(NAME_PLAYER);
	m_game = FindGO<Game>(NAME_GAME);
	m_player->GetRigidBody()->GetBody()->setIgnoreCollisionCheck(m_ghostBox.GetGhostObject(), true);
	
	//鍵があったら座標を登録。
	if (m_skinModelRender_Key != nullptr) {

		m_skinModelRender_Key->SetPosition(m_keyPos);
		m_skinModelRender_Key->SetScale(m_keyScale);
		m_skinModelRender_Key->UpdateWorldMatrix();
	}

	//ドアがあったら座標を登録+当たり判定を付ける。
	if (m_skinModelRender_Door != nullptr) {
		m_skinModelRender_Door->SetPosition(m_doorPos);
		m_skinModelRender_Door->SetScale(m_doorScale);
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
	char filePathtkm[NAME_SIZE];

	sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
	m_skinModelRender_Key = NewGO<SkinModelRender>(enPriority_Zeroth);
	m_skinModelRender_Key->SetFileNametkm(filePathtkm);
	m_skinModelRender_Key->SetShadowReceiverFlag(true);
	m_skinModelRender_Key->SetZprepassFlag(true);
	m_skinModelRender_Key->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

	m_ligKeyData.m_directionLigData[enData_Zeroth].Dir.Set(KEY_LIG_FIRST_DIRECTION);
	m_ligKeyData.m_directionLigData[enData_Zeroth].Dir.Normalize();
	m_ligKeyData.m_directionLigData[enData_Zeroth].Col.Set(KEY_LIG_FIRST_COLOR);

	m_ligKeyData.m_directionLigData[enData_First].Dir.Set(KEY_LIG_SECOND_DIRECTION);
	m_ligKeyData.m_directionLigData[enData_First].Dir.Normalize();
	m_ligKeyData.m_directionLigData[enData_First].Col.Set(KEY_LIG_SECOND_COLOR);

	m_ligKeyData.metaric = KEY_METARIC;
	m_ligKeyData.smooth = KEY_SMOOTH;
	m_ligKeyData.ambient.Set(KEY_AMBIENT);
	m_ligKeyData.edge = Edge_1;
	m_ligKeyData.powValue = KEY_POW_VALUE;
	m_skinModelRender_Key->SetUserLigData(&m_ligKeyData);
	m_skinModelRender_Key->Init();
}

void Key::InitDoor(const char* name) {

	char filePathtkm[NAME_SIZE];

	sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
	m_skinModelRender_Door = NewGO<SkinModelRender>(enPriority_Zeroth);
	m_skinModelRender_Door->SetFileNametkm(filePathtkm);
	m_skinModelRender_Door->SetShadowReceiverFlag(true);
	m_ligDoorData.m_directionLigData[0].Dir.Set(TREASURE_BOX_FLOOR_LIG_DIRECTION);
	m_ligDoorData.m_directionLigData[0].Dir.Normalize();
	m_ligDoorData.m_directionLigData[0].Col.Set(TREASURE_BOX_FLOOR_LIG_COLOR);

	m_ligDoorData.metaric = TREASURE_BOX_METARIC;
	m_ligDoorData.smooth = TREASURE_BOX_SMOOTH;
	m_ligDoorData.ambient.Set(TREASURE_BOX_AMBIENT);
	m_skinModelRender_Door->SetUserLigData(&m_ligDoorData);
	m_skinModelRender_Door->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

	auto mainCamera = FindGO<MainCamera>(NAME_MAIN_CAMERA);
	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, -CAMERA_ROT_VALUE);
		m_rotZ.Apply(m_ligKeyData.m_directionLigData[enData_Zeroth].Dir);
		m_rotZ.Apply(m_ligDoorData.m_directionLigData[enData_Zeroth].Dir);
	});

	m_skinModelRender_Door->SetUserLigData(&m_ligDoorData);
	m_skinModelRender_Door->Init();
}

void Key::Update() {

	if (m_skinModelRender_Key != nullptr) {
		
		m_keyRotTime += GameTime::GameTimeFunc().GetFrameDeltaTime();
		m_keyRot.SetRotationDeg(Vector3::AxisY, BASE_KEY_ROT_VALUE * m_keyRotTime);
		m_skinModelRender_Key->SetRotation(m_keyRot);
	}

	if (m_game->GetTime() > KEY_GET_START_TIME) {
		PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

			if (m_ghostBox.IsSelf(contactObject) && !m_player->GetKeyFlg()) {

				//鍵を消去して取得効果音を再生。
				DeleteGO(m_skinModelRender_Key);

				//MainCameraクラスのフラグ。ステージの回転をカメラと重力を回転させることで実装する。
				//クラスにアクセスし、情報をもらう。
				maincamera = FindGO<MainCamera>(NAME_MAIN_CAMERA);
				//MainCameraクラスのRotFlg変数をtrueに。
				maincamera->SetRotFlg(true);


				if (m_keyGetSoundFlag) {

					//通常BGMを削除。
					BackGround* background = FindGO<BackGround>(NAME_BACK_GROUND);
					SoundManager::GetInstance()->Release(BGM_Game);

					//エフェクト再生
					Effect* ChangeState = nullptr;
					ChangeState = NewGO<Effect>(enPriority_Zeroth);
					ChangeState->Init(KEY_GET_EFFECT_FILE_PATH);
					ChangeState->SetScale(KEY_GET_EFFECT_SCALE);
					Vector3 effPos = m_keyPos;
					effPos += KEY_GET_EFFECT_ADD_POS;
					ChangeState->SetPosition(effPos);
					ChangeState->Play();

					m_gameLevel2D = FindGO<GameLevel2D>(NAME_GAME_LEVEL2D);
					m_gameLevel2D->SetKeyFlg(false);
					

					SoundManager::GetInstance()->Play(SE_KeyGet);

					//falseにして抜ける。
					m_keyGetSoundFlag = false;
				}

				//鍵取得フラグをtrueに。
				m_player->SetKeyFlg(true);

			}
			});
	}
	

	if (!m_startUpTempoSoundFlg) {
		//KeyGetSoundFlagがfalseになったら、
		if (!m_keyGetSoundFlag) {
			m_delayCount += GameTime().GameTimeFunc().GetFrameDeltaTime();
		}

		if (m_delayCount >= SOUND_DERAY_COUNT) {
			//通常BGMのアップテンポ版を再生し変化をつけ、焦らす演出。
			SoundManager::GetInstance()->Play(BGM_GameUpTempo);
			m_startUpTempoSoundFlg = true;
		}
	}

	//鍵を取得しているうえでドアとの距離が3m以内ならドアを破壊。

		if (m_player->GetTreasureFlg()) {

			if (m_gameClearSoundFlag) {

				//falseにして抜ける。
				m_gameClearSoundFlag = false;
			}
		}
}