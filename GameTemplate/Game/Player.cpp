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

	for (int i = 0; i < 2; i++) {
		//SkinModelRenderをNewGO。
		m_skinModelRender[i] = NewGO<SkinModelRender>(1);
	}
	//tkmファイルをロード。
	m_skinModelRender[0]->SetFileNametkm("Assets/modelData/Player_N.tkm");
	//tksファイルをロード。
	m_skinModelRender[0]->SetFileNametks("Assets/modelData/Player_N.tks");

	m_skinModelRender[1]->SetFileNametkm("Assets/modelData/Player_S.tkm");
	m_skinModelRender[1]->SetFileNametks("Assets/modelData/Player_S.tks");

		//アニメーションを設定。
	//m_skinModelRender->InitAnimation(m_animationClips, enAnimClip_Num);
	//最終的な初期化。
	m_skinModelRender[0]->Init(true, false);
	m_skinModelRender[1]->Init(true, false);
	m_skinModelRender[1]->Deactivate();

	return true;
}
void Player::Update()
{
	//Vector3 moveSpeed;
	//moveSpeed.x = g_pad[0]->GetLStickXF() * -3.0f;
	//moveSpeed.z = g_pad[0]->GetLStickYF() * -3.0f;
	//m_pos = m_charaCon.Execute(moveSpeed, 1.0f);
	//m_skinModelRender->SetPosition(m_pos);
	m_movePower.y= 1.0f;
	m_pos = m_charaCon.Execute(m_movePower, 1.0f);

	for (int i = 0; i < 2; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	//Aボタンでプレイヤーの磁力を反転させる
	if (g_pad[0]->IsTrigger(enButtonA)) {
		ChangeState();
		for (int i = 0; i < 2; i++) {
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