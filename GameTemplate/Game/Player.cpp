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

	m_charaCon.Init(50.0f, 100.0f, m_pos);
	//m_movePower = { 0.0f,0.0f,0.0f };
	const char* tkmFilePaths[] = {
		"Assets/modelData/tkm/Player_N.tkm",
		"Assets/modelData/tkm/Player_S.tkm"
	};
	const char* tksFilePaths[] = {
		"Assets/modelData/tkm/Player_N.tks",
		"Assets/modelData/tkm/Player_S.tks"
	};
	for (int i = 0; i < enPlayer_Num; i++) {
		//SkinModelRenderをNewGO。
		m_skinModelRender[i] = NewGO<SkinModelRender>(1);
		//tkmファイルをロード。
		m_skinModelRender[i]->SetFileNametkm(tkmFilePaths[i]);
		//tksファイルをロード。
		m_skinModelRender[i]->SetFileNametks(tksFilePaths[i]);
		m_skinModelRender[i]->Init(true, false);
		if (i == enPlayer_1) {
			//プレイヤー1は最初は非アクティブ。
			m_skinModelRender[i]->Deactivate();
		}
	}
	


		//アニメーションを設定。
	//m_skinModelRender->InitAnimation(m_animationClips, enAnimClip_Num);
	//最終的な初期化。

	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	return true;
}
void Player::Update()
{
	//Vector3 moveSpeed;
	//moveSpeed.x = g_pad[0]->GetLStickXF() * -3.0f;
	//moveSpeed.z = g_pad[0]->GetLStickYF() * -3.0f;
	//m_pos = m_charaCon.Execute(moveSpeed, 1.0f);
	//m_skinModelRender->SetPosition(m_pos);
	m_movePower.y -= 0.2f;
	m_movePower.z = 0.0f;
	//m_movePower.x += 2.0f;
	m_pos = m_charaCon.Execute(m_movePower, 1.0f);

	if (m_charaCon.IsOnWall()) {
		m_movePower.x = 0.0f;
	}

	//Vector3 samplePos = m_pos;
	//samplePos.y += 100.0f;
	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	//Aボタンでプレイヤーの磁力を反転させる
	if (g_pad[0]->IsTrigger(enButtonA)) {
		ChangeState();
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