#include "stdafx.h"
#include "Player.h"
#include "DirectionLight.h"
#include "MainCamera.h"

bool Player::Start()
{

	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->SetFileNametkm("Assets/modelData/unityChan.tkm");
	m_skinModelRender->SetFileNametks("Assets/modelData/unityChan.tks");



	//アニメーションクリップをロードする。
	m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimClip_Run].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimClip_Run].SetLoopFlag(true);

	m_skinModelRender->InitAnimation(m_animationClips, enAnimClip_Num);
	m_skinModelRender->Init(true, false);
	//キャラコンを初期化。
	m_charaCon.Init(40.0f, 100.0f, g_vec3Zero);


	return true;
}
void Player::Update()
{
	Vector3 moveSpeed;
	moveSpeed.x = g_pad[0]->GetLStickXF() * -3.0f;
	moveSpeed.z = g_pad[0]->GetLStickYF() * -3.0f;
	m_pos = m_charaCon.Execute(moveSpeed, 1.0f);
	m_skinModelRender->SetPosition(m_pos);
}