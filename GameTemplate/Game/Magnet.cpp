#include "stdafx.h"
#include "Magnet.h"
#include "Player.h"
#include "Key.h"
#include "Game.h"

bool Magnet::Start() {

	//���W��o�^�B

	m_skinModelRender->SetPosition(m_pos);
	m_key = FindGO<Key>("key");
	m_game = FindGO<Game>("game");

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

	SetMagnetTriggerBox(m_game->GetStageNum());
	m_player->GetRigidBody()->GetBody()->setIgnoreCollisionCheck(m_ghostBox.GetGhostObject(), true);
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
	m_length = m_player->GetPosition() - m_magnetPos;
	
	//if (!m_key->GetdoorbreakFlg()) {
		//�v���C���[�Ƃ̋������Um�ȓ���������͂�^����֐����Ăяo���B
	//if (m_length.Length() <= 1000.0f) {
	//	SetMagnetPower();
	//}
	static float triggerTime = 0.0f;

	triggerTime += GameTime::GameTimeFunc().GetFrameDeltaTime();
	//if (triggerTime >= 1.0f) {
		PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

			if (m_ghostBox.IsSelf(contactObject) == true) {
				//m_ghostObject�ƂԂ�����
				//m_pointLig->SetActiveFlag(true);	//�|�C���g���C�g������B
				//m_ghostBox.SetPosition({ 700.0f,405.0f,0.0f });
				SetMagnetPower();
			}
		});
		triggerTime = 0.0f;
	//}
	//m_skinModelRender->SetPosition(m_pos);

}

void Magnet::SetMagnetPower()const {

	//��b���͂̋����B
	float magnetPower = 100000.0f;

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

void Magnet::SetMagnetTriggerBox(int stageNum) {

	Vector3 ghostPos = m_pos;
	ghostPos.z -= 200.0f;
	switch (stageNum) {		//�X�e�[�W�ԍ�

	case 1:


		switch (m_magnetNum) {		//���Δԍ�

		case 1:
		case 2:
		case 3:
		case 4:
		case 9:
		case 26:
		case 34:
		case 35:
		case 36:
		case 37:
			CreateTriggerBox(Left3);
			break;
		case 11:
		case 24:
		case 27:
			CreateTriggerBox(Down3);
			break;
		case 6:
		case 7:
		case 8:
		case 10:
		case 12:
		case 13:
		case 14:
		case 17:
		case 18:
		case 19:
		case 22:
		case 31:
		case 32:
		case 33:
			CreateTriggerBox(Right3);
			break;
		case 23:
		case 29:
		case 30:
			CreateTriggerBox(Up3);
			break;
		case 0:
			ghostPos.x += 100.0f;
			ghostPos.y -= 100.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 600.0f, 400.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 5:
			ghostPos.x -= 100.0f;
			ghostPos.y -= 150.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 400.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 15:
			ghostPos.x += 200.0f;
			ghostPos.y -= 150.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 400.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 16:
			ghostPos.x += 100.0f;
			ghostPos.y += 100.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 600.0f, 400.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 20:
			ghostPos.x += 200.0f;
			ghostPos.y += 250.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 400.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 21:
			ghostPos.x -= 100.0f;
			ghostPos.y += 250.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 400.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 25:
			ghostPos.x -= 50.0f;
			ghostPos.y -= 150.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 300.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 28:
			ghostPos.x -= 50.0f;
			ghostPos.y += 250.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 300.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		}
		break;
	case 2:
		switch (m_magnetNum) {
		case 1:
		case 3:
		case 10:
		case 11:
			CreateTriggerBox(Up4);
			break;
		case 4:
		case 5:
		case 6:
			CreateTriggerBox(Right3);
			break;
		case 7:
		case 8:
		case 9:
			CreateTriggerBox(Right4);
			break;
		case 13:
		case 14:
			CreateTriggerBox(Down4);
			break;
		case 16:
		case 17:
		case 18:
			CreateTriggerBox(Left3);
			break;
		case 19:
		case 20:
		case 21:
			CreateTriggerBox(Left5);
			break;
		case 0:
		case 2:
			ghostPos.x -= 50.0f;
			ghostPos.y += 300.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 300.0f, 400.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 12:
			ghostPos.x -= 50.0f;
			ghostPos.y -= 200.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 300.0f, 400.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 15:
			ghostPos.x += 150.0f;
			ghostPos.y -= 200.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 300.0f, 400.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 22:
			ghostPos.x += 50.0f;
			ghostPos.y += 200.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 500.0f, 200.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 23:
			ghostPos.x += 50.0f;
			ghostPos.y -= 100.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 500.0f, 200.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 24:
			ghostPos.x += 50.0f;
			ghostPos.y -= 50.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 300.0f, 500.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		}

		break;
	case 3:
		switch (m_magnetNum) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			CreateTriggerBox(Right4);
			break;
		case 9:
		case 10:
		case 11:
			CreateTriggerBox(Up3);
			break;
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			CreateTriggerBox(Left4);
			break;
		case 20:
		case 21:
		case 22:
			CreateTriggerBox(Down2);
			break;
		case 12:
		case 13:
			ghostPos.x += 100.0f;
			ghostPos.y += 150.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 200.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 23:
			ghostPos.x += 200.0f;
			ghostPos.y -= 50.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 400.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 24:
			ghostPos.x -= 100.0f;
			ghostPos.y += 50.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 400.0f, 500.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 25:
		case 26:
			ghostPos.x += 50.0f;
			ghostPos.y += 50.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 100.0f, 500.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case 27:
			ghostPos.x += 50.0f;
			ghostPos.y += 50.0f;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				{ 500.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		}
		break;
	}
}

void Magnet::CreateTriggerBox(int type) {

	Vector3 ghostPos = m_pos;
	ghostPos.z -= 200.0f;
	switch (type) {
	case Left3:
		ghostPos.x -= 150.0f;
		ghostPos.y += 50.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 300.0f, 100.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Left4:
		ghostPos.x -= 200.0f;
		ghostPos.y += 50.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 400.0f, 100.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Left5:
		ghostPos.x -= 250.0f;
		ghostPos.y += 50.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 500.0f, 100.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Right3:
		ghostPos.x += 250.0f;
		ghostPos.y += 50.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 300.0f, 100.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Right4:
		ghostPos.x += 300.0f;
		ghostPos.y += 50.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 400.0f, 100.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Down2:
		ghostPos.x += 50.0f;
		ghostPos.y -= 100.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 100.0f, 200.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Down3:
		ghostPos.x += 50.0f;
		ghostPos.y -= 150.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 100.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Down4:
		ghostPos.x += 50.0f;
		ghostPos.y -= 200.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 100.0f, 400.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Up2:
		ghostPos.x += 50.0f;
		ghostPos.y += 200.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 100.0f, 200.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Up3:
		ghostPos.x += 50.0f;
		ghostPos.y += 250.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 100.0f, 300.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Up4:
		ghostPos.x += 50.0f;
		ghostPos.y += 300.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 100.0f, 400.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	}
}