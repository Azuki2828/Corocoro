#include "stdafx.h"
#include "Resultscene.h"


bool ResultScene::Start()
{
	m_spriteRender = NewGO<SpriteRender>(3);
	m_spriteRender->Init("Assets/Level2D/BackScreen.dds", 1300.0f, 750.0f);
	m_spriteRender->SetPosition({ 0.0f,0.0f,0.0f });


	//StartŠÖ”‚Ìreturn true;
	return true;
}

ResultScene::~ResultScene()
{

}

void ResultScene::Update()
{

}