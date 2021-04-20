#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "GameTime.h"
#include "MainCamera.h"
#include "Key.h"
#include "GameTime.h"
#include "Result.h"
#include "SaveData.h"

bool Game::Start() {


	//セーブを追加
	m_savedata = NewGO<SaveData>(0,"savedata");
	//m_savedata->FileSave();
	m_savedata->Load();
	


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
	m_recordfontRender = NewGO<FontRender>(2);
	wchar_t text[64];
	swprintf_s(text, L"%2.1f", m_savedata->Data.record);
	m_recordfontRender->Init(text);
	m_recordfontRender->SetText(text);
	m_recordfontRender->SetPosition({ 500.0f, 300.0f });
	
	

	
	return true;
}

Game::~Game()
{

}

void Game::Update() {

	if (m_startsoundflg == true) {
		m_sound = NewGO<CSoundSource>(0);

		m_sound->Init(L"Assets/sound/CountDown.wav");	//スターと開始時の効果音
		m_sound->SetVolume(1.0f);
		m_sound->Play(false);
		m_startsoundflg = false;
	}
	/*if (m_startsoundflg == false) {
		m_player = NewGO<Player>(0, "player");			//スターと開始時の効果音が終わったらプレイヤーを追加したい。
	}
	*/
	
	wchar_t text1[4][64];
	
	
	
	m_timer++;		//スタートの効果音が鳴り終わったらタイム計測開始のためのタイム
	if (m_timer >= 190 && doorbreakSoundFlg == true) {
		m_time += GameTime::GameTimeFunc().GetFrameDeltaTime();
	}

	swprintf_s(text1[0], L"Time : %2.1f", m_time);
	m_fontRender->SetText(text1[0]);

	m_fontRender->SetPosition({ 0.0f, 350.0f });
	

	if (m_player->GetdoorbreakFlg() == true && doorbreakSoundFlg == true) {		
		doorbreakSoundFlg = false;			//ゴールしたら計測終了
		NewGO<Result>(0,"result");
	}
		
}