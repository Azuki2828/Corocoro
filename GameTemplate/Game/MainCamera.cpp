#include "stdafx.h"
#include "MainCamera.h"
#include "Player.h"

bool MainCamera::Start() {

	m_player = FindGO<Player>("player");

	g_camera3D->SetPosition({ 0.0f, 70.0f, 150.0f });
	g_camera3D->SetTarget({ 0.0f, 70.0f, 0.0f });

	return true;
}

void MainCamera::Update() {

	m_pos = g_camera3D->GetPosition();
	m_tar = g_camera3D->GetTarget();
	toPos = m_tar - m_pos;
	//コントローラーの入力でY軸周りに回転するカメラを作成する。
	
	//g_pad[0]->GetRStickXF()はコントローラーの右スティックの入力量が取得できる関数。
	m_rotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.005f);
	//回転クォータニオンでtoCameraPosを回す。
	m_rotY.Apply(toPos);

	Vector3 rotAxis;
	rotAxis.Cross(g_vec3AxisY, toPos);
	rotAxis.Normalize();
	
	m_rotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.005f);
	m_rotX.Apply(toPos);

	//新しい注視点をティーポットの少し上に設定する。
	//if (m_player != nullptr) {
		m_tar = m_player->GetPosition();
	//}
	m_tar.y += 50.0f;
	//新しい視点を、「新しい注視点　＋　toCameraPos」で求める。
	m_pos = m_tar + toPos;

	//新しい視点と注視点をカメラに設定する。
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(m_tar);
}