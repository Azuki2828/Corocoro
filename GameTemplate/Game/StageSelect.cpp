#include "stdafx.h"
#include "StageSelect.h"
#include "StageSelectLevel2D.h"
#include "Game.h"
#include "TitleScene.h"

bool StageSelect::Start()
{
	//�X�e�[�W�I����ʕ\��
	sprite = NewGO<StageSelectLevel2D>(0, "StageSelectLevel2D");

	//BGM�Đ��B
	SoundManager::GetInstance()->Play(BGM_Title);
	//BGMSound = NewGO<CSoundSource>(0);
	//BGMSound->Init(L"Assets/sound/TitleBGM.wav");
	//BGMSound->SetVolume(1.0f);
	//BGMSound->Play(true);		//���[�v�Đ��B

	//Stage1
	m_StageSpriteRender[0][0] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[0][0]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[0][0]->Init("Assets/image/Stage1.dds", 350.0f, 350.0f);
	m_StageSpriteRender[0][0]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[0][0]->Deactivate();		//��\��

	m_StageSpriteRender[0][1] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[0][1]->SetPosition({ 0.0f,0.0f,0.0f });
	m_StageSpriteRender[0][1]->Init("Assets/image/Stage01.dds", 1024.0f, 768.0f);
	m_StageSpriteRender[0][1]->SetScale({ 0.5f,0.5f,0.5f });
	m_StageSpriteRender[0][1]->Deactivate();		//��\��
	//Stage2
	m_StageSpriteRender[1][0] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[1][0]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[1][0]->Init("Assets/image/Stage2.dds", 350.0f, 350.0f);
	m_StageSpriteRender[1][0]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[1][0]->Deactivate();		//��\��

	m_StageSpriteRender[1][1] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[1][1]->SetPosition({ 0.0f,0.0f,0.0f });
	m_StageSpriteRender[1][1]->Init("Assets/image/Stage02.dds", 1024.0f, 768.0f);
	m_StageSpriteRender[1][1]->SetScale({ 0.5f,0.5f,0.5f });
	m_StageSpriteRender[1][1]->Deactivate();		//��\��
	//Stage3
	m_StageSpriteRender[2][0] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[2][0]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[2][0]->Init("Assets/image/Stage3.dds", 350.0f, 350.0f);
	m_StageSpriteRender[2][0]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[2][0]->Deactivate();		//��\��

	m_StageSpriteRender[2][1] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[2][1]->SetPosition({ 0.0f, 0.0f,0.0f });
	m_StageSpriteRender[2][1]->Init("Assets/image/Stage03.dds", 1024.0f, 768.0f);
	m_StageSpriteRender[2][1]->SetScale({ 0.5f,0.5f,0.5f });
	m_StageSpriteRender[2][1]->Deactivate();		//��\��

	//Stage4
	m_StageSpriteRender[3][0] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[3][0]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[3][0]->Init("Assets/image/Stage4.dds", 350.0f, 350.0f);
	m_StageSpriteRender[3][0]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[3][0]->Deactivate();		//��\��

	m_StageSpriteRender[3][1] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[3][1]->SetPosition({ 0.0f, 0.0f,0.0f });
	m_StageSpriteRender[3][1]->Init("Assets/image/Stage04.dds", 1024.0f, 768.0f);
	m_StageSpriteRender[3][1]->SetScale({ 0.5f,0.5f,0.5f });
	m_StageSpriteRender[3][1]->Deactivate();		//��\��

	return true;
}

StageSelect::~StageSelect()
{
	DeleteGO(sprite);	//���x���폜
	SoundManager::GetInstance()->Release(BGM_Title);	//BGM�폜
	for (int i = 0; i < (FinalStage-1); i++)
	{
		DeleteGO(m_StageSpriteRender[i][0]);
		DeleteGO(m_StageSpriteRender[i][1]);
	}
}

void StageSelect::Update()
{
	//�E����or�����͂��ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//���݃Z���N�g����Ă���{�^�����u���ǂ�v(0��)��������A
		if (NowSelect % 2 == 0) {
			//�I�����E��1���炷�B
			NowSelect = 1;
		}
		//���݃Z���N�g����Ă���{�^�����u�����Ă��v(1��)��������A
		else {
			//�I��������1���炷�B
			NowSelect = 0;
		}
		//�ړ����ʉ��炷�B
		SoundManager::GetInstance()->Play(SE_CursolMove);
	}

	//�{�^����S�Ĕ������ɂ���B
	for (int i = 4; i < 6; i++) {
		sprite->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

	//���ݑI�����Ă���{�^���̋����\��
	switch (NowSelect) {

		//�u���ǂ�v�{�^�����I�΂�Ă���Ƃ��A
	 case BackButton:
		//�{�^����s�����x100���ɂ���B
		sprite->GetSprite(4)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (Fscale < 0.20f) {
			ScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (Fscale > 0.23f) {
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
		sprite->GetSprite(4)->SetScale(Vscale);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		sprite->GetSprite(5)->SetScale(vscale1);

		break;

		//�u�����Ă��v�{�^�����I�΂�Ă���Ƃ��A
	 case KetteiButton:
		//�{�^����s�����x100���ɂ���B
		sprite->GetSprite(5)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (Fscale1 < 0.15f) {
			ScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (Fscale1 > 0.18f) {
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
		sprite->GetSprite(5)->SetScale(Vscale);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		sprite->GetSprite(4)->SetScale(vscale);

		break;
	};

	//�X�e�[�W�I��

	//���ݑI������Ă���X�e�[�W��1�̂Ƃ��A
	if (NowSelectStage == StageOne)
	{
		//�������\������
		sprite->GetSprite(2)->Deactivate();
		//LB���\������
		sprite->GetSprite(6)->Deactivate();
	}
	//�X�e�[�W�P�ȊO�̎��A
	else
	{
		//������\������
		sprite->GetSprite(2)->Activate();
		//LB��\������
		sprite->GetSprite(6)->Activate();
	}
	//���ݑI������Ă���X�e�[�W���Ō�̃X�e�[�W�̂Ƃ��A
	if (NowSelectStage == FinalStage-1)
	{
		//�E�����\������
		sprite->GetSprite(3)->Deactivate();
		//RB���\������
		sprite->GetSprite(7)->Deactivate();
	}
	//�Ō�̃X�e�[�W�ȊO�̎��A
	else
	{
		//�E����\������
		sprite->GetSprite(3)->Activate();
		//RB��\������
		sprite->GetSprite(7)->Activate();
	}

	//LB�{�^���������ꂽ��A(�L�[�{�[�hB)
	if (g_pad[0]->IsTrigger(enButtonLB1))
	{
		//�X�e�[�W1���I�΂�Ă��Ȃ��Ƃ�����1���ɂ��炷
		if (NowSelectStage != StageOne)
		{
			//�ړ����ʉ��炷�B
			SoundManager::GetInstance()->Play(SE_CursolMove);
			//�X�e�[�W�ԍ����P���ɂ��炷
			NowSelectStage -= 1;
		}
	}
	//RB�{�^���������ꂽ��A(�L�[�{�[�h��7)
	if (g_pad[0]->IsTrigger(enButtonRB1))
	{
		if (NowSelectStage != (FinalStage-1)) {
			//�ړ����ʉ��炷�B
			SoundManager::GetInstance()->Play(SE_CursolMove);
			//�X�e�[�W�ԍ����P��ɂ��炷
			NowSelectStage += 1;
		}
	}
	//�X�e�[�W1,�X�e�[�W2�Ȃǂ̕����摜�\��
	switch (NowSelectStage)
	{
	case StageOne:
		m_StageSpriteRender[0][0]->Activate();			//�\��
		m_StageSpriteRender[0][1]->Activate();			//�\��
		m_StageSpriteRender[1][0]->Deactivate();		//��\��
		m_StageSpriteRender[1][1]->Deactivate();		//��\��
		break;
	case StageTwo:
		m_StageSpriteRender[0][0]->Deactivate();		//��\��
		m_StageSpriteRender[0][1]->Deactivate();		//��\��
		m_StageSpriteRender[1][0]->Activate();			//�\��
		m_StageSpriteRender[1][1]->Activate();			//�\��
		m_StageSpriteRender[2][0]->Deactivate();		//��\��
		m_StageSpriteRender[2][1]->Deactivate();		//��\��
		break;
	case StageThree:
		m_StageSpriteRender[1][0]->Deactivate();		//��\��
		m_StageSpriteRender[1][1]->Deactivate();		//��\��
		m_StageSpriteRender[2][0]->Activate();			//�\��
		m_StageSpriteRender[2][1]->Activate();			//�\��
		m_StageSpriteRender[3][0]->Deactivate();		//��\��
		m_StageSpriteRender[3][1]->Deactivate();		//��\��
		break;
	case StageFour:
		m_StageSpriteRender[2][0]->Deactivate();		//��\��
		m_StageSpriteRender[2][1]->Deactivate();		//��\��
		m_StageSpriteRender[3][0]->Activate();			//�\��
		m_StageSpriteRender[3][1]->Activate();			//�\��
		break;
	}

	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonA)) {
		//����{�^�����Đ��B
		SoundManager::GetInstance()->Play(SE_DecisionButton);

		switch (NowSelect) {

			//�u���ǂ�v�{�^�����I�΂�Ă���Ƃ��A
		 case BackButton:
			//�^�C�g����ʂɑJ�ځB
			NewGO<TitleScene>(0);

			break;

			//�u����v�{�^�����I�΂�Ă���Ƃ��A
		 case KetteiButton:
			 m_game = NewGO<Game>(0, "game");
			 //�Q�[����ʂɑJ��
			 m_game->SetStageNum(4);
			break;
		};
		//�N���X���폜�B
		DeleteGO(this);
	}
}