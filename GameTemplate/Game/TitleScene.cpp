#include "stdafx.h"
#include "TitleScene.h"
#include "TitleLevel2D.h"

#include "Game.h"
#include "RuleScene.h"
#include "SettingScene.h"


bool TitleScene::Start()
{
	//タイトル画面表示
	sprite = NewGO<TitleLevel2D>(0);

	//タイトルBGM再生。

	TitleBGMSound = NewGO<CSoundSource>(0);
	TitleBGMSound->Init(L"Assets/sound/TitleBGM.wav");
	TitleBGMSound->SetVolume(1.0f);
	TitleBGMSound->Play(true);		//ループ再生。

	//Start関数のreturn true;
	return true;
}

TitleScene::~TitleScene()
{
	//タイトル画面のレベルを削除。
	DeleteGO(sprite);
	//タイトルBGMを削除。
	DeleteGO(TitleBGMSound);
}

void TitleScene::Update()
{
	//右入力or左入力されたら、
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「はじめる」(0番)or「せってい」(2番)だったら、
		if (NowSelect % 2 == 0) {
			//選択を右に1つずらす。
			NowSelect += 1;
		}
		//現在セレクトされているボタンが「あそびかた」(1番)or「おわる」(3番)だったら、
		else {
			//選択を左に1つずらす。
			NowSelect -= 1;
		}
	}
	//上入力or下入力されたら、
	if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonUp)) {
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
	}

	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。

		DecisionSound = NewGO<CSoundSource>(0);
		DecisionSound->Init(L"Assets/sound/DecisionButton.wav");
		DecisionSound->SetVolume(1.0f);
		DecisionSound->Play(false);		//1ショット再生。

		switch (NowSelect) {

		 case StartButton:
			//ゲーム画面に遷移。
			NewGO<Game>(0);

			break;

		 case RuleButton:
			//ルール(操作)説明画面に遷移。
			NewGO<RuleScene>(0);

			break;

		 case SettingButton:
			//設定画面に遷移。
			NewGO<SettingScene>(0);

			break;

		 case EndButton:
			//ゲームを終了。

			break;
		};
		//クラスを削除。
		DeleteGO(this);
	}
}