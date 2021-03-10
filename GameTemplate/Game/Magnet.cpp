#include "stdafx.h"
#include "Magnet.h"
#include "Player.h"

bool Magnet::Start() {
	m_skinModelRender->SetPosition(m_pos);
	////���g�̖��O�ɂ���ăX�e�[�g�𕪂��ď���������B
	//if (strcmp(this->m_name.c_str(), "N_Magnet") == 0) {
	//	mState = State_N;
	//}
	//else if (strcmp(this->m_name.c_str(), "S_Magnet") == 0) {
	//	mState = State_S;
	//}
	m_skinModelRender->UpdateWorldMatrix();
	m_physicsStaticObject.CreateFromModel(
		*m_skinModelRender->GetModel(),
		m_skinModelRender->GetModel()->GetWorldMatrix()
	);

	//�v���C���[�̃I�u�W�F�N�g��T���B
	m_player = FindGO<Player>("player");
	return true;
}

void Magnet::Update() {
	
	//�v���C���[�Ɍ������ĐL�т�x�N�g��(����)�B
	m_length = m_player->GetPosition() - m_pos;

	//�v���C���[�Ƃ̋�����10m�ȓ���������͂�^����֐����Ăяo���B
	if (m_length.Length() <= 600.0f) {
		SetMagnetPower();
	}

	//m_skinModelRender->SetPosition(m_pos);

}

void Magnet::SetMagnetPower()const {


	//�v���C���[�Ǝ��g�̎����ɂ������Ȃ玩�g�Ɍ������ĐL�т�x�N�g���ɂ���B
	if (mState != m_player->GetPlayerState()) {
		m_length *= -1.0f;
	}

	//�͂�萔�{����B
	float power = (1 / m_length.Length()) * 100.0f;

	//�x�N�g���𐳋K������B
	m_length.Normalize();

	m_length *= power;
	m_length.z = 0.0f;

	//�v���C���[�ɗ͂�^����B
	m_player->ReceivePower(m_length);
}