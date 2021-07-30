#include "stdafx.h"
#include "MainCamera.h"
#include "Player.h"
#include "MapChip.h"
#include "DirectionLight.h"

bool MainCamera::Start() {
	
	//クラスのインスタンスを探す。
	m_player = FindGO<Player>(NAME_PLAYER);

	//座標を設定する
	m_pos = m_player->GetPosition();
	g_camera3D->SetPosition(m_pos);
	//ターゲットを設定する
	m_tar = m_player->GetPosition();
	g_camera3D->SetTarget(m_tar);

	return true;
}

void MainCamera::Update() {

	//鍵をとったら天井を走るようにカメラを180°回す。
	if (m_rotFlg) {
		//クラスのインスタンスを探す
		m_dir = FindGO<DirectionLight>(NAME_DIRECTION_LIGHT);

		//ぬける。
		m_rotFlg = false;
		m_cameraRotFlg = true;

		//ゲームステートを回転時のものに設定する
		g_engine->SetGameState(GameState::State_Free);
	}
	//ターゲットを更新する
	m_tar = m_player->GetPosition();

	//新しい視点を、「新しい注視点　＋　toCameraPos」で求める。
	m_pos = m_tar + m_toPos;

	//新しい視点と注視点をカメラに設定する。
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(m_tar);
	g_camera3D->Update();
}

void MainCamera::FreeUpdate() {

	//カメラが回転しているときの処理
	if (m_cameraRotFlg) {

		m_waitRot += GameTime::GameTimeFunc().GetFrameDeltaTime();
		//一定時間たったら
		if (m_waitRot > CAMERA_ROT_WAIT_TIME) {
			Quaternion m_rotZ;
			m_rotZ.SetRotationDeg(Vector3::AxisZ, CAMERA_ROT_VALUE);
			m_rotZ.Apply(m_toPos);
			m_rotZ.Apply(m_rotAxis);
			
			g_camera3D->SetUp(m_rotAxis);

			m_count++;
			//半回転したら
			if (m_count == ROT_NUM) {
				m_cameraRotFlg = false;
				//ゲームステートをゲーム中に設定する。
				g_engine->SetGameState(GameState::State_Game);
				//重力を反転させる
				PhysicsWorld::GetInstance()->SetGravity(GRAVITY_REVERSE_VALUE);
			}

			//回転時の各処理を実行する
			for (auto func : changeRotCameraEvent) {
				func();
			}
		}
	}

	//新しい視点を、「新しい注視点　＋　toCameraPos」で求める。
	m_pos = m_tar + m_toPos;

	//新しい視点と注視点をカメラに設定する。
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(m_tar);
	g_camera3D->Update();
}