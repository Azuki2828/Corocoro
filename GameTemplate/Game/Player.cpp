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

	//キャラコンの初期化。
	m_charaCon.Init(50.0f, 100.0f, m_pos);

	//プレイヤーのtkmとtksをロードする種。
	const char* tkmFilePaths[] = {
		"Assets/modelData/tkm/Player_N.tkm",
		"Assets/modelData/tkm/Player_S.tkm"
	};
	const char* tksFilePaths[] = {
		"Assets/modelData/tkm/Player_N.tks",
		"Assets/modelData/tkm/Player_S.tks"
	};

	//プレイヤーの初期化。
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

	//座標を登録。
	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	return true;
}
void Player::Update()
{
	//重力を設定。
	m_movePower.y -= 0.2f;

	//z方向には動かない。
	m_movePower.z = 0.0f;

	//座標を設定。
	m_pos = m_charaCon.Execute(m_movePower, 1.0f);

	//壁に当たっているなら
	if (m_charaCon.IsOnWall()) {

		//1/2の力で跳ね返る。
		m_movePower.x *= -0.5f;
	}

	//地面上にいるなら
	if (m_charaCon.IsOnGround()) {

		//右に動いてたら
		if (m_movePower.x >= 0.0f) {
			//摩擦。
			m_movePower.x -= 0.02f;
			//もし減らしすぎたら０にする。
			if (m_movePower.x < 0.0f) {
				m_movePower.x = 0.0f;
			}
		}//左に動いてたら
		else {
			//摩擦。
			m_movePower.x += 0.02f;
			//もし増やしすぎたら０にする。
			if (m_movePower.x > 0.0f) {
				m_movePower.x = 0.0f;
			}
		}

	}
	
	//座標を登録。
	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	//Aボタンでプレイヤーの磁力を反転させる
	if (g_pad[0]->IsTrigger(enButtonA)) {
		ChangeState();

		//アクティブフラグを更新。
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