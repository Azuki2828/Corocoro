#include "stdafx.h"
#include "MainCamera.h"
#include "Player.h"
#include "MapChip.h"
#include "DirectionLight.h"

bool MainCamera::Start() {

	m_player = FindGO<Player>(NAME_PLAYER);

	//初期設定
	m_pos = m_player->GetPosition();
	g_camera3D->SetPosition(m_pos);
	m_tar = m_player->GetPosition();
	g_camera3D->SetTarget(m_tar);
	//g_camera3D->Update();

	return true;
}

void MainCamera::Update() {


	//m_pos = g_camera3D->GetPosition();
	//m_tar = g_camera3D->GetTarget();
	//toPos = m_tar - m_pos;
	//コントローラーの入力でY軸周りに回転するカメラを作成する。
	
	//g_pad[0]->GetRStickXF()はコントローラーの右スティックの入力量が取得できる関数。


	//m_rotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.05f);
	////回転クォータニオンでtoCameraPosを回す。
	//m_rotY.Apply(toPos);
	//
	//Vector3 rotAxis;
	//rotAxis.Cross(g_vec3AxisY, toPos);
	//rotAxis.Normalize();
	//
	//m_rotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.05f);
	//m_rotX.Apply(toPos);


	//鍵をとったら天井を走るようにカメラを180°回す。
	if (m_rotFlg) {

		m_dir = FindGO<DirectionLight>(NAME_DIRECTION_LIGHT);

		//ぬける。
		m_rotFlg = false;
		m_cameraRotFlg = true;

		g_engine->SetGameState(GameState::State_Free);
	}
	
	m_tar = m_player->GetPosition();

	//新しい視点を、「新しい注視点　＋　toCameraPos」で求める。
	m_pos = m_tar + m_toPos;

	//新しい視点と注視点をカメラに設定する。
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(m_tar);
	g_camera3D->Update();
}

void MainCamera::FreeUpdate() {

	if (m_cameraRotFlg) {

		m_waitRot += GameTime::GameTimeFunc().GetFrameDeltaTime();
		if (m_waitRot > CAMERA_ROT_WAIT_TIME) {
			Quaternion m_rotZ;
			m_rotZ.SetRotationDeg(Vector3::AxisZ, CAMERA_ROT_VALUE);
			m_rotZ.Apply(m_toPos);
			m_rotZ.Apply(m_rotAxis);
			
			g_camera3D->SetUp(m_rotAxis);

			m_count++;
			if (m_count == ROT_NUM) {
				m_cameraRotFlg = false;
				g_engine->SetGameState(GameState::State_Game);
				PhysicsWorld::GetInstance()->SetGravity(GRAVITY_REVERSE_VALUE);
			}
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