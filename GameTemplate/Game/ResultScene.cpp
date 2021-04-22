#include "stdafx.h"
#include "Resultscene.h"
#include "Game.h"
#include "ResultLevel2D.h"
#include "TitleScene.h"


bool ResultScene::Start()
{
	//リザルト画面表示
	sprite = NewGO<ResultLevel2D>(0, "ResultLevel2D");
	m_game = FindGO<Game>("game");

	m_resultLevel2D = FindGO<ResultLevel2D>("ResultLevel2D");

	nowTime = m_game->GetTime();
	bestTime = m_game->GetBestTime();

	m_nowTime = NewGO<FontRender>(3);
	wchar_t text[4][64];
	swprintf_s(text[0], L"%2.1f", nowTime);
	m_nowTime->Init(text[0], { -20.0f,70.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_nowTime->SetScale(1.5f);
	m_nowTime->SetPivot({ 0.0f,0.0f });
	m_BestTime = NewGO<FontRender>(3);
	swprintf_s(text[1], L"%2.1f", bestTime);
	m_BestTime->Init(text[1], { -20.0f,-30.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_BestTime->SetPivot({ 0.0f,0.0f });
	m_BestTime->SetScale(1.5f);

	//Start関数のreturn true;
	return true;
}

ResultScene::~ResultScene()
{
	DeleteGO(sprite);
}

void ResultScene::Update()
{
	//右入力or左入力されたら、
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「たいとる」(0番)だったら、
		if (NowSelect % 2 == 0) {
			//選択を右に1つずらす。
			NowSelect = 1;
		}
		//現在セレクトされているボタンが「しゅうりょう」(1番)だったら、
		else {
			//選択を左に1つずらす。
			NowSelect = 0;
		}
		//移動効果音鳴らす。
		CursorMooveSound = NewGO<CSoundSource>(0);
		CursorMooveSound->Init(L"Assets/sound/CursorMoove.wav");
		CursorMooveSound->SetVolume(1.0f);
		CursorMooveSound->Play(false);		//ワンショット再生。
	}

	//ボタンを全て半透明にする。
	for (int i = 8; i <10 ; i++) {
		m_resultLevel2D->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

	//現在選択しているボタンの強調表示
	switch (NowSelect) {

	//「たいとる」ボタンが選ばれているとき、
	case TitleBackButton:
		//ボタンを不透明度100％にする。
		m_resultLevel2D->GetSprite(8)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		break;

	//「しゅうりょう」ボタンが選ばれているとき、
	case EndButton:
		//ボタンを不透明度100％にする。
		m_resultLevel2D->GetSprite(9)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		break;
	};


	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。

		DecisionSound = NewGO<CSoundSource>(0);
		DecisionSound->Init(L"Assets/sound/DecisionButton.wav");
		DecisionSound->SetVolume(1.0f);
		DecisionSound->Play(false);		//1ショット再生。

		switch (NowSelect) {

			//「たいとる」ボタンが選ばれているとき、
		case TitleBackButton:
			//ゲーム画面に遷移。
			//NewGO<TitleScene>(0);

			break;

			//「おわる」ボタンが選ばれているとき、
		case EndButton:
			//ゲームを終了。
			exit(EXIT_SUCCESS);

			break;
		};
		//クラスを削除。
		//DeleteGO(this);
	}
}