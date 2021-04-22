#include "stdafx.h"
#include "TitleScene.h"
#include "TitleLevel2D.h"

#include "Game.h"
#include "RuleScene.h"
#include "SettingScene.h"


bool TitleScene::Start()
{
	//�^�C�g����ʕ\��
	sprite = NewGO<TitleLevel2D>(0,"titleLevel2D");

	m_titleLevel2D = FindGO<TitleLevel2D>("titleLevel2D");

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
		//���݃Z���N�g����Ă���{�^�����u�����т����v(1��)or�u���イ��傤�v(3��)��������A
		else {
			//�I��������1���炷�B
			NowSelect -= 1;
		}
		//�ړ����ʉ��炷�B
		CursorMooveSound = NewGO<CSoundSource>(0);
		CursorMooveSound->Init(L"Assets/sound/CursorMoove.wav");
		CursorMooveSound->SetVolume(1.0f);
		CursorMooveSound->Play(false);		//�����V���b�g�Đ��B
	}
	//�����or�����͂��ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonDown)) {
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
		//�ړ����ʉ��炷�B
		CursorMooveSound = NewGO<CSoundSource>(0);
		CursorMooveSound->Init(L"Assets/sound/CursorMoove.wav");
		CursorMooveSound->SetVolume(1.0f);
		CursorMooveSound->Play(false);		//�����V���b�g�Đ��B
	}

	//�{�^����S�Ĕ������ɂ���B
	for (int i = 2; i < 6; i++) {
		m_titleLevel2D->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

  //���ݑI�����Ă���{�^���̋����\��
	switch (NowSelect) {

	 //�u�͂��߂�v�{�^�����I�΂�Ă���Ƃ��A
	 case StartButton:
		 //�{�^����s�����x100���ɂ���B
		 m_titleLevel2D->GetSprite(2)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		break;

	 //�u�����т����v�{�^�����I�΂�Ă���Ƃ��A
	 case RuleButton:
		 //�{�^����s�����x100���ɂ���B
		 m_titleLevel2D->GetSprite(3)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		 //�P�U���̌������g���ă{�^�����g��k������B

		break;

	 //�u�����Ă��v�{�^�����I�΂�Ă���Ƃ��A
	 case SettingButton:
		 //�{�^����s�����x100���ɂ���B
		 m_titleLevel2D->GetSprite(4)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		break;

	 //�u���イ��傤�v�{�^�����I�΂�Ă���Ƃ��A
	 case EndButton:
		 //�{�^����s�����x100���ɂ���B
		 m_titleLevel2D->GetSprite(5)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		break;
	};


	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//����{�^�����Đ��B

		DecisionSound = NewGO<CSoundSource>(0);
		DecisionSound->Init(L"Assets/sound/DecisionButton.wav");
		DecisionSound->SetVolume(1.0f);
		DecisionSound->Play(false);		//1�V���b�g�Đ��B

		switch (NowSelect) {

		 //�u�͂��߂�v�{�^�����I�΂�Ă���Ƃ��A
		 case StartButton:
			//�Q�[����ʂɑJ�ځB
			NewGO<Game>(0,"game");

			break;

		 //�u�����т����v�{�^�����I�΂�Ă���Ƃ��A
		 case RuleButton:
			//���[��(����)������ʂɑJ�ځB
			NewGO<RuleScene>(0);

			break;

		 //�u�����Ă��v�{�^�����I�΂�Ă���Ƃ��A
		 case SettingButton:
			//�ݒ��ʂɑJ�ځB
			NewGO<SettingScene>(0);

			break;

		 //�u�����v�{�^�����I�΂�Ă���Ƃ��A
		 case EndButton:
			//�Q�[�����I���B
			 exit(1);

			break;
		};
		//�N���X���폜�B
		DeleteGO(this);
	}
}