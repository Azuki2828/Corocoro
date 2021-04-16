#include "stdafx.h"
#include "Resultscene.h"


ResultScene::ResultScene()
{
	m_spriteRender = NewGO<SpriteRender>(5);
	m_spriteRender->Init("Assets/Level2D/TimeBack.dds", 1080.0f, 720.0f);
	m_spriteRender->SetPosition({ 0.0f,0.0f,0.0f });
}

ResultScene::~ResultScene()
{

}

bool ResultScene::Start()
{


	//StartŠÖ”‚Ìreturn true;
	return true;
}

void ResultScene::Update()
{

}