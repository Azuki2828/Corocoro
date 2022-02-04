#include "stdafx.h"
#include "ResultScene.h"
#include "Game.h"
#include "ResultLevel2D.h"
#include "TitleScene.h"
#include "SaveData.h"

namespace {
	const float NEW_RECORD_X_POS = 1100.0f;					//新記録！のX座標
	const int RESULT_TEXT_NUM = 2;							//テキストの総数
	const float TEXT_SCALE = 1.5f;							//テキストの拡大率
	const Vector2 TEXT_NOW_TIME_POS = { 20.0f,70.0f };		//今回の記録の座標
	const Vector2 TEXT_BEST_TIME_POS = { 20.0f,-30.0f };	//最高記録の座標
}
bool ResultScene::Start()
{
	//クラスを探し出す
	m_game = FindGO<Game>(NAME_GAME);

	//リザルト画面のレベルを生成。
	m_resultLevel2D = NewGO<ResultLevel2D>(enPriority_Zeroth, NAME_RESULT_LEVEL2D);
	//今回の記録を取得。
	m_nowTime = m_game->GetTime();
	//最高記録を取得。
	m_bestTime = m_game->GetBestTime();

	//最高記録を更新。
	if (m_nowTime < m_bestTime)
	{
		//最高記録だったら新記録！を表示するフラグをたてる
		m_newRecordFlg = true;
		m_bestTime = m_nowTime;
	}

	//今回の記録のテキストを生成。
	m_fontNowTime = NewGO<FontRender>(enPriority_Second);

	//今回の記録のテキストを初期化。
	wchar_t text[RESULT_TEXT_NUM][TEXT_SIZE];
	swprintf_s(text[enPriority_Zeroth], L"%2.1f", m_nowTime);
	m_fontNowTime->Init(text[enData_Zeroth], TEXT_NOW_TIME_POS, TRANSLUCENT_VALUE_MAX);
	m_fontNowTime->SetScale(TEXT_SCALE);
	m_fontNowTime->SetShadowParam(true, TEXT_SHADOW_THICKNESS, Vector4::Black);
	m_fontNowTime->SetPosition({ TEXT_NOW_TIME_POS.x - TEXT_BIT_SIZE * GetDigit(m_nowTime),TEXT_NOW_TIME_POS.y });

	//最高記録のテキストを生成。
	m_fontBestTime = NewGO<FontRender>(enPriority_Second);

	//最高記録のテキストを初期化。
	swprintf_s(text[1], L"%2.1f", m_bestTime);
	m_fontBestTime->Init(text[enData_First], TEXT_BEST_TIME_POS, Vector4::White);
	m_fontBestTime->SetScale(TEXT_SCALE);
	m_fontBestTime->SetShadowParam(true, TEXT_SHADOW_THICKNESS, Vector4::Black);
	m_fontBestTime->SetPosition({ TEXT_BEST_TIME_POS.x - TEXT_BIT_SIZE * GetDigit(m_bestTime), TEXT_BEST_TIME_POS.y });

	

	//セーブデータのクラスを探し出す。
	m_saveData = FindGO<SaveData>(NAME_SAVE_DATA);
	//セーブする
	m_saveData->Save();
	return true;
}

ResultScene::~ResultScene()
{
	//クラスの削除
	DeleteGO(m_fontNowTime);
	DeleteGO(m_fontBestTime);
	DeleteGO(m_resultLevel2D);
}

void ResultScene::Update()
{
	//右入力or左入力されたら、
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonRight) || g_pad[enData_Zeroth]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「たいとる」(0番)だったら、
		if (m_nowSelect == enSelect_TitleBackButton) {
			//選択を右に1つずらす。
			m_nowSelect = enSelect_EndButton;
		}
		//現在セレクトされているボタンが「しゅうりょう」(1番)だったら、
		else {
			//選択を左に1つずらす。
			m_nowSelect = enSelect_TitleBackButton;
		}
		//移動効果音鳴らす。
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}

	//ボタンを全て半透明にする。
	HUD::GetHUD()->SetMulColor(enSprite_TitleButton, TRANSLUCENT_VALUE_HALF);
	HUD::GetHUD()->SetMulColor(enSprite_EndButton, TRANSLUCENT_VALUE_HALF);
	m_standardScale[enSelect_TitleBackButton] = HUD::GetHUD()->GetScale(enSprite_TitleButton);
	m_standardScale[enSelect_EndButton] = HUD::GetHUD()->GetScale(enSprite_EndButton);

	//現在選択しているボタンの強調表示
	switch (m_nowSelect) {

	//「たいとる」ボタンが選ばれているとき、
	case enSelect_TitleBackButton:
		//ボタンを不透明度100％にする。
		HUD::GetHUD()->SetMulColor(enSprite_TitleButton, TRANSLUCENT_VALUE_MAX);

		 //大きさが最小になったとき、
		if (m_fontScale < BACK_BUTTON_SIZE_MIN) {
			m_scaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (m_fontScale > BACK_BUTTON_SIZE_MAX) {
			m_scaleUpFlag = false;
		}

		if (m_scaleUpFlag == true) {
			//拡大
			m_fontScale += BUTTON_SCALE_ADD;
		}
		if (m_scaleUpFlag == false) {
			//縮小
			m_fontScale -= BUTTON_SCALE_ADD;
		}
		//スプライトに反映。
		m_scale = { m_fontScale,m_fontScale,m_fontScale };
		HUD::GetHUD()->SetScale(enSprite_TitleButton, m_scale);

		//選択されていないボタンの拡大率を元に戻す。
		HUD::GetHUD()->SetScale(enSprite_EndButton, m_standardScale[enSelect_EndButton]);

		break;

	//「しゅうりょう」ボタンが選ばれているとき、
	case enSelect_EndButton:
		//ボタンを不透明度100％にする。
		HUD::GetHUD()->SetMulColor(enSprite_EndButton, TRANSLUCENT_VALUE_MAX);

		 //大きさが最小になったとき、
		if (m_fontScale2 < DECISION_BUTTON_SIZE_MIN) {
			m_scaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (m_fontScale2 > DECISION_BUTTON_SIZE_MAX) {
			m_scaleUpFlag = false;
		}

		if (m_scaleUpFlag == true) {
			//拡大
			m_fontScale2 += BUTTON_SCALE_ADD;
		}
		if (m_scaleUpFlag == false) {
			//縮小
			m_fontScale2 -= BUTTON_SCALE_ADD;
		}
		//スプライトに反映。
		m_scale = { m_fontScale2,m_fontScale2,m_fontScale2 };
		HUD::GetHUD()->SetScale(enSprite_EndButton, m_scale);

		//選択されていないボタンの拡大率を元に戻す。
		HUD::GetHUD()->SetScale(enSprite_TitleButton, m_standardScale[enSelect_TitleBackButton]);

		break;
	};


	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。
		SoundManager::GetInstance()->Play(enSE_DecisionButton);

		switch (m_nowSelect) {

			//「たいとる」ボタンが選ばれているとき、
		case enSelect_TitleBackButton:
			//ゲーム画面に遷移。
			NewGO<TitleScene>(enPriority_Zeroth);
			DeleteGO(m_game);
			HUD::GetHUD()->Release();
			if (SoundManager::GetInstance()->IsPlaying(enSE_GameClear)) {
				SoundManager::GetInstance()->Release(enSE_GameClear);
			}
			LightManager::GetInstance()->RemoveLightAll();

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
	//		m_spriteRender->SetPosition({ NEW_RECORD_X_POS,0.0f,0.0f });
	//		m_spriteRender->Init("Assets/image/Record.dds", 750.0f, 750.0f);
	//		NewRecordFlgSub = false;
	//	}
	//	//右から左に移動する処理
	//		m_spriteRender->SetPosition({ NEW_RECORD_X_POS,0.0f,0.0f });
	//		m_recordPos-=5;
	//		//画面外に移動すると無駄に残さずにスプライトを消す
	//		if (m_recordPos < -1000.0f)
	//		{
	//			//初期位置に戻す
	//			m_recordPos = 1100.0f;
	//		}
	//}
}