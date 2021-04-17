#include "stdafx.h"
#include "TitleScene.h"
#include "TitleLevel2D.h"

#include "Game.h"
#include "RuleScene.h"
#include "SettingScene.h"


bool TitleScene::Start()
{
	//�^�C�g����ʕ\��
	sprite = NewGO<TitleLevel2D>(0);

	//�^�C�g��BGM�Đ��B

	TitleBGMSound = NewGO<CSoundSource>(0);
	TitleBGMSound->Init(L"Assets/sound/TitleBGM.wav");
	TitleBGMSound->SetVolume(1.0f);
	TitleBGMSound->Play(true);		//���[�v�Đ��B

	//Start�֐���return true;
	return true;
}

TitleScene::~TitleScene()
{
	//�^�C�g����ʂ̃��x�����폜�B
	DeleteGO(sprite);
	//�^�C�g��BGM���폜�B
	DeleteGO(TitleBGMSound);
}

void TitleScene::Update()
{
	//�E����or�����͂��ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//���݃Z���N�g����Ă���{�^�����u�͂��߂�v(0��)or�u�����Ă��v(2��)��������A
		if (NowSelect % 2 == 0) {
			//�I�����E��1���炷�B
			NowSelect += 1;
		}
		//���݃Z���N�g����Ă���{�^�����u�����т����v(1��)or�u�����v(3��)��������A
		else {
			//�I��������1���炷�B
			NowSelect -= 1;
		}
	}
	//�����or�����͂��ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonUp)) {
		//���݃Z���N�g����Ă���{�^�����u�͂��߂�v(0��)or�u�����т����v(1��)��������A
		if (NowSelect < 2) {
			//�I����^����1���炷�B
			NowSelect += 2;
		}
		//���݃Z���N�g����Ă���{�^�����u�����Ă��v(2��)or�u�����v(3��)��������A
		else {
			//�I����^��ɂ��炷�B
			NowSelect -= 2;
		}
	}

	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//����{�^�����Đ��B

		DecisionSound = NewGO<CSoundSource>(0);
		DecisionSound->Init(L"Assets/sound/DecisionButton.wav");
		DecisionSound->SetVolume(1.0f);
		DecisionSound->Play(false);		//1�V���b�g�Đ��B

		switch (NowSelect) {

		 case StartButton:
			//�Q�[����ʂɑJ�ځB
			NewGO<Game>(0);

			break;

		 case RuleButton:
			//���[��(����)������ʂɑJ�ځB
			NewGO<RuleScene>(0);

			break;

		 case SettingButton:
			//�ݒ��ʂɑJ�ځB
			NewGO<SettingScene>(0);

			break;

		 case EndButton:
			//�Q�[�����I���B

			break;
		};
		//�N���X���폜�B
		DeleteGO(this);
	}
}