#include "stdafx.h"
#include "Resultscene.h"
#include "Game.h"
#include "ResultLevel2D.h"
#include "TitleScene.h"


bool ResultScene::Start()
{
	//���U���g��ʕ\��
	sprite = NewGO<ResultLevel2D>(0, "ResultLevel2D");
	m_game = FindGO<Game>("game");

	m_resultLevel2D = FindGO<ResultLevel2D>("ResultLevel2D");

	nowTime = m_game->GetTime();
	bestTime = m_game->GetBestTime();

	m_nowTime = NewGO<FontRender>(3);
	wchar_t text[4][64];
	swprintf_s(text[0], L"%2.1f", nowTime);
	m_nowTime->Init(text[0], { -20.0f,70.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_nowTime->SetScale(1.5f);
	m_nowTime->SetPivot({ 0.0f,0.0f });
	m_BestTime = NewGO<FontRender>(3);
	swprintf_s(text[1], L"%2.1f", bestTime);
	m_BestTime->Init(text[1], { -20.0f,-30.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_BestTime->SetPivot({ 0.0f,0.0f });
	m_BestTime->SetScale(1.5f);

	//Start�֐���return true;
	return true;
}

ResultScene::~ResultScene()
{
	DeleteGO(sprite);
}

void ResultScene::Update()
{
	//�E����or�����͂��ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//���݃Z���N�g����Ă���{�^�����u�����Ƃ�v(0��)��������A
		if (NowSelect % 2 == 0) {
			//�I�����E��1���炷�B
			NowSelect = 1;
		}
		//���݃Z���N�g����Ă���{�^�����u���イ��傤�v(1��)��������A
		else {
			//�I��������1���炷�B
			NowSelect = 0;
		}
		//�ړ����ʉ��炷�B
		CursorMooveSound = NewGO<CSoundSource>(0);
		CursorMooveSound->Init(L"Assets/sound/CursorMoove.wav");
		CursorMooveSound->SetVolume(1.0f);
		CursorMooveSound->Play(false);		//�����V���b�g�Đ��B
	}

	//�{�^����S�Ĕ������ɂ���B
	for (int i = 8; i <10 ; i++) {
		m_resultLevel2D->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

	//���ݑI�����Ă���{�^���̋����\��
	switch (NowSelect) {

	//�u�����Ƃ�v�{�^�����I�΂�Ă���Ƃ��A
	case TitleBackButton:
		//�{�^����s�����x100���ɂ���B
		m_resultLevel2D->GetSprite(8)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		break;

	//�u���イ��傤�v�{�^�����I�΂�Ă���Ƃ��A
	case EndButton:
		//�{�^����s�����x100���ɂ���B
		m_resultLevel2D->GetSprite(9)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

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

			//�u�����Ƃ�v�{�^�����I�΂�Ă���Ƃ��A
		case TitleBackButton:
			//�Q�[����ʂɑJ�ځB
			//NewGO<TitleScene>(0);

			break;

			//�u�����v�{�^�����I�΂�Ă���Ƃ��A
		case EndButton:
			//�Q�[�����I���B
			exit(EXIT_SUCCESS);

			break;
		};
		//�N���X���폜�B
		//DeleteGO(this);
	}
}