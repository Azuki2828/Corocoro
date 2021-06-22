#include "stdafx.h"
#include "StageSelect.h"
#include "StageSelectLevel2D.h"
#include "Game.h"
#include "TitleScene.h"

bool StageSelect::Start()
{
	//�X�e�[�W�I����ʕ\��
	m_sprite = NewGO<StageSelectLevel2D>(enPriority_Zeroth, NAME_STAGE_SELECT_LEVEL2D);

	//BGM�Đ��B
	SoundManager::GetInstance()->Play(enBGM_Title);

	//Stage1
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->SetPosition(SPRITE_STAGE_NUM_POS);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->Init(SPRITE_NAME_STAGE_NUM_1, SPRITE_STAGE_NUM_WH.x, SPRITE_STAGE_NUM_WH.y);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->SetScale(SPRITE_STAGE_NUM_SCALE);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->Deactivate();		//��\��

	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->SetPosition(Vector3::Zero);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->Init(SPRITE_NAME_STAGE_MODEL_1, SPRITE_STAGE_MODEL_WH.x, SPRITE_STAGE_MODEL_WH.y);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->SetScale(SPRITE_STAGE_MODEL_SCALE);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->Deactivate();		//��\��
	//Stage2
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->SetPosition(SPRITE_STAGE_NUM_POS);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Init(SPRITE_NAME_STAGE_NUM_2, SPRITE_STAGE_NUM_WH.x, SPRITE_STAGE_NUM_WH.y);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->SetScale(SPRITE_STAGE_NUM_SCALE);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Deactivate();		//��\��

	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->SetPosition(Vector3::Zero);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Init(SPRITE_NAME_STAGE_MODEL_2, SPRITE_STAGE_MODEL_WH.x, SPRITE_STAGE_MODEL_WH.y);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->SetScale(SPRITE_STAGE_MODEL_SCALE);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Deactivate();		//��\��
	//Stage3
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->SetPosition(SPRITE_STAGE_NUM_POS);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Init(SPRITE_NAME_STAGE_NUM_3, SPRITE_STAGE_NUM_WH.x, SPRITE_STAGE_NUM_WH.y);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->SetScale(SPRITE_STAGE_NUM_SCALE);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Deactivate();		//��\��

	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->SetPosition(Vector3::Zero);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Init(SPRITE_NAME_STAGE_MODEL_3, SPRITE_STAGE_MODEL_WH.x, SPRITE_STAGE_MODEL_WH.y);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->SetScale(SPRITE_STAGE_MODEL_SCALE);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Deactivate();		//��\��

	//Stage4
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->SetPosition(SPRITE_STAGE_NUM_POS);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->Init(SPRITE_NAME_STAGE_NUM_4, SPRITE_STAGE_NUM_WH.x, SPRITE_STAGE_NUM_WH.y);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->SetScale(SPRITE_STAGE_NUM_SCALE);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->Deactivate();		//��\��

	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->SetPosition(Vector3::Zero);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->Init(SPRITE_NAME_STAGE_MODEL_4, SPRITE_STAGE_MODEL_WH.x, SPRITE_STAGE_MODEL_WH.y);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->SetScale(SPRITE_STAGE_MODEL_SCALE);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->Deactivate();		//��\��

	return true;
}

StageSelect::~StageSelect()
{
	DeleteGO(m_sprite);	//���x���폜
	SoundManager::GetInstance()->Release(enBGM_Title);	//BGM�폜
	for (int i = 0; i < Stage_Num; i++)
	{
		DeleteGO(m_stageSpriteRender[i][enStageSelectSprite_StageNum]);
		DeleteGO(m_stageSpriteRender[i][enStageSelectSprite_StageModel]);
	}
}

void StageSelect::Update()
{
	//�E����or�����͂��ꂽ��A
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonRight) || g_pad[enData_Zeroth]->IsTrigger(enButtonLeft)) {
		//���݃Z���N�g����Ă���{�^�����u���ǂ�v(0��)��������A
		if (NowSelect == BackButton) {
			//�I�����E��1���炷�B
			NowSelect = KetteiButton;
		}
		//���݃Z���N�g����Ă���{�^�����u�����Ă��v(1��)��������A
		else {
			//�I��������1���炷�B
			NowSelect = BackButton;
		}
		//�ړ����ʉ��炷�B
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}

	//�{�^����S�Ĕ������ɂ���B
	HUD::GetHUD()->SetMulColor(enSprite_Back, TRANSLUCENT_VALUE_HALF);
	HUD::GetHUD()->SetMulColor(enSprite_Decision, TRANSLUCENT_VALUE_HALF);

	m_standardScale[BackButton] = HUD::GetHUD()->GetScale(enSprite_Back);
	m_standardScale[KetteiButton] = HUD::GetHUD()->GetScale(enSprite_Decision);

	//���ݑI�����Ă���{�^���̋����\��
	switch (NowSelect) {

		//�u���ǂ�v�{�^�����I�΂�Ă���Ƃ��A
	 case BackButton:
		//�{�^����s�����x100���ɂ���B
		 HUD::GetHUD()->SetMulColor(enSprite_Back, TRANSLUCENT_VALUE_MAX);

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (Fscale < BUTTON_SIZE_MIN) {
			ScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (Fscale > BUTTON_SIZE_MAX) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//�g��
			Fscale += BUTTON_SCALE_ADD;
		}
		if (ScaleUpFlag == false) {
			//�k��
			Fscale -= BUTTON_SCALE_ADD;
		}
		//�X�v���C�g�ɔ��f�B
		Vscale = { Fscale,Fscale,Fscale };
		HUD::GetHUD()->SetScale(enSprite_Back, Vscale);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		HUD::GetHUD()->SetScale(enSprite_Decision, m_standardScale[KetteiButton]);

		break;

		//�u�����Ă��v�{�^�����I�΂�Ă���Ƃ��A
	 case KetteiButton:
		//�{�^����s�����x100���ɂ���B
		 HUD::GetHUD()->SetMulColor(enSprite_Decision, TRANSLUCENT_VALUE_MAX);

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (Fscale1 < BUTTON_SIZE_MIN) {
			ScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (Fscale1 > BUTTON_SIZE_MAX) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//�g��
			Fscale1 += BUTTON_SCALE_ADD;
		}
		if (ScaleUpFlag == false) {
			//�k��
			Fscale1 -= BUTTON_SCALE_ADD;
		}
		//�X�v���C�g�ɔ��f�B
		Vscale = { Fscale1,Fscale1,Fscale1 };
		HUD::GetHUD()->SetScale(enSprite_Decision, Vscale);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		HUD::GetHUD()->SetScale(enSprite_Back, m_standardScale[BackButton]);

		break;
	};

	//�X�e�[�W�I��

	//���ݑI������Ă���X�e�[�W��1�̂Ƃ��A
	if (NowSelectStage == Stage_One)
	{
		//�������\������
		HUD::GetHUD()->Deactivate(enSprite_LeftSelect);
		//LB���\������
		HUD::GetHUD()->Deactivate(enSprite_LB);
	}
	//�X�e�[�W�P�ȊO�̎��A
	else
	{
		//������\������
		HUD::GetHUD()->Activate(enSprite_LeftSelect);
		//LB��\������
		HUD::GetHUD()->Activate(enSprite_LB);
	}
	//���ݑI������Ă���X�e�[�W���Ō�̃X�e�[�W�̂Ƃ��A
	if (NowSelectStage == Stage_Four)
	{
		//�E�����\������
		HUD::GetHUD()->Deactivate(enSprite_RightSelect);
		//RB���\������
		HUD::GetHUD()->Deactivate(enSprite_RB);
	}
	//�Ō�̃X�e�[�W�ȊO�̎��A
	else
	{
		//�E����\������
		HUD::GetHUD()->Activate(enSprite_RightSelect);
		//RB��\������
		HUD::GetHUD()->Activate(enSprite_RB);
	}

	//LB�{�^���������ꂽ��A(�L�[�{�[�hB)
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonLB1))
	{
		//�X�e�[�W1���I�΂�Ă��Ȃ��Ƃ�����1���ɂ��炷
		if (NowSelectStage != Stage_One)
		{
			//�ړ����ʉ��炷�B
			SoundManager::GetInstance()->Play(enSE_CursolMove);
			//�X�e�[�W�ԍ����P���ɂ��炷
			NowSelectStage--;
		}
	}
	//RB�{�^���������ꂽ��A(�L�[�{�[�h��7)
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonRB1))
	{
		if (NowSelectStage != Stage_Four) {
			//�ړ����ʉ��炷�B
			SoundManager::GetInstance()->Play(enSE_CursolMove);
			//�X�e�[�W�ԍ����P��ɂ��炷
			NowSelectStage++;
		}
	}
	//�X�e�[�W1,�X�e�[�W2�Ȃǂ̕����摜�\��
	switch (NowSelectStage)
	{
	case Stage_One:
		m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->Activate();			//�\��
		m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->Activate();			//�\��
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Deactivate();		//��\��
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Deactivate();		//��\��
		break;
	case Stage_Two:
		m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->Deactivate();		//��\��
		m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->Deactivate();		//��\��
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Activate();			//�\��
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Activate();			//�\��
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Deactivate();		//��\��
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Deactivate();		//��\��
		break;
	case Stage_Three:
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Deactivate();		//��\��
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Deactivate();		//��\��
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Activate();			//�\��
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Activate();			//�\��
		m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->Deactivate();		//��\��
		m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->Deactivate();		//��\��
		break;
	case Stage_Four:
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Deactivate();		//��\��
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Deactivate();		//��\��
		m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->Activate();			//�\��
		m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->Activate();			//�\��
		break;
	}

	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonA)) {
		//����{�^�����Đ��B
		SoundManager::GetInstance()->Play(enSE_DecisionButton);

		switch (NowSelect) {

			//�u���ǂ�v�{�^�����I�΂�Ă���Ƃ��A
		 case BackButton:
			//�^�C�g����ʂɑJ�ځB
			NewGO<TitleScene>(enPriority_Zeroth);

			break;

			//�u����v�{�^�����I�΂�Ă���Ƃ��A
		 case KetteiButton:
			 m_game = NewGO<Game>(enPriority_Zeroth, "game");
			 //�Q�[����ʂɑJ��
			 m_game->SetStageNum(NowSelectStage);
			break;
		};
		//�N���X���폜�B
		DeleteGO(this);
	}
}