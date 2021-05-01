#include "stdafx.h"
#include "MainCamera.h"
#include "Player.h"

bool MainCamera::Start() {

	m_player = FindGO<Player>("player");

	//�����ݒ�
	m_pos = m_player->GetPosition();
	m_pos.z += 100.0f;
	g_camera3D->SetPosition(m_pos);
	m_tar = m_player->GetPosition();
	g_camera3D->SetTarget(m_tar);
	g_camera3D->Update();

	return true;
}

void MainCamera::Update() {

	if (RotFlg == true) {
		//�����Ƃ�����V��𑖂�悤�ɃJ������180���񂷁B
		//�J�����ɉ�]����`����B
		g_camera3D->SetUp(m_rotZ);
		//�v���X�ŏd�͂𔽓]������B
		PhysicsWorld::GetInstance()->SetGravity({ 0, 300, 0 });

		//�ʂ���B
		RotFlg = false;
	}

	if (CameraScrollFlag == true) {
		//�����̓X�e�[�W�I�����ɉ��X�e�[�W�ڂ��ŃX�E�B�b�`�����ăX�e�[�W���Ƃ̃J�����X�N���[���֐����ĂԁB

		//�X�e�[�W1���J�����X�N���[���Œ��߂�֐�
		Stage1ScrollCamera();
	}
	//�ʏ펞�̏����B
	else {
		if (m_player != nullptr) {
			//�v���C���[�̏ꏊ���擾���A�����_�̕ϐ��ɓ����B
			m_tar = m_player->GetPosition();
			//�v���C���[�̂�����Ə�ɒ����_��u���B
			m_tar.y += 50.0f;

		}
	}

	//�V�������_���A�u�V���������_�@�{�@toCameraPos�v�ŋ��߂�B
	m_pos = m_tar + toPos;

	//�V�������_�ƒ����_���J�����ɐݒ肷��B
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(m_tar);
	g_camera3D->Update();
}


//�X�e�[�W1���J�����X�N���[���Œ��߂�֐�
void MainCamera::Stage1ScrollCamera() {
	switch (CamePosiFlag) {
	case 0:
		//�X�^�[�g�̏ꏊ�ŏ�����ʂ̃X�N���[�����Œ�B�X�^�[�g�n�_���v���C���[�ɓ`���₷������B
		ScrollStaticTimer++;
		//2�b�Î~�B
		if (ScrollStaticTimer == 120) {
			CamePosiFlag = 1;
		}
		break;
	case 1:
		//�X�^�[�g�ʒu����E�[��...
		m_tar.x += 30.0f;
		if (m_tar.x > 3000.0f) {
			CamePosiFlag = 2;
		}
		break;
	case 2:
		//2�K�w�܂ŏ�ɂ�����B
		m_tar.y += 30.0f;
		if (m_tar.y > 1500.0f) {
			CamePosiFlag = 3;
		}
		break;
	case 3:
		//2�K�w�̉E�[���獶�[�ɐi�ށB
		m_tar.x -= 30.0f;
		if (m_tar.x < 700.0f) {
			CamePosiFlag = 4;
		}
		break;
	case 4:
		//3�K�w�܂ŏ�ɂ�����B
		m_tar.y += 30.0f;
		if (m_tar.y > 2800.0f) {
			CamePosiFlag = 5;
		}
		break;
	case 5:
		//���̏ꏊ�܂ŉE�ɐi�ށB
		m_tar.x += 30.0f;
		if (m_tar.x > 3000.0f) {
			CamePosiFlag = 6;
		}
		break;
	case 6:
		//���̏ꏊ�ŏ�����ʂ̃X�N���[�����Œ�B�ړI�n���v���C���[�ɓ`���₷������B
		ScrollStaticTimer++;
		//2�b�Î~�B
		if (ScrollStaticTimer == 240) {
			CamePosiFlag = 7;
		}
		break;
	case 7:
		//�J�����̏ꏊ����ŒZ�ŃX�^�[�g�܂Ŗ߂�B
		m_tar.x -= 40.0f;
		m_tar.y -= 35.0f;
		//�v���C���[�̏������W�܂Ŗ߂�����A
		if (m_tar.x < 400.0f && m_tar.y < 370.0f) {
			//�J�������{�[�����_�ɖ߂�������J�����X�N���[���̃t���O�𔲂���B
			CameraScrollFlag = false;
		}
		break;
	}
}