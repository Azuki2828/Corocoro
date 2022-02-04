#include "stdafx.h"
#include "TitleScene.h"
#include "TitleLevel2D.h"
#include "Game.h"
#include "StageSelect.h"
#include "RuleScene.h"
#include "SettingScene.h"

namespace {
	const Vector3 DEFAULT_SPRITE_SCALE = { 0.2f,0.2f,0.2f };	//�f�t�H���g�̃{�^���̊g�嗦�B
}
bool TitleScene::Start()
{

	m_ButtonScale = DEFAULT_SPRITE_SCALE.x;

	

	//�^�C�g����ʕ\��
	m_titleLevel2D = NewGO<TitleLevel2D>(enPriority_Zeroth, NAME_TITLE_LEVEL2D);

	//�^�C�g��BGM�Đ��B
	SoundManager::GetInstance()->Play(enBGM_Title);
	//TitleBGMSound = NewGO<CSoundSource>(0);
	//TitleBGMSound->Init(L"Assets/sound/TitleBGM.wav");
	//TitleBGMSound->SetVolume(1.0f);
	//TitleBGMSound->Play(true);		//���[�v�Đ��B

	//Start�֐���return true;
	return true;
}

TitleScene::~TitleScene()
{
	//�^�C�g����ʂ̃��x�����폜�B
	DeleteGO(m_titleLevel2D);
	//�^�C�g��BGM���폜�B
	SoundManager::GetInstance()->Release(enBGM_Title);
}

void TitleScene::Update()
{
	//�{�^����S�Ĕ������ɂ���B
	m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);
	m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);
	m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);

	//�E����or�����͂��ꂽ��A
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonRight) || g_pad[enData_Zeroth]->IsTrigger(enButtonLeft)) {
		//���݃Z���N�g����Ă���{�^�����u�͂��߂�v(0��)or�u�����Ă��v(2��)��������A
		switch (m_nowSelect) {
		case StartButton:
			m_nowSelect = RuleButton;
			break;
		case RuleButton:
			m_nowSelect = StartButton;
			break;
		case EndButton:
			break;
		}
		//���݃Z���N�g����Ă���{�^�����u�����т����v(1��)or�u���イ��傤�v(3��)��������A
		//else {
		//	//�I��������1���炷�B
		//	NowSelect -= 1;
		//}
		
		//�ړ����ʉ��炷�B
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}
	//�����or�����͂��ꂽ��A
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonUp) || g_pad[enData_Zeroth]->IsTrigger(enButtonDown)) {
		//���݃Z���N�g����Ă���{�^�����u�͂��߂�v(0��)or�u�����т����v(1��)��������A
		if (m_nowSelect < EndButton) {
			//�I����^����1���炷�B
			m_nowSelect = EndButton;
		}
		//���݃Z���N�g����Ă���{�^�����u�����Ă��v(2��)or�u�����v(3��)��������A
		else {
			//�I����^��ɂ��炷�B
			m_nowSelect = RuleButton;
		}

		//�ړ����ʉ��炷�B
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}



  //���ݑI�����Ă���{�^���̋����\��
	switch (m_nowSelect) {

	 //�u�͂��߂�v�{�^�����I�΂�Ă���Ƃ��A
	 case StartButton:
		 //�{�^����s�����x100���ɂ���B
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);


		  //�傫�����ŏ��ɂȂ����Ƃ��A
		 if (m_ButtonScale < TITLE_SELECT_BUTTON_SCALE_MIN) {
			 m_scaleUpFlag = true;
		 }
		 //�傫�����ő�ɂȂ����Ƃ��A
		 if (m_ButtonScale > TITLE_SELECT_BUTTON_SCALE_MAX) {
			 m_scaleUpFlag = false;
		 }

		 if (m_scaleUpFlag == true) {
			 //�g��
			 m_ButtonScale += BUTTON_SCALE_ADD;
		 }
		 if (m_scaleUpFlag == false) {
			 //�k��
			 m_ButtonScale -= BUTTON_SCALE_ADD;
		 }
		 //�X�v���C�g�ɔ��f�B
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetScale({ m_ButtonScale,m_ButtonScale,m_ButtonScale });

		 //�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetScale(DEFAULT_SPRITE_SCALE);
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetScale(DEFAULT_SPRITE_SCALE);

		break;

	 //�u�����т����v�{�^�����I�΂�Ă���Ƃ��A
	 case RuleButton:
		 //�{�^����s�����x100���ɂ���B
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		 //�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		 if (m_ButtonScale < TITLE_SELECT_BUTTON_SCALE_MIN) {
			 m_scaleUpFlag = true;
		 }
		 //�傫�����ő�ɂȂ����Ƃ��A
		 if (m_ButtonScale > TITLE_SELECT_BUTTON_SCALE_MAX) {
			 m_scaleUpFlag = false;
		 }

		 if (m_scaleUpFlag == true) {
			 //�g��
			 m_ButtonScale += BUTTON_SCALE_ADD;
		 }
		 if (m_scaleUpFlag == false) {
			 //�k��
			 m_ButtonScale -= BUTTON_SCALE_ADD;
		 }
		 //�X�v���C�g�ɔ��f�B
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetScale({ m_ButtonScale,m_ButtonScale,m_ButtonScale });

		 //�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetScale(DEFAULT_SPRITE_SCALE);
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetScale(DEFAULT_SPRITE_SCALE);

		break;

	 //�u���イ��傤�v�{�^�����I�΂�Ă���Ƃ��A
	 case EndButton:
		 //�{�^����s�����x100���ɂ���B
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		 if (m_ButtonScale < TITLE_SELECT_BUTTON_SCALE_MIN) {
			 m_scaleUpFlag = true;
		 }
		 //�傫�����ő�ɂȂ����Ƃ��A
		 if (m_ButtonScale > TITLE_SELECT_BUTTON_SCALE_MAX) {
			 m_scaleUpFlag = false;
		 }

		 if (m_scaleUpFlag == true) {
			 //�g��
			 m_ButtonScale += BUTTON_SCALE_ADD;
		 }
		 if (m_scaleUpFlag == false) {
			 //�k��
			 m_ButtonScale -= BUTTON_SCALE_ADD;
		 }
		 //�X�v���C�g�ɔ��f�B
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_EndButton)->SetScale({ m_ButtonScale,m_ButtonScale,m_ButtonScale });

		 //�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_StartButton)->SetScale(DEFAULT_SPRITE_SCALE);
		 m_titleLevel2D->GetTitleSprite(enTitleSprite_RuleButton)->SetScale(DEFAULT_SPRITE_SCALE);


		break;
	};


	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//����{�^�����Đ��B

		SoundManager::GetInstance()->Play(enSE_DecisionButton);

		switch (m_nowSelect) {

			//�u�͂��߂�v�{�^�����I�΂�Ă���Ƃ��A
		case StartButton:
			//�X�e�[�W�Z���N�g��ʂɑJ�ځB
			NewGO<StageSelect>(enPriority_Zeroth, NAME_STAGE_SELECT);

			break;

			//�u�����т����v�{�^�����I�΂�Ă���Ƃ��A
		case RuleButton:
			//���[��(����)������ʂɑJ�ځB
			NewGO<RuleScene>(enPriority_Zeroth, NAME_RULE_SCENE);

			break;

			//�u�����v�{�^�����I�΂�Ă���Ƃ��A
		case EndButton:
			//�Q�[�����I���B
			exit(EXIT_SUCCESS);

			break;
		};
		//�N���X���폜�B
		DeleteGO(this);
	};
}