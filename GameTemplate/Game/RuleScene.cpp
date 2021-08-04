#include "stdafx.h"
#include "Game.h"
#include "RuleScene.h"
#include "RuleLevel2D.h"
#include "TitleScene.h"
#include "RuleSceneConstData.h"

namespace{
	
}
bool RuleScene::Start()
{
	//�y�[�W�ԍ���1�y�[�W�ڂɐݒ�B
	m_pageNum = OnePage;
	//�I���󋵂��u���v�ɐݒ�B
	m_nowSelect = next;
	//���[����ʂ𐶐��B
	m_level2D = NewGO<RuleLevel2D>(enPriority_Zeroth, NAME_RULE_LEVEL2D);

	//BGM�Đ�
	SoundManager::GetInstance()->Play(enBGM_Title);

	//�͂��߂���Start�֐���NewGO����
	//��
	m_page1SpriteRender[Page1Sprite_Key] = NewGO<SpriteRender>(enPriority_Second);
	m_page1SpriteRender[Page1Sprite_Key]->SetPosition(SPRITE_POS_KEY);
	m_page1SpriteRender[Page1Sprite_Key]->Init(SPRITE_NAME_KEY, SPRITE_WH_KEY.x, SPRITE_WH_KEY.y);
	//�ԃ{�[��
	m_page1SpriteRender[Page1Sprite_RedBall] = NewGO<SpriteRender>(enPriority_Second);
	m_page1SpriteRender[Page1Sprite_RedBall]->SetPosition(SPRITE_POS_RED_BALL);
	m_page1SpriteRender[Page1Sprite_RedBall]->Init(SPRITE_NAME_RED_BALL, SPRITE_WH_RED_BALL.x, SPRITE_WH_RED_BALL.y);
	//Start!
	m_page1SpriteRender[Page1Sprite_Start] = NewGO<SpriteRender>(enPriority_First);
	m_page1SpriteRender[Page1Sprite_Start]->SetPosition(SPRITE_POS_START);
	m_page1SpriteRender[Page1Sprite_Start]->Init(SPRITE_NAME_START, SPRITE_WH_START.x, SPRITE_WH_START.y);
	m_page1SpriteRender[Page1Sprite_Start]->SetScale(SPRITE_SCALE_START);
	//Get
	m_page1SpriteRender[Page1Sprite_Get] = NewGO<SpriteRender>(enPriority_First);
	m_page1SpriteRender[Page1Sprite_Get]->SetPosition(SPRITE_POS_GET);
	m_page1SpriteRender[Page1Sprite_Get]->Init(SPRITE_NAME_GET, SPRITE_WH_GET.x, SPRITE_WH_GET.y);
	m_page1SpriteRender[Page1Sprite_Get]->SetScale(SPRITE_SCALE_GET);
	m_page1SpriteRender[Page1Sprite_Get]->Deactivate();		//��\��
	//Goal
	m_page1SpriteRender[Page1Sprite_Goal] = NewGO<SpriteRender>(enPriority_First);
	m_page1SpriteRender[Page1Sprite_Goal]->SetPosition(SPRITE_POS_GOAL);
	m_page1SpriteRender[Page1Sprite_Goal]->Init(SPRITE_NAME_GOAL, SPRITE_WH_GOAL.x, SPRITE_WH_GOAL.y);
	m_page1SpriteRender[Page1Sprite_Goal]->SetScale(SPRITE_SCALE_GOAL);
	m_page1SpriteRender[Page1Sprite_Goal]->Deactivate();		//��\��
	//1/4
	m_quarterSpriteRender[OnePage] = NewGO<SpriteRender>(enPriority_Second);
	m_quarterSpriteRender[OnePage]->SetPosition(SPRITE_POS_QUARTER_ONE);
	m_quarterSpriteRender[OnePage]->Init(SPRITE_NAME_QUARTER_ONE, SPRITE_WH_QUARTER_ONE.x, SPRITE_WH_QUARTER_ONE.y);

	//�X�^�[�g�֐���return true;
	return true;
}

RuleScene::~RuleScene()
{
	//���[����ʂ̃��x�����폜�B
	DeleteGO(m_level2D);

	for (int i = 0; i < 6; i++)
	{
		DeleteGO(m_deathSpriteRender[i]);
		m_deathSpriteRender[i] = nullptr;
	}
	DeleteGO(m_quarterSpriteRender[3]);
	for (int i = 0; i < 5; i++)
	{
		DeleteGO(m_page1SpriteRender[i]);
		m_page1SpriteRender[i] = nullptr;
	}
	DeleteGO(m_quarterSpriteRender[0]);
	m_quarterSpriteRender[0] = nullptr;

	//�^�C�g��BGM���폜�B
	SoundManager::GetInstance()->Release(enBGM_Title);
}

void RuleScene::Update()
{
	//�{�^����S�Ĕ������ɂ���B
	m_level2D->GetSprite(enSprite_Back)->SetMulColor(TRANSLUCENT_VALUE_ONE_THIRD);
	m_level2D->GetSprite(enSprite_Next)->SetMulColor(TRANSLUCENT_VALUE_ONE_THIRD);

	//�E����or�����͂��ꂽ��A
	if (g_pad[PAD_0]->IsTrigger(enButtonRight) || g_pad[PAD_0]->IsTrigger(enButtonLeft)) {
		//���݃Z���N�g����Ă���{�^�����u���ǂ�v(0��)��������A
		if (m_nowSelect == back) {
			//�I�����E��1���炷�B
			m_nowSelect++;
		}
		//���݃Z���N�g����Ă���{�^�����u���v(1��)��������A
		else {
			//�I��������1���炷�B
			m_nowSelect--;
		}
		//�ړ����ʉ��炷�B
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}

	//���ݑI�����Ă���{�^���̋����\��
	switch (m_nowSelect) {

		//�u�͂��߂�v�{�^�����I�΂�Ă���Ƃ��A
	 case back:
		//�{�^����s�����x100���ɂ���B
		 m_level2D->GetSprite(enSprite_Back)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (m_scale < SPRITE_SCALE_MIN) {
			m_scaleUpFlg = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (m_scale > SPRITE_SCALE_MAX) {
			m_scaleUpFlg = false;
		}

		if (m_scaleUpFlg == true) {
			//�g��
			m_scale += BUTTON_SCALE_ADD;
		}
		if (m_scaleUpFlg == false) {
			//�k��
			m_scale -= BUTTON_SCALE_ADD;
		}
		//�X�v���C�g�ɔ��f�B
		m_scale2 = { m_scale,m_scale,m_scale };
		m_level2D->GetSprite(enSprite_Back)->SetScale(m_scale2);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_level2D->GetSprite(enSprite_Next)->SetScale(m_scale3);

		break;

		//�u�����т����v�{�^�����I�΂�Ă���Ƃ��A
	 case next:
		//�{�^����s�����x100���ɂ���B
		 m_level2D->GetSprite(enSprite_Next)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		//�P�U���̌������g���ă{�^�����g��k������B

		//�傫�����ŏ��ɂȂ����Ƃ��A
		if (m_scale < SPRITE_SCALE_MIN) {
			m_scaleUpFlg = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (m_scale > SPRITE_SCALE_MAX) {
			m_scaleUpFlg = false;
		}

		if (m_scaleUpFlg == true) {
			//�g��
			m_scale += BUTTON_SCALE_ADD;
		}
		if (m_scaleUpFlg == false) {
			//�k��
			m_scale -= BUTTON_SCALE_ADD;
		}
		//�X�v���C�g�ɔ��f�B
		m_scale2 = { m_scale,m_scale,m_scale };
		m_level2D->GetSprite(enSprite_Next)->SetScale(m_scale2);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_level2D->GetSprite(enSprite_Back)->SetScale(m_scale3);

		break;
	};

	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[PAD_0]->IsTrigger(enButtonA)) {

		//����{�^�����Đ��B
		SoundManager::GetInstance()->Play(enSE_DecisionButton);

		switch (m_nowSelect) {

			//�u���ǂ�v�{�^�����I�΂ꂽ�Ƃ��A
		 case back:
			 //�y�[�W��O�ɖ߂��B
			 m_pageNum--;

			m_nextPageFlg = false;

			break;

			//�u���v�{�^�����I�΂ꂽ�Ƃ��A
		 case next:
			 //�y�[�W�����ɐi�߂�B
			 m_pageNum++;

			m_nextPageFlg = true;

			break;
		};

		switch (m_pageNum)
		{
			//1�y�[�W��
		case OnePage:
			//��
			m_page1SpriteRender[Page1Sprite_Key] = NewGO<SpriteRender>(enPriority_Second);
			m_page1SpriteRender[Page1Sprite_Key]->SetPosition(SPRITE_POS_KEY);
			m_page1SpriteRender[Page1Sprite_Key]->Init(SPRITE_NAME_KEY, SPRITE_WH_KEY.x, SPRITE_WH_KEY.y);
			//�ԃ{�[��
			m_page1SpriteRender[Page1Sprite_RedBall] = NewGO<SpriteRender>(enPriority_Second);
			m_page1SpriteRender[Page1Sprite_RedBall]->SetPosition(SPRITE_POS_RED_BALL);
			m_page1SpriteRender[Page1Sprite_RedBall]->Init(SPRITE_NAME_RED_BALL, SPRITE_WH_RED_BALL.x, SPRITE_WH_RED_BALL.y);
			//Start!
			m_page1SpriteRender[Page1Sprite_Start] = NewGO<SpriteRender>(enPriority_First);
			m_page1SpriteRender[Page1Sprite_Start]->SetPosition(SPRITE_POS_START);
			m_page1SpriteRender[Page1Sprite_Start]->Init(SPRITE_NAME_START, SPRITE_WH_START.x, SPRITE_WH_START.y);
			m_page1SpriteRender[Page1Sprite_Start]->SetScale(SPRITE_SCALE_START);
			//Get
			m_page1SpriteRender[Page1Sprite_Get] = NewGO<SpriteRender>(enPriority_First);
			m_page1SpriteRender[Page1Sprite_Get]->SetPosition(SPRITE_POS_GET);
			m_page1SpriteRender[Page1Sprite_Get]->Init(SPRITE_NAME_GET, SPRITE_WH_GET.x, SPRITE_WH_GET.y);
			m_page1SpriteRender[Page1Sprite_Get]->SetScale(SPRITE_SCALE_GET);
			m_page1SpriteRender[Page1Sprite_Get]->Deactivate();		//��\��
			//Goal
			m_page1SpriteRender[Page1Sprite_Goal] = NewGO<SpriteRender>(enPriority_First);
			m_page1SpriteRender[Page1Sprite_Goal]->SetPosition(SPRITE_POS_GOAL);
			m_page1SpriteRender[Page1Sprite_Goal]->Init(SPRITE_NAME_GOAL, SPRITE_WH_GOAL.x, SPRITE_WH_GOAL.y);
			m_page1SpriteRender[Page1Sprite_Goal]->SetScale(SPRITE_SCALE_GOAL);
			m_page1SpriteRender[Page1Sprite_Goal]->Deactivate();		//��\��
			//1/4
			m_quarterSpriteRender[OnePage] = NewGO<SpriteRender>(enPriority_Second);
			m_quarterSpriteRender[OnePage]->SetPosition(SPRITE_POS_QUARTER_ONE);
			m_quarterSpriteRender[OnePage]->Init(SPRITE_NAME_QUARTER_ONE, SPRITE_WH_QUARTER_ONE.x, SPRITE_WH_QUARTER_ONE.y);
			
			for (int i = 0; i < 6; i++)
			{
				DeleteGO(m_inryokuSpriteRender[i]);		//�����̓X�v���C�g�폜
				m_inryokuSpriteRender[i] = nullptr;
			}
			DeleteGO(m_quarterSpriteRender[1]);		//2/4�X�v���C�g�폜
			m_quarterSpriteRender[1] = nullptr;

			break;

			//2�y�[�W��
		case TwoPage:
			
			//�E���\��
			m_inryokuSpriteRender[Page2Sprite_Arrow] = NewGO<SpriteRender>(enPriority_Second);
			m_inryokuSpriteRender[Page2Sprite_Arrow]->SetPosition(SPRITE_POS_RIGHT_ARROW);
			m_inryokuSpriteRender[Page2Sprite_Arrow]->Init(SPRITE_NAME_RIGHT_ARROW, SPRITE_WH_RIGHT_ARROW.x, SPRITE_WH_RIGHT_ARROW.y);
			m_inryokuSpriteRender[Page2Sprite_Arrow]->SetMulColor(TRANSLUCENT_VALUE_HALF);		//�������ɂ���
			//�ԃ{�[���\��
			m_inryokuSpriteRender[Page2Sprite_Red_Ball] = NewGO<SpriteRender>(enPriority_Second);
			m_inryokuSpriteRender[Page2Sprite_Red_Ball]->SetPosition(SPRITE_POS_RED_BALL_PAGE2);
			m_inryokuSpriteRender[Page2Sprite_Red_Ball]->Init(SPRITE_NAME_RED_BALL_PAGE2, SPRITE_WH_RED_BALL_PAGE2.x, SPRITE_WH_RED_BALL_PAGE2.y);
			//�{�[���\��
			m_inryokuSpriteRender[Page2Sprite_Blue_Ball] = NewGO<SpriteRender>(enPriority_Second);
			m_inryokuSpriteRender[Page2Sprite_Blue_Ball]->SetPosition({ -300.0f,-100.0f,0.0f });
			m_inryokuSpriteRender[Page2Sprite_Blue_Ball]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//�}�O�l�b�g(��)�\��
			m_inryokuSpriteRender[Page2Sprite_Magnet01] = NewGO<SpriteRender>(enPriority_Second);
			m_inryokuSpriteRender[Page2Sprite_Magnet01]->SetPosition({ 300.0f,50.0f,0.0f });
			m_inryokuSpriteRender[Page2Sprite_Magnet01]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_inryokuSpriteRender[Page2Sprite_Magnet01]->SetScale({ -1.2f,-1.2f,1.2f });		//�����傫������(+���])
			//�}�O�l�b�g(��)�\��
			m_inryokuSpriteRender[Page2Sprite_Magnet02] = NewGO<SpriteRender>(enPriority_Second);
			m_inryokuSpriteRender[Page2Sprite_Magnet02]->SetPosition({ 300.0f,-100.0f,0.0f });
			m_inryokuSpriteRender[Page2Sprite_Magnet02]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_inryokuSpriteRender[Page2Sprite_Magnet02]->SetScale({ 1.2,1.2,1.2f });		//�����傫������
			//���͕����\��
			m_inryokuSpriteRender[Page2Sprite_Inryoku] = NewGO<SpriteRender>(enPriority_First);
			m_inryokuSpriteRender[Page2Sprite_Inryoku]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_inryokuSpriteRender[Page2Sprite_Inryoku]->Init("Assets/image/Inryoku.dds", 350.0f, 350.0f);
			m_inryokuSpriteRender[Page2Sprite_Inryoku]->SetScale({ 1.3f,1.3f,1.3f });		//�����傫������
			//2/4�\��
			m_quarterSpriteRender[1] = NewGO<SpriteRender>(enPriority_Second);
			m_quarterSpriteRender[1]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_quarterSpriteRender[1]->Init("Assets/image/TwoQuarters.dds", 500.0f, 500.0f);

			//1�y�[�W��
			if (m_nextPageFlg)
			{
				for (int i = 0; i < 5; i++)
				{
					DeleteGO(m_page1SpriteRender[i]);		//���Ɛԃ{�[���X�v���C�g�폜
					m_page1SpriteRender[i] = nullptr;
				}
				DeleteGO(m_quarterSpriteRender[0]);		//1/4�X�v���C�g�폜
				m_quarterSpriteRender[0] = nullptr;
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_sekiryokuSpriteRender[i]);		//���˗̓X�v���C�g�폜
					m_sekiryokuSpriteRender[i] = nullptr;
				}
				DeleteGO(m_quarterSpriteRender[2]);		//3/4�X�v���C�g�폜
				m_quarterSpriteRender[2] = nullptr;
			}

			break;

			//3�y�[�W��
		case ThreePage:

			//�����\��
			m_sekiryokuSpriteRender[0] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[0]->SetPosition({ 100.0f,-30.0f,0.0f });
			m_sekiryokuSpriteRender[0]->Init("Assets/image/Yazirusi02.dds", 800.0f, 400.0f);
			m_sekiryokuSpriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });		//�������ɂ���
			//�ԃ{�[���\��
			m_sekiryokuSpriteRender[1] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[1]->SetPosition({ 125.0f,50.0f,0.0f });
			m_sekiryokuSpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//�{�[���\��
			m_sekiryokuSpriteRender[2] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[2]->SetPosition({ 125.0f,-100.0f,0.0f });
			m_sekiryokuSpriteRender[2]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//�}�O�l�b�g(��)�\��
			m_sekiryokuSpriteRender[3] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[3]->SetPosition({ 300.0f,50.0f,0.0f });
			m_sekiryokuSpriteRender[3]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_sekiryokuSpriteRender[3]->SetScale({ 1.2,1.2,1.2 });
			//�}�O�l�b�g(��)�\��
			m_sekiryokuSpriteRender[4] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[4]->SetPosition({ 300.0f,-100.0f,0.0f });
			m_sekiryokuSpriteRender[4]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);		//�����傫������
			m_sekiryokuSpriteRender[4]->SetScale({ -1.2,-1.2,1.2 });		//�����傫������(+���])
			//�˗͕����\��
			m_sekiryokuSpriteRender[5] = NewGO<SpriteRender>(1);
			m_sekiryokuSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_sekiryokuSpriteRender[5]->Init("Assets/image/Sekiryoku.dds", 350.0f, 350.0f);
			m_sekiryokuSpriteRender[5]->SetScale({ 1.3,1.3,1.3 });		//�����傫������
			//3/4�\��
			m_quarterSpriteRender[2] = NewGO<SpriteRender>(2);
			m_quarterSpriteRender[2]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_quarterSpriteRender[2]->Init("Assets/image/ThreeQuarters.dds", 500.0f, 500.0f);
			if (m_nextPageFlg)
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_inryokuSpriteRender[i]);		//�����̓X�v���C�g�폜
					m_inryokuSpriteRender[i] = nullptr;
				}
				DeleteGO(m_quarterSpriteRender[1]);		//2/4�X�v���C�g�폜
				m_quarterSpriteRender[1] = nullptr;
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_deathSpriteRender[i]);		//���ʏ��X�v���C�g�폜
					m_deathSpriteRender[i] = nullptr;
				}
				DeleteGO(m_quarterSpriteRender[3]);		//4/4�X�v���C�g�폜
				m_quarterSpriteRender[3] = nullptr;
			}

			break;

			//4�y�[�W��
		case FourPage:
			//�ԃ{�[���摜�\��
			m_deathSpriteRender[0] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[0]->SetPosition({ -250.0f,50.0f,0.0f });
			m_deathSpriteRender[0]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//�{�[���摜�\��
			m_deathSpriteRender[1] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[1]->SetPosition({ -250.0f,-100.0f,0.0f });
			m_deathSpriteRender[1]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//���ʏ��摜�\��
			m_deathSpriteRender[2] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[2]->SetPosition({ 300.0f,-30.0f,0.0f });
			m_deathSpriteRender[2]->SetScale({ 1.2f,1.2f,1.2f });		//������������������傫������
			m_deathSpriteRender[2]->Init("Assets/image/DeathFloor.dds", 350.0f, 350.0f);
			//�o�c(1)�摜�\��
			m_deathSpriteRender[3] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[3]->SetPosition({ 230.0f,50.0f,0.0f });
			m_deathSpriteRender[3]->SetScale({ 0.5f,0.5f,0.5f });		//������������������傫������
			m_deathSpriteRender[3]->Init("Assets/image/Batu.dds", 350.0f, 350.0f);
			m_deathSpriteRender[3]->Deactivate();		//��\��
			//�o�c(2)�摜�\��
			m_deathSpriteRender[4] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[4]->SetPosition({ 230.0f,-100.0f,0.0f });
			m_deathSpriteRender[4]->SetScale({ 0.5f,0.5f,0.5f });		//������������������傫������
			m_deathSpriteRender[4]->Init("Assets/image/Batu.dds", 350.0f, 350.0f);
			m_deathSpriteRender[4]->Deactivate();		//��\��
			//Dame�摜�\��
			m_deathSpriteRender[5] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_deathSpriteRender[5]->SetScale({ 1.5f,1.5f,1.5f });		//������������������傫������
			m_deathSpriteRender[5]->Init("Assets/image/Dame.dds", 350.0f, 350.0f);
			m_deathSpriteRender[5]->Deactivate();		//��\��
			//4/4�\��
			m_quarterSpriteRender[3] = NewGO<SpriteRender>(2);
			m_quarterSpriteRender[3]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_quarterSpriteRender[3]->Init("Assets/image/FourQuarters.dds", 500.0f, 500.0f);

			for (int i = 0; i < 6; i++)
			{
				DeleteGO(m_sekiryokuSpriteRender[i]);		//���˗̓X�v���C�g�폜
				m_sekiryokuSpriteRender[i] = nullptr;
			}
			DeleteGO(m_quarterSpriteRender[2]);		//3/4�X�v���C�g�폜
			m_quarterSpriteRender[2] = nullptr;

			break;
		}
	}

	//��ɌĂ΂��
	switch (m_pageNum)
	{
	 case OnePage:
		 m_onePageTimer++;
		 if (m_onePageTimer < 110)
		 {
			 m_page1SpriteRender[2]->Activate();		//�\��
			 //�{�[���̈ʒu���E�ɂ��炵�Ă����B
			 m_onePageBallPos += 5;
		 }
		 //���̏ꏊ�܂ōs������A
		 else if(110<= m_onePageTimer && m_onePageTimer <=200)
		 {
			 m_page1SpriteRender[2]->Deactivate();		//��\��
			 m_page1SpriteRender[3]->Activate();		//�\��

			 m_keyPos.y += 1.0f;
			 m_page1SpriteRender[0]->SetPosition({ m_keyPos });		//���̈ʒu�X�V
		 }
		 else if (200 < m_onePageTimer && m_onePageTimer < 310)
		 {
			 m_page1SpriteRender[3]->Activate();		//�\��

			 //�{�[���̈ʒu�����ɂ��炵�Ă����B
			 m_onePageBallPos -= 5;
			 m_page1SpriteRender[0]->SetPosition({ m_onePageBallPos,m_keyPos.y,m_keyPos.z });		//���̈ʒu�X�V
		 }
		 else if (310 <= m_onePageTimer && m_onePageTimer <=400)
		 {
			 m_page1SpriteRender[3]->Deactivate();		//��\��
			 m_page1SpriteRender[4]->Activate();		//�\��
		 }
		 else
		 {
			 m_page1SpriteRender[4]->Deactivate();		//�\��
			 m_page1SpriteRender[2]->Activate();		//�\��
			 //���̎����グ����y���W��߂��B(������)
			 m_keyPos = { 300.0f,-30.0f,0.0f };
			 m_page1SpriteRender[0]->SetPosition({ m_keyPos });		//���̈ʒu�X�V
			 //�^�C�}�[�����������ď��߂�if���ɖ߂�
			 m_onePageTimer = 0;
		 }

		 m_page1SpriteRender[1]->SetPosition({ m_onePageBallPos,-30.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V

		 break;

	 case TwoPage:

		 m_twoPageTimer++;
		 if (m_twoPageTimer < 108)
		 {
			 //�{�[���̈ʒu���E�ɂ��炵�Ă����B
			 m_twoPageBallPos += 4;
		 }
		 else if(108<= m_twoPageTimer && m_twoPageTimer <= 200)
		 {
			 //�Ȃɂ����Ȃ�
		 }
		 else
		 {
			 m_twoPageBallPos = -300.0f;//�{�[�����͂��߂̈ʒu�Ɏ����Ă����B
			 //�^�C�}�[�����������ď��߂�if���ɖ߂�
			 m_twoPageTimer = 0;
		 }

		 m_inryokuSpriteRender[1]->SetPosition({ m_twoPageBallPos,50.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V
		 m_inryokuSpriteRender[2]->SetPosition({ m_twoPageBallPos,-100.0f,0.0f });		//�{�[���̈ʒu�X�V

		break;

	 case ThreePage:

		 m_threePageTimer++;
		 if (m_threePageTimer < 108)
		 {
			 //�{�[���̈ʒu���E�ɂ��炵�Ă����B
			 m_threePageBallPos -= 4;
		 }
		 else if (108 <= m_threePageTimer && m_threePageTimer <= 200)
		 {
			 //�Ȃɂ����Ȃ�
		 }
		 else
		 {
			 m_threePageBallPos =  125.0f;//�{�[�����͂��߂̈ʒu�Ɏ����Ă����B
			 //�^�C�}�[�����������ď��߂�if���ɖ߂�
			 m_threePageTimer = 0;
		 }

		 m_sekiryokuSpriteRender[1]->SetPosition({ m_threePageBallPos,50.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V
		 m_sekiryokuSpriteRender[2]->SetPosition({ m_threePageBallPos,-100.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V

		break;

	 case FourPage:
		 m_fourPageTimer++;
		 if (m_fourPageTimer < 85)
		 {
			 //�{�[���̈ʒu���E�ɂ��炵�Ă����B
			 m_fourPageBallPos += 5;
		 }
		 else
		 {
			 m_deathSpriteRender[3]->Activate();		//�\��
			 m_deathSpriteRender[4]->Activate();		//�\��
			 m_deathSpriteRender[5]->Activate();		//�\��

			 if (m_fourPageTimer > 200)
			 {
				 m_fourPageBallPos = -250.0f;		//�{�[�����͂��߂̈ʒu�Ɏ����Ă����B
				 m_fourPageTimer = 0;		//�^�C�}�[���������ď��if�ɖ߂�B
				 m_deathSpriteRender[3]->Deactivate();		//��\��
				 m_deathSpriteRender[4]->Deactivate();		//��\��
				 m_deathSpriteRender[5]->Deactivate();		//��\��
			 }
		 }
		 m_deathSpriteRender[0]->SetPosition({ m_fourPageBallPos,50.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V
		 m_deathSpriteRender[1]->SetPosition({ m_fourPageBallPos,-100.0f,0.0f });		//�{�[���̈ʒu�X�V
			break;
	 default:
		 //�N���X�̔j��
		 DeleteGO(this);

		 //�^�C�g����ʂ���X�^�[�g
		 NewGO<TitleScene>(0);

		 break;
	}
}