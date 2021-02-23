#include "stdafx.h"
#include "Player.h"
#include "DirectionLight.h"
#include "MainCamera.h"

bool Player::Start()
{
	////アニメーションクリップをロードする。
	//m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	//m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	//m_animationClips[enAnimClip_Run].Load("Assets/animData/walk.tka");
	//m_animationClips[enAnimClip_Run].SetLoopFlag(true);

	m_charaCon.Init(40.0f, 100.0f, g_vec3Zero);
	m_movePower = { 0.0f,0.0f,0.0f };

	//SkinModelRenderをNewGO。
	m_skinModelRender = NewGO<SkinModelRender>(0);
	//tkmファイルをロード。
	m_skinModelRender->SetFileNametkm("Assets/modelData/Player_N.tkm");
	//tksファイルをロード。
	m_skinModelRender->SetFileNametks("Assets/modelData/Player_N.tks");
	//アニメーションを設定。
	//m_skinModelRender->InitAnimation(m_animationClips, enAnimClip_Num);
	//最終的な初期化。
	m_skinModelRender->Init(true, false);

	return true;
}
void Player::Update()
{
	//Vector3 moveSpeed;
	//moveSpeed.x = g_pad[0]->GetLStickXF() * -3.0f;
	//moveSpeed.z = g_pad[0]->GetLStickYF() * -3.0f;
	//m_pos = m_charaCon.Execute(moveSpeed, 1.0f);
	//m_skinModelRender->SetPosition(m_pos);

	m_pos = m_charaCon.Execute(m_movePower, 1.0f);
	m_skinModelRender->SetPosition(m_pos);

	//Aボタンでプレイヤーの磁力を反転させる
	if (g_pad[0]->IsTrigger(enButtonA)) {
		if (pState == State_N) {
			pState = State_S;
		}
		else if (pState == State_S) {
			pState = State_N;
		}
	}
}