#include "stdafx.h"
#include "TitleScene.h"
#include "Player.h"
#include "MainCamera.h"
#include "Background.h"

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{
	DeleteGO(m_spriteRender);
}

bool TitleScene::Start()
{
	//スプライトを初期化。
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/Image/ehehe.dds", 1000, 1000);

	return true;
}

void TitleScene::Update()
{
	if (g_pad[0]->IsPress(enButtonA) == true) {
		//Aボタンが押されたらインゲーム
			//プレイヤーを生成。
		NewGO<Player>(0, "player");
		//カメラを生成。
		NewGO<MainCamera>(0);
		//背景を生成。
		NewGO<Background>(0);

		DeleteGO(this);
	}
}