#include "stdafx.h"
#include "TitleScene.h"
#include "Game.h"
#include "TitleLevel2D.h"

bool TitleScene::Start()
{
	//�^�C�g����ʕ\��
	sprite = NewGO<TitleLevel2D>(0);

	//�^�C�g��BGM�Đ��B

	TitleBGMSound = NewGO<CSoundSource>(0);

	TitleBGMSound->Init(L"Assets/sound/TitleBGM.wav");
	TitleBGMSound->SetVolume(1.0f);
	TitleBGMSound->Play(true);		//���[�v�Đ��B

	//m_spriteRender = NewGO<SpriteRender>(0);
	//m_spriteRender->Init("Assets/Level2D/TimeBack.dds", 1080.0f, 720.0f);
	//m_spriteRender->SetPosition({ 0.0f,0.0f,0.0f });


	//Start�֐���return true;
	return true;
}



TitleScene::~TitleScene()
{
	//��ʂ̃X�v���C�g���폜�B
	DeleteGO(sprite);
	//�^�C�g��BGM���폜�B
	DeleteGO(TitleBGMSound);
}

void TitleScene::Update()
{
	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonA)) {
		//�Q�[����ʂɑJ��
		NewGO<Game>(0);
		//�N���X���폜�B
		DeleteGO(this);
	}
}