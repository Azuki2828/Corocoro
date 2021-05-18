#include "stdafx.h"
#include "TitleScene.h"
#include "TitleLevel2D.h"
#include "Game.h"
#include "StageSelect.h"
#include "RuleScene.h"
#include "SettingScene.h"


bool TitleScene::Start()
{

	//タイトル画面表示
	sprite = NewGO<TitleLevel2D>(0,"titleLevel2D");

	m_titleLevel2D = FindGO<TitleLevel2D>("titleLevel2D");

	//タイトルBGM再生。
	SoundManager::GetInstance()->Play(BGM_Title);
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
	DeleteGO(sprite);
	//タイトルBGMを削除。
	SoundManager::GetInstance()->Release(BGM_Title);
}

void TitleScene::Update()
{
	//ボタンを全て半透明にする。
	for (int i = 2; i < 6; i++) {
		m_titleLevel2D->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

	//右入力or左入力されたら、
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「はじめる」(0番)or「せってい」(2番)だったら、
		if (NowSelect % 2 == 0) {
			//選択を右に1つずらす。
			NowSelect += 1;
		}
		//現在セレクトされているボタンが「あそびかた」(1番)or「しゅうりょう」(3番)だったら、
		else {
			//選択を左に1つずらす。
			NowSelect -= 1;
		}
		//移動効果音鳴らす。

		SoundManager::GetInstance()->Play(SE_CursolMove);
	}
	//上入力or下入力されたら、
	if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonDown)) {
		//現在セレクトされているボタンが「はじめる」(0番)or「あそびかた」(1番)だったら、
		if (NowSelect < 2) {
			//選択を真下に1つずらす。
			NowSelect += 2;
		}
		//現在セレクトされているボタンが「せってい」(2番)or「おわる」(3番)だったら、
		else {
			//選択を真上にずらす。
			NowSelect -= 2;
		}
		//移動効果音鳴らす。

		SoundManager::GetInstance()->Play(SE_CursolMove);
		//CursorMooveSound = NewGO<CSoundSource>(0);
		//CursorMooveSound->Init(L"Assets/sound/CursorMove.wav");
		//CursorMooveSound->SetVolume(1.0f);
		//CursorMooveSound->Play(false);		//ワンショット再生。
	}



  //現在選択しているボタンの強調表示
	switch (NowSelect) {

	 //「はじめる」ボタンが選ばれているとき、
	 case StartButton:
		 //ボタンを不透明度100％にする。
		 m_titleLevel2D->GetSprite(2)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		 //単振動の公式を使ってボタンを拡大縮小する。

		  //大きさが最小になったとき、
		 if (Fscale < 0.20f) {
			 ScaleUpFlag = true;
		 }
		 //大きさが最大になったとき、
		 if (Fscale > 0.225f) {
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
		 m_titleLevel2D->GetSprite(2)->SetScale(Vscale);

		 //選択されていないボタンの拡大率を元に戻す。
		 m_titleLevel2D->GetSprite(3)->SetScale(vscale);
		 m_titleLevel2D->GetSprite(4)->SetScale(vscale);
		 m_titleLevel2D->GetSprite(5)->SetScale(vscale);

		break;

	 //「あそびかた」ボタンが選ばれているとき、
	 case RuleButton:
		 //ボタンを不透明度100％にする。
		 m_titleLevel2D->GetSprite(3)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		 //単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		 if (Fscale < 0.20f) {
			 ScaleUpFlag = true;
		 }
		 //大きさが最大になったとき、
		 if (Fscale > 0.225f) {
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
		 m_titleLevel2D->GetSprite(3)->SetScale(Vscale);

		 //選択されていないボタンの拡大率を元に戻す。
		 m_titleLevel2D->GetSprite(2)->SetScale(vscale);
		 m_titleLevel2D->GetSprite(4)->SetScale(vscale);
		 m_titleLevel2D->GetSprite(5)->SetScale(vscale);

		break;

	 //「せってい」ボタンが選ばれているとき、
	 case SettingButton:
		 //ボタンを不透明度100％にする。
		 m_titleLevel2D->GetSprite(4)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		 if (Fscale < 0.20f) {
			 ScaleUpFlag = true;
		 }
		 //大きさが最大になったとき、
		 if (Fscale > 0.225f) {
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
		 m_titleLevel2D->GetSprite(4)->SetScale(Vscale);

		 //選択されていないボタンの拡大率を元に戻す。
		 m_titleLevel2D->GetSprite(2)->SetScale(vscale);
		 m_titleLevel2D->GetSprite(3)->SetScale(vscale);
		 m_titleLevel2D->GetSprite(5)->SetScale(vscale);

		break;

	 //「しゅうりょう」ボタンが選ばれているとき、
	 case EndButton:
		 //ボタンを不透明度100％にする。
		 m_titleLevel2D->GetSprite(5)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		   //大きさが最小になったとき、
		 if (Fscale < 0.20f) {
			 ScaleUpFlag = true;
		 }
		 //大きさが最大になったとき、
		 if (Fscale > 0.225f) {
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
		 m_titleLevel2D->GetSprite(5)->SetScale(Vscale);

		 //選択されていないボタンの拡大率を元に戻す。
		 m_titleLevel2D->GetSprite(2)->SetScale(vscale);
		 m_titleLevel2D->GetSprite(3)->SetScale(vscale);
		 m_titleLevel2D->GetSprite(4)->SetScale(vscale);


		break;
	};


	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。

		SoundManager::GetInstance()->Play(SE_DecisionButton);

		switch (NowSelect) {

		 //「はじめる」ボタンが選ばれているとき、
		 case StartButton:
			//ステージセレクト画面に遷移。
			NewGO<StageSelect>(0,"stageselect");

			break;

		 //「あそびかた」ボタンが選ばれているとき、
		 case RuleButton:
			//ルール(操作)説明画面に遷移。
			NewGO<RuleScene>(0,"rule");

			break;

		 //「せってい」ボタンが選ばれているとき、
		 case SettingButton:
			//設定画面に遷移。
			NewGO<SettingScene>(0);

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
}