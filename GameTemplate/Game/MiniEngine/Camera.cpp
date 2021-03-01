#include "stdafx.h"
#include "Camera.h"
#include "Player.h"

bool Camera::Start() {

	return true;
}

void Camera::Update() {

	m_player = FindGO<Player>("player");

	m_tar = m_player->GetPosition();
	//m_tar.y += 30.0f;
	m_tar.z += 50.0f;

	m_pos = m_tar + toCameraPos;

	g_camera3D->SetTarget(m_tar);
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetFar(16000.0f);
	g_camera3D->Update();
}