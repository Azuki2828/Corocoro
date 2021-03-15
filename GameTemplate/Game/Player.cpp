#include "stdafx.h"
#include "Player.h"
#include "DirectionLight.h"
#include "MainCamera.h"

bool Player::Start()
{
	////�A�j���[�V�����N���b�v�����[�h����B
	//m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	//m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	//m_animationClips[enAnimClip_Run].Load("Assets/animData/walk.tka");
	//m_animationClips[enAnimClip_Run].SetLoopFlag(true);

	//�L�����R���̏������B
	m_charaCon.Init(50.0f, 100.0f, m_pos);

	//�v���C���[��tkm��tks�����[�h�����B
	const char* tkmFilePaths[] = {
		"Assets/modelData/tkm/Player_N.tkm",
		"Assets/modelData/tkm/Player_S.tkm"
	};
	const char* tksFilePaths[] = {
		"Assets/modelData/tkm/Player_N.tks",
		"Assets/modelData/tkm/Player_S.tks"
	};

	//�v���C���[�̏������B
	for (int i = 0; i < enPlayer_Num; i++) {
		//SkinModelRender��NewGO�B
		m_skinModelRender[i] = NewGO<SkinModelRender>(1);
		//tkm�t�@�C�������[�h�B
		m_skinModelRender[i]->SetFileNametkm(tkmFilePaths[i]);
		//tks�t�@�C�������[�h�B
		m_skinModelRender[i]->SetFileNametks(tksFilePaths[i]);
		m_skinModelRender[i]->Init(true, false);
		if (i == enPlayer_1) {
			//�v���C���[1�͍ŏ��͔�A�N�e�B�u�B
			m_skinModelRender[i]->Deactivate();
		}
	}
	


		//�A�j���[�V������ݒ�B
	//m_skinModelRender->InitAnimation(m_animationClips, enAnimClip_Num);

	//���W��o�^�B
	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	return true;
}
void Player::Update()
{
	//�d�͂�ݒ�B
	m_movePower.y -= 0.2f;

	//z�����ɂ͓����Ȃ��B
	m_movePower.z = 0.0f;

	//���W��ݒ�B
	m_pos = m_charaCon.Execute(m_movePower, 1.0f);

	//�ǂɓ������Ă���Ȃ�
	if (m_charaCon.IsOnWall()) {

		//1/2�̗͂Œ��˕Ԃ�B
		m_movePower.x *= -0.5f;
	}

	//�n�ʏ�ɂ���Ȃ�
	if (m_charaCon.IsOnGround()) {

		//�E�ɓ����Ă���
		if (m_movePower.x >= 0.0f) {
			//���C�B
			m_movePower.x -= 0.02f;
			//�������炵��������O�ɂ���B
			if (m_movePower.x < 0.0f) {
				m_movePower.x = 0.0f;
			}
		}//���ɓ����Ă���
		else {
			//���C�B
			m_movePower.x += 0.02f;
			//�������₵��������O�ɂ���B
			if (m_movePower.x > 0.0f) {
				m_movePower.x = 0.0f;
			}
		}

	}
	
	//���W��o�^�B
	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	//A�{�^���Ńv���C���[�̎��͂𔽓]������
	if (g_pad[0]->IsTrigger(enButtonA)) {
		ChangeState();

		//�A�N�e�B�u�t���O���X�V�B
		for (int i = 0; i < enPlayer_Num; i++) {
			if (m_skinModelRender[i]->IsActive() == true) {
				m_skinModelRender[i]->Deactivate();
			}
			else {
				m_skinModelRender[i]->Activate();
			}
		}
	}
}

void Player::ChangeState() {
	if (pState == State_N) {
		pState = State_S;
	}
	else {
		pState = State_N;
	}
}

void Player::Render(RenderContext& rc) {

	wchar_t numtext[5][64];

	swprintf_s(numtext[0], L"State:%d", pState);
	//swprintf_s(numtext[1], L"vit+%d", m_plus_vit);

	m_font.Begin(rc);

	m_font.Draw(
		numtext[0],
		{ 120.0f, 10.0f },
		{ 0.55f,0.0f,0.0f,1.0f },
		0.0f,
		0.4f,
		{ 0.5f,0.5f }
	);

	m_font.End(rc);
}