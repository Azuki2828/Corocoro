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

	//m_spriteRender = NewGO<SpriteRender>(0);
	//m_spriteRender->Init("Assets/Level2D/TimeBack.dds", 1080.0f, 720.0f);
	//m_spriteRender->SetPosition({ 0.0f,0.0f,0.0f });


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
		//ゲーム画面に遷移
		NewGO<Game>(0);
		//クラスを削除。
		DeleteGO(this);
	}
}