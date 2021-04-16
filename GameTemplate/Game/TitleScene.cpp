#include "stdafx.h"
#include "TitleScene.h"
#include "Game.h"
#include "TitleLevel2D.h"

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
	//画面のスプライトを削除。
	DeleteGO(sprite);
	//タイトルBGMを削除。
	DeleteGO(TitleBGMSound);
}

void TitleScene::Update()
{
	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。

		DecisionSound = NewGO<CSoundSource>(0);
		DecisionSound->Init(L"Assets/sound/DecisionButton.wav");
		DecisionSound->SetVolume(1.0f);
		DecisionSound->Play(false);		//ループ再生。


		//ゲーム画面に遷移
		NewGO<Game>(0);
		//クラスを削除。
		DeleteGO(this);
	}
}