#include "stdafx.h"
#include "ResultScene.h"
#include "Game.h"
#include "ResultLevel2D.h"
#include "TitleScene.h"
#include "SaveData.h"

bool ResultScene::Start()
{
	//リザルト画面表示
	m_game = FindGO<Game>(NAME_GAME);
	m_resultLevel2D = NewGO<ResultLevel2D>(0, NAME_RESULT_LEVEL2D);
	m_nowTime = m_game->GetTime();
	m_bestTime = m_game->GetBestTime();
	m_fontNowTime = NewGO<FontRender>(2);
	wchar_t text[4][64];
	swprintf_s(text[0], L"%2.1f", m_nowTime);
	m_fontNowTime->Init(text[0], { 20.0f,70.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_fontNowTime->SetScale(1.5f);
	m_fontNowTime->SetPivot({ 0.0f,0.0f });
	m_fontNowTime->SetShadowParam(true, 1.0f, Vector4::Black);
	//記録が1桁の時
	if (m_nowTime < 10) {
		//x座標を調整。
		m_fontNowTime->SetPosition({ 20.0f,70.0f });	//場所
	}
	//記録が10桁の時
	else if (m_nowTime > 10 && m_nowTime < 100) {
		//x座標を調整。
		m_fontNowTime->SetPosition({ -12.0f,70.0f });	//場所
	}
	//記録が100桁の時
	else if (m_nowTime > 100 && m_nowTime < 1000) {
		//x座標を調整。
		m_fontNowTime->SetPosition({ -44.0f,70.0f });	//場所
	}
	else if (m_nowTime > 1000 && m_nowTime < 10000) {
		//x座標を調整。
		m_fontNowTime->SetPosition({ -76.0f,70.0f });	//場所
	}

	m_fontBestTime = NewGO<FontRender>(2);
	swprintf_s(text[1], L"%2.1f", m_bestTime);
	m_fontBestTime->Init(text[1], { 20.0f,-30.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_fontBestTime->SetPivot({ 0.0f,0.0f });
	m_fontBestTime->SetScale(1.5f);
	m_fontBestTime->SetShadowParam(true, 1.0f, Vector4::Black);
		//記録が1桁の時
	if (m_bestTime < 10) {
		//x座標を調整。
		m_fontBestTime->SetPosition({ 20.0f,-30.0f });	//場所
	}
	//記録が10桁の時
	if (m_bestTime > 10 && m_bestTime < 100) {
		//x座標を調整。
		m_fontBestTime->SetPosition({ -12.0f,-30.0f });	//場所
	}
	//記録が100桁の時
	if (m_bestTime > 100 && m_bestTime < 1000) {
		//x座標を調整。
		m_fontBestTime->SetPosition({ -44.0f,-30.0f });	//場所
	}

	if (m_nowTime < m_bestTime)
	{
		m_newRecordFlg = true;
		//このチームのコードは詳しくないから消さないけど、この１文っているの？
		m_bestTime = m_nowTime;
	}

	m_game = FindGO<Game>(NAME_GAME);
	m_time = m_game->GetTime();		//Gameで取得したタイム
	SaveData* savedata = FindGO<SaveData>(NAME_SAVE_DATA);
	savedata->Save();	//タイムをセーブする
	return true;
}

ResultScene::~ResultScene()
{
	DeleteGO(m_fontNowTime);
	DeleteGO(m_fontBestTime);
	DeleteGO(m_resultLevel2D);
}

void ResultScene::Update()
{
	//右入力or左入力されたら、
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「たいとる」(0番)だったら、
		if (m_nowSelect % 2 == 0) {
			//選択を右に1つずらす。
			m_nowSelect = 1;
		}
		//現在セレクトされているボタンが「しゅうりょう」(1番)だったら、
		else {
			//選択を左に1つずらす。
			m_nowSelect = 0;
		}
		//移動効果音鳴らす。
		SoundManager::GetInstance()->Play(SE_CursolMove);
	}

	//ボタンを全て半透明にする。
	HUD::GetHUD()->SetMulColor(enSprite_TitleButton, { 1.0f, 1.0f, 1.0f, 0.5f });
	HUD::GetHUD()->SetMulColor(enSprite_EndButton, { 1.0f, 1.0f, 1.0f, 0.5f });
	m_standardScale[enSprite_TitleButton] = HUD::GetHUD()->GetScale(enSprite_TitleButton);
	m_standardScale[enSprite_EndButton] = HUD::GetHUD()->GetScale(enSprite_EndButton);

	//現在選択しているボタンの強調表示
	switch (m_nowSelect) {

	//「たいとる」ボタンが選ばれているとき、
	case enSelect_TitleBackButton:
		//ボタンを不透明度100％にする。
		//m_resultLevel2D->GetSprite(8)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		HUD::GetHUD()->SetMulColor(enSprite_TitleButton, { 1.0f, 1.0f, 1.0f, 1.0f });
		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (m_fontScale < 0.25f) {
			m_scaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (m_fontScale > 0.275f) {
			m_scaleUpFlag = false;
		}

		if (m_scaleUpFlag == true) {
			//拡大
			m_fontScale += 0.0005f;
		}
		if (m_scaleUpFlag == false) {
			//縮小
			m_fontScale -= 0.0005f;
		}
		//スプライトに反映。
		m_scale = { m_fontScale,m_fontScale,m_fontScale };
		//m_resultLevel2D->GetSprite(8)->SetScale(m_scale);
		HUD::GetHUD()->SetScale(enSprite_TitleButton, m_scale);

		//選択されていないボタンの拡大率を元に戻す。
		HUD::GetHUD()->SetScale(enSprite_EndButton, m_standardScale[enSprite_EndButton]);

		break;

	//「しゅうりょう」ボタンが選ばれているとき、
	case enSelect_EndButton:
		//ボタンを不透明度100％にする。
		HUD::GetHUD()->SetMulColor(enSprite_EndButton, { 1.0f, 1.0f, 1.0f, 1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (m_fontScale2 < 0.2f) {
			m_scaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (m_fontScale2 > 0.225f) {
			m_scaleUpFlag = false;
		}

		if (m_scaleUpFlag == true) {
			//拡大
			m_fontScale2 += 0.0005f;
		}
		if (m_scaleUpFlag == false) {
			//縮小
			m_fontScale2 -= 0.0005f;
		}
		//スプライトに反映。
		m_scale = { m_fontScale2,m_fontScale2,m_fontScale2 };
		HUD::GetHUD()->SetScale(enSprite_EndButton, m_scale);

		//選択されていないボタンの拡大率を元に戻す。
		HUD::GetHUD()->SetScale(enSprite_TitleButton, m_standardScale[enSprite_TitleButton]);

		break;
	};


	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。
		SoundManager::GetInstance()->Play(SE_DecisionButton);

		switch (m_nowSelect) {

			//「たいとる」ボタンが選ばれているとき、
		case enSelect_TitleBackButton:
			//ゲーム画面に遷移。
			NewGO<TitleScene>(0);
			DeleteGO(m_game);
			HUD::GetHUD()->Release();
			if (SoundManager::GetInstance()->IsPlaying(SE_GameClear)) {
				SoundManager::GetInstance()->Release(SE_GameClear);
			}

			break;

			//「おわる」ボタンが選ばれているとき、
		case enSelect_EndButton:
			//ゲームを終了。
			exit(EXIT_SUCCESS);

			break;
		};
		//クラスを削除。
		DeleteGO(this);
	}

	//しんきろく！の文字が流れていく処理

	//if (m_newRecordFlg)
	//{
	//	if (m_newRecordFlgSub) {
	//		//しんきろく！画像を初期化。
	//		m_spriteRender = NewGO<SpriteRender>(2);
	//		m_spriteRender->SetPosition({ RecordPos,0.0f,0.0f });
	//		m_spriteRender->Init("Assets/image/Record.dds", 750.0f, 750.0f);
	//		NewRecordFlgSub = false;
	//	}
	//	//右から左に移動する処理
	//		m_spriteRender->SetPosition({ m_recordPos,0.0f,0.0f });
	//		m_recordPos-=5;
	//		//画面外に移動すると無駄に残さずにスプライトを消す
	//		if (m_recordPos < -1000.0f)
	//		{
	//			//初期位置に戻す
	//			m_recordPos = 1100.0f;
	//		}
	//}
}