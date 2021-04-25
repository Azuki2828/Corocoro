#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "GameTime.h"
#include "MainCamera.h"
#include "Key.h"
#include "GameTime.h"
#include "SaveData.h"
#include "ResultScene.h"

bool Game::Start() {


	m_gameStartTime = 3.0f / g_graphicsEngine->GetGraphicTime();

	//セーブを追加
	m_savedata = NewGO<SaveData>(0, "savedata");
	//m_savedata->FileSave();
	m_savedata->Load();



	m_dirLight = NewGO<DirectionLight>(0);
	m_dirLight->SetLigDirection();
	m_dirLight->SetLigColor();
	//カメラを生成。
	m_camera = NewGO<MainCamera>(0);
	//プレイヤーを生成。
	m_player = NewGO<Player>(0, "player");
	//地形を生成。
	m_backGround = NewGO<Background>(0, "background");
	//フォントレンダーを生成
	m_fontRender = NewGO<FontRender>(2);
	//時間経過を表示
	m_fontRender->Init(L"Time", { -520.0f,310.0f });	//場所
	m_fontRender->SetColor({ 1.0f,1.0f,1.0f,1.0f });	//色
	m_fontRender->SetPivot({ 1.0f, 0.0f });				//中心を右側に

	//m_recordfontRender = NewGO<FontRender>(2);
	wchar_t text[64];
	swprintf_s(text, L"%2.1f", m_savedata->Data.record);
	//m_recordfontRender->Init(text);
	//m_recordfontRender->SetText(text);
	//m_recordfontRender->SetPosition({ 500.0f, 300.0f });




	return true;
}

Game::~Game()
{
	DeleteGO(m_savedata);
	DeleteGO(m_dirLight);
	DeleteGO(m_player);
	DeleteGO(m_backGround);
	DeleteGO(m_camera);
	DeleteGO(m_fontRender);
	DeleteGO(m_recordfontRender);
}

void Game::Update() {
	//カメラのスクロールが終わってプレイヤーの視点になる。且つ、ワンショット再生させるためのフラグ。
	if (m_camera->CameraScrollFlag == false&& m_startsoundflg == true) {
		m_sound = NewGO<CSoundSource>(0);

		m_sound->Init(L"Assets/sound/CountDown.wav");	//３、２、１、スタート！カウントダウン効果音
		m_sound->SetVolume(1.0f);
		m_sound->Play(false);
		m_startsoundflg = false;

		KauntoDownSprite = true;
	}

	//カウントダウンが鳴りだしたら、
	if (KauntoDownSprite == true) {
		//カウントダウンスプライトを表示。
		switch (KauntoDownTimer) {
		 case 0:
			//「3」表示
			m_sprite[0] = NewGO<SpriteRender>(1);
			m_sprite[0]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[0]->Init("Assets/image/3.dds", 1000.0f, 1000.0f);

			break;

		 case 60:
			//「3」削除。
			DeleteGO(m_sprite[0]);

			//「2」表示
			m_sprite[1] = NewGO<SpriteRender>(1);
			m_sprite[1]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[1]->Init("Assets/image/2.dds", 1000.0f, 1000.0f);

			break;

		 case 120:
			//「2」削除。
			DeleteGO(m_sprite[1]);

			//「1」表示
			m_sprite[2] = NewGO<SpriteRender>(1);
			m_sprite[2]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[2]->Init("Assets/image/1.dds", 1000.0f, 1000.0f);

			break;

		 case 180:
			//「1」削除。
			DeleteGO(m_sprite[2]);

			//「GO!!」表示
			m_sprite[3] = NewGO<SpriteRender>(1);
			m_sprite[3]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[3]->Init("Assets/image/GO.dds", 1000.0f, 1000.0f);

			break;

		 case 300:
			//「GO!!」削除。
			DeleteGO(m_sprite[3]);

			KauntoDownSprite = false;

			break;
		}

		KauntoDownTimer++;

	}

	wchar_t text1[64];

	//スタートの効果音が鳴り終わったら
	if (m_startsoundflg == false) {
		m_timer += GameTime::GameTimeFunc().GetFrameDeltaTime();		//タイム計測開始のためのタイム
	}
	if (m_timer >= m_gameStartTime && doorbreakSoundFlg == true) {
		m_time += GameTime::GameTimeFunc().GetFrameDeltaTime();
	}

	//タイム文字表示
	swprintf_s(text1, L"%2.1f", m_time);
	m_fontRender->SetText(text1);


	if (m_player->GetdoorbreakFlg() == true && doorbreakSoundFlg == true) {
		doorbreakSoundFlg = false;			//ゴールしたら計測終了
		NewGO<ResultScene>(0,"resultscene");
	}
}