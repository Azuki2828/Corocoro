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
	//�X�v���C�g���������B
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/Image/ehehe.dds", 1000, 1000);

	return true;
}

void TitleScene::Update()
{
	if (g_pad[0]->IsPress(enButtonA) == true) {
		//A�{�^���������ꂽ��C���Q�[��
			//�v���C���[�𐶐��B
		NewGO<Player>(0, "player");
		//�J�����𐶐��B
		NewGO<MainCamera>(0);
		//�w�i�𐶐��B
		NewGO<Background>(0);

		DeleteGO(this);
	}
}