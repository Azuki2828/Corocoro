#include "stdafx.h"
#include "StageSelect.h"
#include "StageSelectLevel2D.h"
#include "Game.h"
#include "TitleScene.h"

bool StageSelect::Start()
{
	//�X�e�[�W�I����ʕ\��
	m_stageSelectLevel2D = NewGO<StageSelectLevel2D>(enPriority_Zeroth, NAME_STAGE_SELECT_LEVEL2D);

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

	//m_standardScale[BackButton] = m_stageSelectLevel2D->GetScale(enStageSelectSprite_BackButton);
	//m_standardScale[KetteiButton] = m_stageSelectLevel2D->GetScale(enStageSelectSprite_DecisionButton);

	return true;
}

StageSelect::~StageSelect()
{
	DeleteGO(m_stageSelectLevel2D);	//���x���폜
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
		if (m_nowSelect == BackButton) {
			//�I�����E��1���炷�B
			m_nowSelect = KetteiButton;
		}
		//���݃Z���N�g����Ă���{�^�����u�����Ă��v(1��)��������A
		else {
			//�I��������1���炷�B
			m_nowSelect = BackButton;
		}
		//�ړ����ʉ��炷�B
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}

	//�{�^����S�Ĕ������ɂ���B
	m_stageSelectLevel2D->GetSprite(enStageSelectSprite_BackButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);
	m_stageSelectLevel2D->GetSprite(enStageSelectSprite_DecisionButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);

	//���ݑI�����Ă���{�^���̋����\��
	switch (m_nowSelect) {

		//�u���ǂ�v�{�^�����I�΂�Ă���Ƃ��A
	 case BackButton:
		//�{�^����s�����x100���ɂ���B
		 m_stageSelectLevel2D->GetSprite(enStageSelectSprite_BackButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (m_spriteBackScale < BACK_BUTTON_SIZE_MIN) {
			m_spriteScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (m_spriteBackScale > BACK_BUTTON_SIZE_MAX) {
			m_spriteScaleUpFlag = false;
		}

		if (m_spriteScaleUpFlag == true) {
			//�g��
			m_spriteBackScale += BUTTON_SCALE_ADD;
		}
		if (m_spriteScaleUpFlag == false) {
			//�k��
			m_spriteBackScale -= BUTTON_SCALE_ADD;
		}
		//�X�v���C�g�ɔ��f�B
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_BackButton)->SetScale({ m_spriteBackScale, m_spriteBackScale, m_spriteBackScale });

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_DecisionButton)->SetScale({ DECISION_BUTTON_SIZE_MIN ,DECISION_BUTTON_SIZE_MIN ,DECISION_BUTTON_SIZE_MIN });

		break;

		//�u�����Ă��v�{�^�����I�΂�Ă���Ƃ��A
	 case KetteiButton:
		//�{�^����s�����x100���ɂ���B
		 m_stageSelectLevel2D->GetSprite(enStageSelectSprite_DecisionButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (m_spriteDecisionScale < DECISION_BUTTON_SIZE_MIN) {
			m_spriteScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (m_spriteDecisionScale > DECISION_BUTTON_SIZE_MAX) {
			m_spriteScaleUpFlag = false;
		}

		if (m_spriteScaleUpFlag == true) {
			//�g��
			m_spriteDecisionScale += BUTTON_SCALE_ADD;
		}
		if (m_spriteScaleUpFlag == false) {
			//�k��
			m_spriteDecisionScale -= BUTTON_SCALE_ADD;
		}
		//�X�v���C�g�ɔ��f�B
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_DecisionButton)->SetScale({ m_spriteDecisionScale,m_spriteDecisionScale,m_spriteDecisionScale });

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_BackButton)->SetScale({ BACK_BUTTON_SIZE_MIN ,BACK_BUTTON_SIZE_MIN ,BACK_BUTTON_SIZE_MIN });

		break;
	};

	//�X�e�[�W�I��

	//���ݑI������Ă���X�e�[�W��1�̂Ƃ��A
	if (m_nowSelectStage == Stage_One)
	{
		//�������\������
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_Select_Left)->Deactivate();
		//LB���\������
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_LB)->Deactivate();
	}
	//�X�e�[�W�P�ȊO�̎��A
	else
	{
		//������\������
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_Select_Left)->Activate();
		//LB��\������
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_LB)->Activate();
	}
	//���ݑI������Ă���X�e�[�W���Ō�̃X�e�[�W�̂Ƃ��A
	if (m_nowSelectStage == Stage_Four)
	{
		//�E�����\������
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_Select_Right)->Deactivate();
		//RB���\������
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_RB)->Deactivate();
	}
	//�Ō�̃X�e�[�W�ȊO�̎��A
	else
	{
		//�E����\������
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_Select_Right)->Activate();
		//RB��\������
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_RB)->Activate();
	}

	//LB�{�^���������ꂽ��A(�L�[�{�[�hB)
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonLB1))
	{
		//�X�e�[�W1���I�΂�Ă��Ȃ��Ƃ�����1���ɂ��炷
		if (m_nowSelectStage != Stage_One)
		{
			//�ړ����ʉ��炷�B
			SoundManager::GetInstance()->Play(enSE_CursolMove);
			//�X�e�[�W�ԍ����P���ɂ��炷
			m_nowSelectStage--;
		}
	}
	//RB�{�^���������ꂽ��A(�L�[�{�[�h��7)
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonRB1))
	{
		if (m_nowSelectStage != Stage_Four) {
			//�ړ����ʉ��炷�B
			SoundManager::GetInstance()->Play(enSE_CursolMove);
			//�X�e�[�W�ԍ����P��ɂ��炷
			m_nowSelectStage++;
		}
	}
	//�X�e�[�W1,�X�e�[�W2�Ȃǂ̕����摜�\��
	switch (m_nowSelectStage)
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

		switch (m_nowSelect) {

			//�u���ǂ�v�{�^�����I�΂�Ă���Ƃ��A
		 case BackButton:
			//�^�C�g����ʂɑJ�ځB
			NewGO<TitleScene>(enPriority_Zeroth);

			break;

			//�u����v�{�^�����I�΂�Ă���Ƃ��A
		 case KetteiButton:
			 m_game = NewGO<Game>(enPriority_Zeroth, "game");
			 //�Q�[����ʂɑJ��
			 m_game->SetStageNum(m_nowSelectStage);
			break;
		};
		//�N���X���폜�B
		DeleteGO(this);
	}
}