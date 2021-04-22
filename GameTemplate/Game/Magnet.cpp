#include "stdafx.h"
#include "Magnet.h"
#include "Player.h"
#include "Key.h"

bool Magnet::Start() {

	//���W��o�^�B

	m_skinModelRender->SetPosition(m_pos);
	m_key = FindGO<Key>("key");

	/*
	���O�������悤�Ƃ��Ă��Ƃ��̂�B
	////���g�̖��O�ɂ���ăX�e�[�g�𕪂��ď���������B
	//if (strcmp(this->m_name.c_str(), "N_Magnet") == 0) {
	//	mState = State_N;
	//}
	//else if (strcmp(this->m_name.c_str(), "S_Magnet") == 0) {
	//	mState = State_S;
	//}

	*/
	
	//�������̂���Ȃ��Ȃ���W���X�V���ē����蔻���t����B
	if (!moveFlg) {
		m_skinModelRender->UpdateWorldMatrix();
		m_physicsStaticObject.CreateFromModel(
			*m_skinModelRender->GetModel(),
			m_skinModelRender->GetModel()->GetWorldMatrix()
		);
		m_physicsStaticObject.SetFriction(10.0f);
	}


	//�������̂���Ȃ��Ȃ瓮�����������ݒ�B
	if (moveFlg) {
		moveSpeed = (moveRange_back - moveRange_front) /= 150.0f;
	}

	//�v���C���[�̃I�u�W�F�N�g��T���B
	m_player = FindGO<Player>("player");
	return true;
}

void Magnet::Update() {
	
	//�������̂Ȃ�
	if (moveFlg) {


		m_pos += moveSpeed;

		//�ݒ肳�ꂽ�E�[�܂ł����瓮���������t�ɂ���B
		if (m_pos.x > moveRange_back.x) {
			m_pos.x = moveRange_back.x;
		
		m_timer++;								//
		if (m_timer == 60) {					//<�ύX>�������΂�1�b�Ԉꎞ��~����悤��if���ǉ�
			moveSpeed *= -1.0f;
			m_timer = 0;						//
			}
		}
		//�ݒ肳�ꂽ���[�܂ł����瓮���������t�ɂ���B
		if (m_pos.x < moveRange_front.x) {
			m_pos.x = moveRange_front.x;

		m_timer++;								//
		if (m_timer == 60) {					//<�ύX>�������΂�1�b�Ԓ�~����悤��if���ǉ�
			moveSpeed *= -1.0f;
			m_timer = 0;						//
			}
		}
	}

	//���W��o�^�B
	m_skinModelRender->SetPosition(m_pos);
	//�v���C���[�Ɍ������ĐL�т�x�N�g��(����)�B
	m_length = m_player->GetPosition() - m_pos;

	if (!m_key->GetdoorbreakFlg()) {
		//�v���C���[�Ƃ̋������Um�ȓ���������͂�^����֐����Ăяo���B
		if (m_length.Length() <= 1000.0f) {
			SetMagnetPower();
		}
	}

	//m_skinModelRender->SetPosition(m_pos);

}

void Magnet::SetMagnetPower()const {

	//��b���͂̋����B
	float magnetPower = 120000.0f;

	//�v���C���[�Ǝ��g�̎����ɂ������Ȃ玩�g�Ɍ������ĐL�т�x�N�g���ɂ���B
	if (mState != m_player->GetPlayerState()) {
		m_length *= -1.0f;
	}

	//�͂�萔�{����B
	float power = (1 / m_length.Length()) * magnetPower;

	//�������΂Ȃ玥�͂�1.5�{�ɁB
	if (plusFlg) {
		power *= 1.5f;
	}
	//�x�N�g���𐳋K������B
	m_length.Normalize();

	//���K�������x�N�g���Ɏ��͂��|����B
	m_length *= power;

	//Z�����ւ̗͂��O�ɂ���B
	m_length.z = 0.0f;

	//�v���C���[�ɗ͂�^����B
	m_player->ReceivePower(m_length);
}