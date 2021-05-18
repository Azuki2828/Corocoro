#include "stdafx.h"
#include "ResultScene.h"
#include "Game.h"
#include "ResultLevel2D.h"
#include "TitleScene.h"
#include "SaveData.h"

bool ResultScene::Start()
{
	//���U���g��ʕ\��
	sprite = NewGO<ResultLevel2D>(0, "ResultLevel2D");
	m_game = FindGO<Game>("game");

	m_resultLevel2D = FindGO<ResultLevel2D>("ResultLevel2D");

	nowTime = m_game->GetTime();
	bestTime = m_game->GetBestTime();

	if(nowTime < bestTime)
	{
		NewRecordFlg = true;
		bestTime = nowTime;
	}

	m_nowTime = NewGO<FontRender>(2);
	wchar_t text[4][64];
	swprintf_s(text[0], L"%2.1f", nowTime);
	m_nowTime->Init(text[0], { 20.0f,70.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_nowTime->SetScale(1.5f);
	m_nowTime->SetPivot({ 0.0f,0.0f });

	//�L�^��1���̎�
	if (nowTime < 10) {
		//x���W�𒲐��B
		m_nowTime->SetPosition({ 20.0f,70.0f });	//�ꏊ
	}
	//�L�^��10���̎�
	if (nowTime > 10 && nowTime < 100) {
		//x���W�𒲐��B
		m_nowTime->SetPosition({ -15.0f,70.0f });	//�ꏊ
	}
	//�L�^��100���̎�
	if (nowTime > 100 && nowTime < 1000) {
		//x���W�𒲐��B
		m_nowTime->SetPosition({ -45.0f,70.0f });	//�ꏊ
	}

	m_BestTime = NewGO<FontRender>(2);
	swprintf_s(text[1], L"%2.1f", bestTime);
	m_BestTime->Init(text[1], { 20.0f,-30.0f }, { 1.0f,1.0f,1.0f,1.0f });
	m_BestTime->SetPivot({ 0.0f,0.0f });
	m_BestTime->SetScale(1.5f);

	//�L�^��1���̎�
	if (bestTime < 10) {
		//x���W�𒲐��B
		m_BestTime->SetPosition({ 20.0f,-30.0f });	//�ꏊ
	}
	//�L�^��10���̎�
	if (bestTime > 10 && bestTime < 100) {
		//x���W�𒲐��B
		m_BestTime->SetPosition({ -15.0f,-30.0f });	//�ꏊ
	}
	//�L�^��100���̎�
	if (bestTime > 100 && bestTime < 1000) {
		//x���W�𒲐��B
		m_BestTime->SetPosition({ -45.0f,-30.0f });	//�ꏊ
	}

	//C++����̃L���X�g���@�B
	//static_cast<int>(bestTime);

	m_game = FindGO<Game>("game");
	m_time = m_game->GetTime();		//Game�Ŏ擾�����^�C��
	SaveData* savedata = FindGO<SaveData>("savedata");
	savedata->FileSave();	//�^�C�����Z�[�u����

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
		SoundManager::GetInstance()->Play(SE_CursolMove);
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

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (Fscale < 0.25f) {
			ScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (Fscale > 0.275f) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//�g��
			Fscale += 0.0005f;
		}
		if (ScaleUpFlag == false) {
			//�k��
			Fscale -= 0.0005f;
		}
		//�X�v���C�g�ɔ��f�B
		Vscale = { Fscale,Fscale,Fscale };
		m_resultLevel2D->GetSprite(8)->SetScale(Vscale);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_resultLevel2D->GetSprite(9)->SetScale(vscale1);

		break;

	//�u���イ��傤�v�{�^�����I�΂�Ă���Ƃ��A
	case EndButton:
		//�{�^����s�����x100���ɂ���B
		m_resultLevel2D->GetSprite(9)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (Fscale1 < 0.2f) {
			ScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (Fscale1 > 0.225f) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//�g��
			Fscale1 += 0.0005f;
		}
		if (ScaleUpFlag == false) {
			//�k��
			Fscale1 -= 0.0005f;
		}
		//�X�v���C�g�ɔ��f�B
		Vscale = { Fscale1,Fscale1,Fscale1 };
		m_resultLevel2D->GetSprite(9)->SetScale(Vscale);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_resultLevel2D->GetSprite(8)->SetScale(vscale);

		break;
	};


	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//����{�^�����Đ��B
		SoundManager::GetInstance()->Play(SE_DecisionButton);

		switch (NowSelect) {

			//�u�����Ƃ�v�{�^�����I�΂�Ă���Ƃ��A
		case TitleBackButton:
			//�Q�[����ʂɑJ�ځB
			NewGO<TitleScene>(0);

			break;

			//�u�����v�{�^�����I�΂�Ă���Ƃ��A
		case EndButton:
			//�Q�[�����I���B
			exit(EXIT_SUCCESS);

			break;
		};
		//�N���X���폜�B
		DeleteGO(this);
	}

	//���񂫂낭�I�̕���������Ă�������
	//if (NewRecordFlg)
	//{
	//	if (NewRecordFlgSub) {
	//		//���񂫂낭�I�摜���������B
	//		m_spriteRender = NewGO<SpriteRender>(2);
	//		m_spriteRender->SetPosition({ RecordPos,0.0f,0.0f });
	//		m_spriteRender->Init("Assets/image/Record.dds", 750.0f, 750.0f);
	//		NewRecordFlgSub = false;
	//	}
	//	//�E���獶�Ɉړ����鏈��
	//		m_spriteRender->SetPosition({ RecordPos,0.0f,0.0f });
	//		RecordPos-=5;
	//		//��ʊO�Ɉړ�����Ɩ��ʂɎc�����ɃX�v���C�g������
	//		if (RecordPos < -1000.0f)
	//		{
	//			//�����ʒu�ɖ߂�
	//			RecordPos = 1100.0f;
	//		}
	//}
}