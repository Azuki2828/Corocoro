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
	//�R���g���[���[�̓��͂�Y������ɉ�]����J�������쐬����B
	
	//g_pad[0]->GetRStickXF()�̓R���g���[���[�̉E�X�e�B�b�N�̓��͗ʂ��擾�ł���֐��B
	m_rotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.005f);
	//��]�N�H�[�^�j�I����toCameraPos���񂷁B
	m_rotY.Apply(toPos);

	Vector3 rotAxis;
	rotAxis.Cross(g_vec3AxisY, toPos);
	rotAxis.Normalize();
	
	m_rotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.005f);
	m_rotX.Apply(toPos);

	//�V���������_���e�B�[�|�b�g�̏�����ɐݒ肷��B
	//if (m_player != nullptr) {
		m_tar = m_player->GetPosition();
	//}
	m_tar.y += 50.0f;
	//�V�������_���A�u�V���������_�@�{�@toCameraPos�v�ŋ��߂�B
	m_pos = m_tar + toPos;

	//�V�������_�ƒ����_���J�����ɐݒ肷��B
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(m_tar);
}