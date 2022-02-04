#include "stdafx.h"
#include "TitleScene.h"
#include "TitleLevel2D.h"
#include "Game.h"
#include "StageSelect.h"
#include "RuleScene.h"
#include "SettingScene.h"

namespace {
	const Vector3 DEFAULT_SPRITE_SCALE = { 0.2f,0.2f,0.2f };	//デフォルトのボタンの拡大率。
}
bool TitleScene::Start()
{

	m_ButtonScale = DEFAULT_SPRITE_SCALE.x;

	

	//タイトル画面表示
	m_titleLevel2D = NewGO<TitleLevel2D>(enPriority_Zeroth, NAME_TITLE_LEVEL2D);

	//タイトルBGM再生。
	SoundManager::GetInstance()->Play(enBGM_Title);
	//TitleBGMSound = NewGO<CSoundSource>(0);
	//TitleBGMSound->Init(L"Assets/sound/TitleBGM.wav");
	//TitleBGMSound->SetVolume(1.0f);
	//TitleBGMSound->Play(true);		//ループ再生。

	//Start関数のreturn true;
	return true;
}

TitleScene::~TitleScene()
{
	//タイトル画面のレベルを削除。
	DeleteGO(m_titleLevel2D);
	//タイトルBGMを削除。
	SoundManager::GetInstance()->Release(enBGM_Title);
}

void TitleScene::Update()
{
	//ボタンを全て半透明にする。
	m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);
	m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);
	m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);

	//右入力or左入力されたら、
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonRight) || g_pad[enData_Zeroth]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「はじめる」(0番)or「せってい」(2番)だったら、
		switch (m_nowSelect) {
		case StartButton:
			m_nowSelect = RuleButton;
			break;
		case RuleButton:
			m_nowSelect = StartButton;
			break;
		case EndButton:
			break;
		}
		//現在セレクトされているボタンが「あそびかた」(1番)or「しゅうりょう」(3番)だったら、
		//else {
		//	//選択を左に1つずらす。
		//	NowSelect -= 1;
		//}
		
		//移動効果音鳴らす。
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}
	//上入力or下入力されたら、
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonUp) || g_pad[enData_Zeroth]->IsTrigger(enButtonDown)) {
		//現在セレクトされているボタンが「はじめる」(0番)or「あそびかた」(1番)だったら、
		if (m_nowSelect < EndButton) {
			//選択を真下に1つずらす。
			m_nowSelect = EndButton;
		}
		//現在セレクトされているボタンが「せってい」(2番)or「おわる」(3番)だったら、
		else {
			//選択を真上にずらす。
			m_nowSelect = RuleButton;
		}

		//移動効果音鳴らす。
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}



  //現在選択しているボタンの強調表示
	switch (m_nowSelect) {

	 //「はじめる」ボタンが選ばれているとき、
	 case StartButton:
		 //ボタンを不透明度100％にする。
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);


		  //大きさが最小になったとき、
		 if (m_ButtonScale < TITLE_SELECT_BUTTON_SCALE_MIN) {
			 m_scaleUpFlag = true;
		 }
		 //大きさが最大になったとき、
		 if (m_ButtonScale > TITLE_SELECT_BUTTON_SCALE_MAX) {
			 m_scaleUpFlag = false;
		 }

		 if (m_scaleUpFlag == true) {
			 //拡大
			 m_ButtonScale += BUTTON_SCALE_ADD;
		 }
		 if (m_scaleUpFlag == false) {
			 //縮小
			 m_ButtonScale -= BUTTON_SCALE_ADD;
		 }
		 //スプライトに反映。
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetScale({ m_ButtonScale,m_ButtonScale,m_ButtonScale });

		 //選択されていないボタンの拡大率を元に戻す。
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetScale(DEFAULT_SPRITE_SCALE);
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetScale(DEFAULT_SPRITE_SCALE);

		break;

	 //「あそびかた」ボタンが選ばれているとき、
	 case RuleButton:
		 //ボタンを不透明度100％にする。
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		 //単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		 if (m_ButtonScale < TITLE_SELECT_BUTTON_SCALE_MIN) {
			 m_scaleUpFlag = true;
		 }
		 //大きさが最大になったとき、
		 if (m_ButtonScale > TITLE_SELECT_BUTTON_SCALE_MAX) {
			 m_scaleUpFlag = false;
		 }

		 if (m_scaleUpFlag == true) {
			 //拡大
			 m_ButtonScale += BUTTON_SCALE_ADD;
		 }
		 if (m_scaleUpFlag == false) {
			 //縮小
			 m_ButtonScale -= BUTTON_SCALE_ADD;
		 }
		 //スプライトに反映。
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetScale({ m_ButtonScale,m_ButtonScale,m_ButtonScale });

		 //選択されていないボタンの拡大率を元に戻す。
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetScale(DEFAULT_SPRITE_SCALE);
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetScale(DEFAULT_SPRITE_SCALE);

		break;

	 //「しゅうりょう」ボタンが選ばれているとき、
	 case EndButton:
		 //ボタンを不透明度100％にする。
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		 //大きさが最小になったとき、
		 if (m_ButtonScale < TITLE_SELECT_BUTTON_SCALE_MIN) {
			 m_scaleUpFlag = true;
		 }
		 //大きさが最大になったとき、
		 if (m_ButtonScale > TITLE_SELECT_BUTTON_SCALE_MAX) {
			 m_scaleUpFlag = false;
		 }

		 if (m_scaleUpFlag == true) {
			 //拡大
			 m_ButtonScale += BUTTON_SCALE_ADD;
		 }
		 if (m_scaleUpFlag == false) {
			 //縮小
			 m_ButtonScale -= BUTTON_SCALE_ADD;
		 }
		 //スプライトに反映。
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetScale({ m_ButtonScale,m_ButtonScale,m_ButtonScale });

		 //選択されていないボタンの拡大率を元に戻す。
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetScale(DEFAULT_SPRITE_SCALE);
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetScale(DEFAULT_SPRITE_SCALE);


		break;
	};


	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。

		SoundManager::GetInstance()->Play(enSE_DecisionButton);

		switch (m_nowSelect) {

			//「はじめる」ボタンが選ばれているとき、
		case StartButton:
			//ステージセレクト画面に遷移。
			NewGO<StageSelect>(enPriority_Zeroth, NAME_STAGE_SELECT);

			break;

			//「あそびかた」ボタンが選ばれているとき、
		case RuleButton:
			//ルール(操作)説明画面に遷移。
			NewGO<RuleScene>(enPriority_Zeroth, NAME_RULE_SCENE);

			break;

			//「おわる」ボタンが選ばれているとき、
		case EndButton:
			//ゲームを終了。
			exit(EXIT_SUCCESS);

			break;
		};
		//クラスを削除。
		DeleteGO(this);
	};
}