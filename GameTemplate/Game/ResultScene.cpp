#include "stdafx.h"
#include "Resultscene.h"


ResultScene::ResultScene()
{
	m_spriteRender = NewGO<SpriteRender>(3);
	m_spriteRender->Init("Assets/Level2D/BackScreen.dds", 1300.0f, 750.0f);
	m_spriteRender->SetPosition({ 0.0f,0.0f,0.0f });

	//TimeBackスプライトの上に表示させたいからゲーム画面のUIレイヤー1に+1した2にしている。
	m_fontRender = NewGO<FontRender>(4);
	m_fontRender->Init(L"Result", Vector2{ (-300.0f),(300.0f) }, Vector4{(0.0f),(0.0f),(0.0f),(1.0f)},0.0f,5.0f);
	//スケールを5倍にした
}

ResultScene::~ResultScene()
{

}

bool ResultScene::Start()
{


	//Start関数のreturn true;
	return true;
}

void ResultScene::Update()
{

}