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
	BGMSound = NewGO<CSoundSource>(0);
	BGMSound->Init(L"Assets/sound/TitleBGM.wav");
	BGMSound->SetVolume(1.0f);
	BGMSound->Play(true);		//���[�v�Đ��B

	//Stage1
	m_StageSpriteRender[0] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[0]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[0]->Init("Assets/image/Stage1.dds", 350.0f, 350.0f);
	m_StageSpriteRender[0]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[0]->Deactivate();		//��\��
	//Stage2
	m_StageSpriteRender[1] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[1]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[1]->Init("Assets/image/Stage2.dds", 350.0f, 350.0f);
	m_StageSpriteRender[1]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[1]->Deactivate();		//��\��
	//Stage3
	m_StageSpriteRender[2] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[2]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[2]->Init("Assets/image/Stage3.dds", 350.0f, 350.0f);
	m_StageSpriteRender[2]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[2]->Deactivate();		//��\��

	return true;
}

StageSelect::~StageSelect()
{
	DeleteGO(sprite);	//���x���폜
	DeleteGO(BGMSound);	//BGM�폜
	for (int i = 0; i < (FinalStage-1); i++)
	{
		DeleteGO(m_StageSpriteRender[i]);
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
		CursorMooveSound = NewGO<CSoundSource>(0);
		CursorMooveSound->Init(L"Assets/sound/CursorMoove.wav");
		CursorMooveSound->SetVolume(1.0f);
		CursorMooveSound->Play(false);		//�����V���b�g�Đ��B
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
			CursorMooveSound = NewGO<CSoundSource>(0);
			CursorMooveSound->Init(L"Assets/sound/CursorMoove.wav");
			CursorMooveSound->SetVolume(1.0f);
			CursorMooveSound->Play(false);		//�����V���b�g�Đ��B
			//�X�e�[�W�ԍ����P���ɂ��炷
			NowSelectStage -= 1;
		}
	}
	//RB�{�^���������ꂽ��A(�L�[�{�[�h��7)
	if (g_pad[0]->IsTrigger(enButtonRB1))
	{
		if (NowSelectStage != (FinalStage-1)) {
			//�ړ����ʉ��炷�B
			CursorMooveSound = NewGO<CSoundSource>(0);
			CursorMooveSound->Init(L"Assets/sound/CursorMoove.wav");
			CursorMooveSound->SetVolume(1.0f);
			CursorMooveSound->Play(false);		//�����V���b�g�Đ��B
			//�X�e�[�W�ԍ����P��ɂ��炷
			NowSelectStage += 1;
		}
	}
	//�X�e�[�W1,�X�e�[�W2�Ȃǂ̕����摜�\��
	switch (NowSelectStage)
	{
	case StageOne:
		m_StageSpriteRender[0]->Activate();			//�\��
		m_StageSpriteRender[1]->Deactivate();		//��\��
		break;
	case StageTwo:
		m_StageSpriteRender[0]->Deactivate();		//��\��
		m_StageSpriteRender[1]->Activate();			//�\��
		m_StageSpriteRender[2]->Deactivate();		//��\��
		break;
	case StageThree:
		m_StageSpriteRender[1]->Deactivate();		//��\��
		m_StageSpriteRender[2]->Activate();			//�\��
		break;
	}

	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonA)) {
		//����{�^�����Đ��B
		DecisionSound = NewGO<CSoundSource>(0);
		DecisionSound->Init(L"Assets/sound/DecisionButton.wav");
		DecisionSound->SetVolume(1.0f);
		DecisionSound->Play(false);		//1�V���b�g�Đ��B

		switch (NowSelect) {

			//�u���ǂ�v�{�^�����I�΂�Ă���Ƃ��A
		 case BackButton:
			//�^�C�g����ʂɑJ�ځB
			NewGO<TitleScene>(0);

			break;

			//�u�����v�{�^�����I�΂�Ă���Ƃ��A
		 case KetteiButton:
			 //�Q�[����ʂɑJ��
			NewGO<Game>(0, "game");

			break;
		};
		//�N���X���폜�B
		DeleteGO(this);
	}
}