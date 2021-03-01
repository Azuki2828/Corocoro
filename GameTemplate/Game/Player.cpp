#include "stdafx.h"
#include "Player.h"
#include "DirectionLight.h"
#include "MainCamera.h"

bool Player::Start()
{
	char objName[64];
	wcstombs(objName, name, 64);

	////�A�j���[�V�����N���b�v�����[�h����B
	//m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	//m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	//m_animationClips[enAnimClip_Run].Load("Assets/animData/walk.tka");
	//m_animationClips[enAnimClip_Run].SetLoopFlag(true);

	//m_charaCon.Init(40.0f, 100.0f, g_vec3Zero);
	//m_movePower = { 0.0f,0.0f,0.0f };

	//SkinModelRender��NewGO�B
	m_skinModelRender = NewGO<SkinModelRender>(0);


	//tkm�t�@�C�������[�h�B
	char filePathtkm[64];
	sprintf(filePathtkm, "Assets/modelData/%s.tkm", objName);
	m_skinModelRender->SetFileNametkm(static_cast<const char*>(filePathtkm));

	//tks�t�@�C�������[�h�B
	char filePathtks[64];
	sprintf(filePathtks, "Assets/modelData/%s.tks", objName);
	m_skinModelRender->SetFileNametkm(static_cast<const char*>(filePathtks));

	//�A�j���[�V������ݒ�B
	//m_skinModelRender->InitAnimation(m_animationClips, enAnimClip_Num);
	//�ŏI�I�ȏ������B
	m_skinModelRender->Init(true, false);


	m_fontRender = NewGO<FontRender>(1);
	m_fontRender->Init(L"hello!!");
	return true;
}
void Player::Update()
{
	//Vector3 moveSpeed;
	//moveSpeed.x = g_pad[0]->GetLStickXF() * -3.0f;
	//moveSpeed.z = g_pad[0]->GetLStickYF() * -3.0f;
	//m_pos = m_charaCon.Execute(moveSpeed, 1.0f);
	//m_skinModelRender->SetPosition(m_pos);
	//m_movePower.y= 1.0f;
	//m_pos = m_charaCon.Execute(m_movePower, 1.0f);
	m_skinModelRender->SetPosition(m_pos);
}

//void Player::ChangeState() {
//	if (pState == State_N) {
//		pState = State_S;
//	}
//	else if (pState == State_S) {
//		pState = State_N;
//	}
//}