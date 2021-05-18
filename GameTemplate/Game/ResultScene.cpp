#include "stdafx.h"
#include "ResultScene.h"
#include "Game.h"
#include "ResultLevel2D.h"
#include "TitleScene.h"
#include "SaveData.h"

bool ResultScene::Start()
{
	//リザルト画面表示
	sprite = NewGO<ResultLevel2D>(0, "ResultLevel2D");
	m_game = FindGO<Game>("game");

	m_resultLevel2D = FindGO<ResultLevel2D>("ResultLevel2D");

	nowTime = m_game->GetTime();
	bestTime = m_game->GetBestTime();

	if(nowTime < bestTime)
	{
		NewRecordFlg = true;
		bestTime = nowTime;
	}

	m_nowTime = NewGO<FontRender>(2);
	wchar_t text[4][64];
	swprintf_s(text[0], L"%2.1f", nowTime);
	m_nowTime->Init(text[0], { 20.0f,70.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_nowTime->SetScale(1.5f);
	m_nowTime->SetPivot({ 0.0f,0.0f });

	//記録が1桁の時
	if (nowTime < 10) {
		//x座標を調整。
		m_nowTime->SetPosition({ 20.0f,70.0f });	//場所
	}
	//記録が10桁の時
	if (nowTime > 10 && nowTime < 100) {
		//x座標を調整。
		m_nowTime->SetPosition({ -15.0f,70.0f });	//場所
	}
	//記録が100桁の時
	if (nowTime > 100 && nowTime < 1000) {
		//x座標を調整。
		m_nowTime->SetPosition({ -45.0f,70.0f });	//場所
	}

	m_BestTime = NewGO<FontRender>(2);
	swprintf_s(text[1], L"%2.1f", bestTime);
	m_BestTime->Init(text[1], { 20.0f,-30.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_BestTime->SetPivot({ 0.0f,0.0f });
	m_BestTime->SetScale(1.5f);

	//記録が1桁の時
	if (bestTime < 10) {
		//x座標を調整。
		m_BestTime->SetPosition({ 20.0f,-30.0f });	//場所
	}
	//記録が10桁の時
	if (bestTime > 10 && bestTime < 100) {
		//x座標を調整。
		m_BestTime->SetPosition({ -15.0f,-30.0f });	//場所
	}
	//記録が100桁の時
	if (bestTime > 100 && bestTime < 1000) {
		//x座標を調整。
		m_BestTime->SetPosition({ -45.0f,-30.0f });	//場所
	}

	//C++限定のキャスト方法。
	//static_cast<int>(bestTime);

	m_game = FindGO<Game>("game");
	m_time = m_game->GetTime();		//Gameで取得したタイム
	SaveData* savedata = FindGO<SaveData>("savedata");
	savedata->FileSave();	//タイムをセーブする

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
		SoundManager::GetInstance()->Play(SE_CursolMove);
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

		 //大きさが最小になったとき、
		if (Fscale < 0.25f) {
			ScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (Fscale > 0.275f) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//拡大
			Fscale += 0.0005f;
		}
		if (ScaleUpFlag == false) {
			//縮小
			Fscale -= 0.0005f;
		}
		//スプライトに反映。
		Vscale = { Fscale,Fscale,Fscale };
		m_resultLevel2D->GetSprite(8)->SetScale(Vscale);

		//選択されていないボタンの拡大率を元に戻す。
		m_resultLevel2D->GetSprite(9)->SetScale(vscale1);

		break;

	//「しゅうりょう」ボタンが選ばれているとき、
	case EndButton:
		//ボタンを不透明度100％にする。
		m_resultLevel2D->GetSprite(9)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (Fscale1 < 0.2f) {
			ScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (Fscale1 > 0.225f) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//拡大
			Fscale1 += 0.0005f;
		}
		if (ScaleUpFlag == false) {
			//縮小
			Fscale1 -= 0.0005f;
		}
		//スプライトに反映。
		Vscale = { Fscale1,Fscale1,Fscale1 };
		m_resultLevel2D->GetSprite(9)->SetScale(Vscale);

		//選択されていないボタンの拡大率を元に戻す。
		m_resultLevel2D->GetSprite(8)->SetScale(vscale);

		break;
	};


	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。
		SoundManager::GetInstance()->Play(SE_DecisionButton);

		switch (NowSelect) {

			//「たいとる」ボタンが選ばれているとき、
		case TitleBackButton:
			//ゲーム画面に遷移。
			NewGO<TitleScene>(0);

			break;

			//「おわる」ボタンが選ばれているとき、
		case EndButton:
			//ゲームを終了。
			exit(EXIT_SUCCESS);

			break;
		};
		//クラスを削除。
		DeleteGO(this);
	}

	//しんきろく！の文字が流れていく処理
	//if (NewRecordFlg)
	//{
	//	if (NewRecordFlgSub) {
	//		//しんきろく！画像を初期化。
	//		m_spriteRender = NewGO<SpriteRender>(2);
	//		m_spriteRender->SetPosition({ RecordPos,0.0f,0.0f });
	//		m_spriteRender->Init("Assets/image/Record.dds", 750.0f, 750.0f);
	//		NewRecordFlgSub = false;
	//	}
	//	//右から左に移動する処理
	//		m_spriteRender->SetPosition({ RecordPos,0.0f,0.0f });
	//		RecordPos-=5;
	//		//画面外に移動すると無駄に残さずにスプライトを消す
	//		if (RecordPos < -1000.0f)
	//		{
	//			//初期位置に戻す
	//			RecordPos = 1100.0f;
	//		}
	//}
}