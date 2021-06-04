#include "stdafx.h"
#include "Game.h"
#include "RuleScene.h"
#include "RuleLevel2D.h"
#include "TitleScene.h"

namespace{
	const int NUM_HOGE = 10;
	const float MOVE_SPEED = 100;
	const int BAR = 10;
}
bool RuleScene::Start()
{
	//���[����ʕ\��
	m_sprite = NewGO<RuleLevel2D>(0,"RuleLevel2D");

	//BGM�Đ�
	SoundManager::GetInstance()->Play(BGM_Title);

	//�͂��߂���Start�֐���NewGO����
	//��
	m_keySpriteRender[0] = NewGO<SpriteRender>(2);
	m_keySpriteRender[0]->SetPosition({ 300.0f,-30.0f,0.0f });
	m_keySpriteRender[0]->Init("Assets/Level2D/KeyGet.dds", 150.0f, 150.0f);
	//�ԃ{�[��
	m_keySpriteRender[1] = NewGO<SpriteRender>(2);
	m_keySpriteRender[1]->SetPosition({ -300.0f,-30.0f,0.0f });
	m_keySpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
	//Start!
	m_keySpriteRender[2] = NewGO<SpriteRender>(1);
	m_keySpriteRender[2]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_keySpriteRender[2]->Init("Assets/image/Start!!.dds", 350.0f, 350.0f);
	m_keySpriteRender[2]->SetScale({1.3f,1.3f,1.3f});
	//Get
	m_keySpriteRender[3] = NewGO<SpriteRender>(1);
	m_keySpriteRender[3]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_keySpriteRender[3]->Init("Assets/image/Get.dds", 350.0f, 350.0f);
	m_keySpriteRender[3]->SetScale({ 1.3f,1.3f,1.3f });
	m_keySpriteRender[3]->Deactivate();		//��\��
	//Goal
	m_keySpriteRender[4] = NewGO<SpriteRender>(1);
	m_keySpriteRender[4]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_keySpriteRender[4]->Init("Assets/image/Goal.dds", 350.0f, 350.0f);
	m_keySpriteRender[4]->SetScale({ 1.3f,1.3f,1.3f });
	m_keySpriteRender[4]->Deactivate();		//��\��
	//1/4
	m_quarterSpriteRender[0] = NewGO<SpriteRender>(2);
	m_quarterSpriteRender[0]->SetPosition({ 0.0f,-280.0f,0.0f });
	m_quarterSpriteRender[0]->Init("Assets/image/OneQuarter.dds", 500.0f, 500.0f);

	//�X�^�[�g�֐���return true;
	return true;
}

RuleScene::~RuleScene()
{
	//���[����ʂ̃��x�����폜�B
	DeleteGO(m_sprite);

	for (int i = 0; i < 6; i++)
	{
		DeleteGO(m_deathSpriteRender[i]);
		m_deathSpriteRender[i] = nullptr;
	}
	DeleteGO(m_quarterSpriteRender[3]);
	for (int i = 0; i < 5; i++)
	{
		DeleteGO(m_keySpriteRender[i]);
		m_keySpriteRender[i] = nullptr;
	}
	DeleteGO(m_quarterSpriteRender[0]);
	m_quarterSpriteRender[0] = nullptr;

	//�^�C�g��BGM���폜�B
	SoundManager::GetInstance()->Release(BGM_Title);
}

void RuleScene::Update()
{
	//�{�^����S�Ĕ������ɂ���B
	for (int i = 1; i < 3; i++) {
		m_sprite->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

	//�E����or�����͂��ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//���݃Z���N�g����Ă���{�^�����u���ǂ�v(0��)��������A
		if (m_nowSelect == 0) {
			//�I�����E��1���炷�B
			m_nowSelect += 1;
		}
		//���݃Z���N�g����Ă���{�^�����u���v(1��)��������A
		else {
			//�I��������1���炷�B
			m_nowSelect -= 1;
		}
		//�ړ����ʉ��炷�B
		SoundManager::GetInstance()->Play(SE_CursolMove);
	}

	//���ݑI�����Ă���{�^���̋����\��
	switch (m_nowSelect) {

		//�u�͂��߂�v�{�^�����I�΂�Ă���Ƃ��A
	 case back:
		//�{�^����s�����x100���ɂ���B
		 m_sprite->GetSprite(1)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (m_scale < 0.20f) {
			m_scaleUpFlg = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (m_scale > 0.225f) {
			m_scaleUpFlg = false;
		}

		if (m_scaleUpFlg == true) {
			//�g��
			m_scale += 0.0005f;
		}
		if (m_scaleUpFlg == false) {
			//�k��
			m_scale -= 0.0005f;
		}
		//�X�v���C�g�ɔ��f�B
		m_scale2 = { m_scale,m_scale,m_scale };
		m_sprite->GetSprite(1)->SetScale(m_scale2);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_sprite->GetSprite(2)->SetScale(m_scale3);

		break;

		//�u�����т����v�{�^�����I�΂�Ă���Ƃ��A
	 case next:
		//�{�^����s�����x100���ɂ���B
		 m_sprite->GetSprite(2)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		//�傫�����ŏ��ɂȂ����Ƃ��A
		if (m_scale < 0.20f) {
			m_scaleUpFlg = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (m_scale > 0.225f) {
			m_scaleUpFlg = false;
		}

		if (m_scaleUpFlg == true) {
			//�g��
			m_scale += 0.0005f;
		}
		if (m_scaleUpFlg == false) {
			//�k��
			m_scale -= 0.0005f;
		}
		//�X�v���C�g�ɔ��f�B
		m_scale2 = { m_scale,m_scale,m_scale };
		m_sprite->GetSprite(2)->SetScale(m_scale2);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_sprite->GetSprite(1)->SetScale(m_scale3);

		break;
	};

	//A�{�^��(�L�[�{�[�h��J)�������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//����{�^�����Đ��B
		SoundManager::GetInstance()->Play(SE_DecisionButton);

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
			m_keySpriteRender[0] = NewGO<SpriteRender>(2);
			m_keySpriteRender[0]->SetPosition({ 300.0f,-30.0f,0.0f });
			m_keySpriteRender[0]->Init("Assets/Level2D/KeyGet.dds", 150.0f, 150.0f);

			m_keySpriteRender[1] = NewGO<SpriteRender>(2);
			m_keySpriteRender[1]->SetPosition({ -300.0f,-100.0f,0.0f });
			m_keySpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);

			m_keySpriteRender[2] = NewGO<SpriteRender>(1);
			m_keySpriteRender[2]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_keySpriteRender[2]->Init("Assets/image/Start!!.dds", 350.0f, 350.0f);
			m_keySpriteRender[2]->SetScale({ 1.3f,1.3f,1.3f });
			m_keySpriteRender[2]->Deactivate();		//��\��

			m_keySpriteRender[3] = NewGO<SpriteRender>(1);
			m_keySpriteRender[3]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_keySpriteRender[3]->Init("Assets/image/Get.dds", 350.0f, 350.0f);
			m_keySpriteRender[3]->SetScale({ 1.3f,1.3f,1.3f });
			m_keySpriteRender[3]->Deactivate();		//��\��

			m_keySpriteRender[4] = NewGO<SpriteRender>(1);
			m_keySpriteRender[4]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_keySpriteRender[4]->Init("Assets/image/Goal.dds", 350.0f, 350.0f);
			m_keySpriteRender[4]->SetScale({ 1.3f,1.3f,1.3f });
			m_keySpriteRender[4]->Deactivate();		//��\��
			m_quarterSpriteRender[0] = NewGO<SpriteRender>(2);
			m_quarterSpriteRender[0]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_quarterSpriteRender[0]->Init("Assets/image/OneQuarter.dds", 500.0f, 500.0f);
			
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
			m_inryokuSpriteRender[0] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[0]->SetPosition({ 100.0f,-30.0f,0.0f });
			m_inryokuSpriteRender[0]->Init("Assets/image/Yazirusi01.dds", 800.0f, 400.0f);
			m_inryokuSpriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });		//�������ɂ���
			//�ԃ{�[���\��
			m_inryokuSpriteRender[1] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[1]->SetPosition({ -300.0f,50.0f,0.0f });
			m_inryokuSpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//�{�[���\��
			m_inryokuSpriteRender[2] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[2]->SetPosition({ -300.0f,-100.0f,0.0f });
			m_inryokuSpriteRender[2]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//�}�O�l�b�g(��)�\��
			m_inryokuSpriteRender[3] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[3]->SetPosition({ 300.0f,50.0f,0.0f });
			m_inryokuSpriteRender[3]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_inryokuSpriteRender[3]->SetScale({ -1.2,-1.2,1.2 });		//�����傫������(+���])
			//�}�O�l�b�g(��)�\��
			m_inryokuSpriteRender[4] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[4]->SetPosition({ 300.0f,-100.0f,0.0f });
			m_inryokuSpriteRender[4]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_inryokuSpriteRender[4]->SetScale({ 1.2,1.2,1.2 });		//�����傫������
			//���͕����\��
			m_inryokuSpriteRender[5] = NewGO<SpriteRender>(1);
			m_inryokuSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_inryokuSpriteRender[5]->Init("Assets/image/Inryoku.dds", 350.0f, 350.0f);
			m_inryokuSpriteRender[5]->SetScale({ 1.3,1.3,1.3 });		//�����傫������
			//2/4�\��
			m_quarterSpriteRender[1] = NewGO<SpriteRender>(2);
			m_quarterSpriteRender[1]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_quarterSpriteRender[1]->Init("Assets/image/TwoQuarters.dds", 500.0f, 500.0f);

			//1�y�[�W��
			if (m_nextPageFlg)
			{
				for (int i = 0; i < 5; i++)
				{
					DeleteGO(m_keySpriteRender[i]);		//���Ɛԃ{�[���X�v���C�g�폜
					m_keySpriteRender[i] = nullptr;
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
	 //�^�C�g���ɖ߂�B
	 case ZeroPage:

		//�N���X�̔j��
		DeleteGO(this);

		//�^�C�g����ʂ���X�^�[�g
		NewGO<TitleScene>(0);

		break;

	 case OnePage:
		 m_onePageTimer++;
		 if (m_onePageTimer < 110)
		 {
			 m_keySpriteRender[2]->Activate();		//�\��
			 //�{�[���̈ʒu���E�ɂ��炵�Ă����B
			 m_onePageBallPos += 5;
		 }
		 //���̏ꏊ�܂ōs������A
		 else if(110<= m_onePageTimer && m_onePageTimer <=200)
		 {
			 m_keySpriteRender[2]->Deactivate();		//��\��
			 m_keySpriteRender[3]->Activate();		//�\��

			 m_keyPos.y += 1.0f;
			 m_keySpriteRender[0]->SetPosition({ m_keyPos });		//���̈ʒu�X�V
		 }
		 else if (200 < m_onePageTimer && m_onePageTimer < 310)
		 {
			 m_keySpriteRender[3]->Activate();		//�\��

			 //�{�[���̈ʒu�����ɂ��炵�Ă����B
			 m_onePageBallPos -= 5;
			 m_keySpriteRender[0]->SetPosition({ m_onePageBallPos,m_keyPos.y,m_keyPos.z });		//���̈ʒu�X�V
		 }
		 else if (310 <= m_onePageTimer && m_onePageTimer <=400)
		 {
			 m_keySpriteRender[3]->Deactivate();		//��\��
			 m_keySpriteRender[4]->Activate();		//�\��
		 }
		 else
		 {
			 m_keySpriteRender[4]->Deactivate();		//�\��
			 m_keySpriteRender[2]->Activate();		//�\��
			 //���̎����グ����y���W��߂��B(������)
			 m_keyPos = { 300.0f,-30.0f,0.0f };
			 m_keySpriteRender[0]->SetPosition({ m_keyPos });		//���̈ʒu�X�V
			 //�^�C�}�[�����������ď��߂�if���ɖ߂�
			 m_onePageTimer = 0;
		 }

		 m_keySpriteRender[1]->SetPosition({ m_onePageBallPos,-30.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V

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

	 //�^�C�g���ɖ߂�B
	 case FivePage:

		 DeleteGO(this);

		 //�^�C�g����ʂ���X�^�[�g
		 NewGO<TitleScene>(0);

		 break;
	}
}