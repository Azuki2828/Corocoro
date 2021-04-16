#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "GameTime.h"
#include "MainCamera.h"
#include "Key.h"
#include "GameTime.h"

bool Game::Start() {

	m_dirLight = NewGO<DirectionLight>(0);
	m_dirLight->SetLigDirection();
	m_dirLight->SetLigColor();
	//プレイヤーを生成。
	m_player = NewGO<Player>(0, "player");
	//地形を生成。
	m_backGround = NewGO<Background>(0,"background");
	//カメラを生成。
	m_camera = NewGO<MainCamera>(0);
	//フォントレンダーを生成
	m_fontRender = NewGO<FontRender>(2);
	//時間経過を表示
	m_fontRender->Init(L"Time", { .0f,0.0f });


	

	
	return true;
}

void Game::Update() {

	if (m_startsoundflg == true) {
		m_sound = NewGO<CSoundSource>(0);

		m_sound->Init(L"Assets/sound/CountDown.wav");	//スターと開始時の効果音
		m_sound->SetVolume(1.0f);
		m_sound->Play(false);
		m_startsoundflg = false;
	}
	
	wchar_t text1[4][64];
	
	
	m_timer++;		//スタートの効果音が鳴り終わったらタイム計測開始のためのタイム
	if (m_timer >= 200 && doorbreakSoundFlg == true) {
		time += GameTime::GameTimeFunc().GetFrameDeltaTime();
	}

	swprintf_s(text1[0], L"Time : %2.1f", time);
	m_fontRender->SetText(text1[0]);
	m_fontRender->SetPosition({ 350.0f, 350.0f });
	

	if (m_player->GetdoorbreakFlg() == true && doorbreakSoundFlg == true) {		
		doorbreakSoundFlg = false;			//ゴールしたら計測終了

	}
		
}