#include "stdafx.h"
#include "RuleScene.h"
#include "RuleLevel2D.h"
#include "TitleScene.h"


bool RuleScene::Start()
{
	//���[����ʕ\��
	sprite = NewGO<RuleLevel2D>(0,"RuleLevel2D");
	m_RuleLevel2D = FindGO<RuleLevel2D>("RuleLevel2D");

	//BGM�Đ�
	BGMSound = NewGO<CSoundSource>(0);
	BGMSound->Init(L"Assets/sound/TitleBGM.wav");
	BGMSound->SetVolume(1.0f);
	BGMSound->Play(true);		//���[�v�Đ��B

	//�͂��߂���Start�֐���NewGO����
	//��
	m_KeySpriteRender[0] = NewGO<SpriteRender>(2);
	m_KeySpriteRender[0]->SetPosition({ 300.0f,-30.0f,0.0f });
	m_KeySpriteRender[0]->Init("Assets/Level2D/KeyGet.dds", 150.0f, 150.0f);
	//�ԃ{�[��
	m_KeySpriteRender[1] = NewGO<SpriteRender>(2);
	m_KeySpriteRender[1]->SetPosition({ -300.0f,-30.0f,0.0f });
	m_KeySpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
	//Start!
	m_KeySpriteRender[2] = NewGO<SpriteRender>(1);
	m_KeySpriteRender[2]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_KeySpriteRender[2]->Init("Assets/image/Start!!.dds", 350.0f, 350.0f);
	m_KeySpriteRender[2]->SetScale({1.3f,1.3f,1.3f});
	//Get
	m_KeySpriteRender[3] = NewGO<SpriteRender>(1);
	m_KeySpriteRender[3]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_KeySpriteRender[3]->Init("Assets/image/Get.dds", 350.0f, 350.0f);
	m_KeySpriteRender[3]->SetScale({ 1.3f,1.3f,1.3f });
	m_KeySpriteRender[3]->Deactivate();		//��\��
	//Goal
	m_KeySpriteRender[4] = NewGO<SpriteRender>(1);
	m_KeySpriteRender[4]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_KeySpriteRender[4]->Init("Assets/image/Goal.dds", 350.0f, 350.0f);
	m_KeySpriteRender[4]->SetScale({ 1.3f,1.3f,1.3f });
	m_KeySpriteRender[4]->Deactivate();		//��\��
	//1/4
	m_QuarterSpriteRender[0] = NewGO<SpriteRender>(2);
	m_QuarterSpriteRender[0]->SetPosition({ 0.0f,-280.0f,0.0f });
	m_QuarterSpriteRender[0]->Init("Assets/image/OneQuarter.dds", 500.0f, 500.0f);

	//�X�^�[�g�֐���return true;
	return true;
}

RuleScene::~RuleScene()
{
	//���[����ʂ̃��x�����폜�B
	DeleteGO(sprite);

	for (int i = 0; i < 6; i++)
	{
		DeleteGO(m_DeathSpriteRender[i]);
	}
	DeleteGO(m_QuarterSpriteRender[3]);
	for (int i = 0; i < 5; i++)
	{
		DeleteGO(m_KeySpriteRender[i]);
	}
	DeleteGO(m_QuarterSpriteRender[0]);

	//�^�C�g��BGM���폜�B
	DeleteGO(BGMSound);
}

void RuleScene::Update()
{
	//�{�^����S�Ĕ������ɂ���B
	for (int i = 1; i < 3; i++) {
		m_RuleLevel2D->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

	//�E����or�����͂��ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//���݃Z���N�g����Ă���{�^�����u���ǂ�v(0��)��������A
		if (NowSelect  == 0) {
			//�I�����E��1���炷�B
			NowSelect += 1;
		}
		//���݃Z���N�g����Ă���{�^�����u���v(1��)��������A
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

	//���ݑI�����Ă���{�^���̋����\��
	switch (NowSelect) {

		//�u�͂��߂�v�{�^�����I�΂�Ă���Ƃ��A
	 case back:
		//�{�^����s�����x100���ɂ���B
		m_RuleLevel2D->GetSprite(1)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		 //�傫�����ŏ��ɂȂ����Ƃ��A
		if (Fscale < 0.20f) {
			ScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (Fscale > 0.225f) {
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
		m_RuleLevel2D->GetSprite(1)->SetScale(Vscale);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_RuleLevel2D->GetSprite(2)->SetScale(vscale);

		break;

		//�u�����т����v�{�^�����I�΂�Ă���Ƃ��A
	 case next:
		//�{�^����s�����x100���ɂ���B
		m_RuleLevel2D->GetSprite(2)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//�P�U���̌������g���ă{�^�����g��k������B

		//�傫�����ŏ��ɂȂ����Ƃ��A
		if (Fscale < 0.20f) {
			ScaleUpFlag = true;
		}
		//�傫�����ő�ɂȂ����Ƃ��A
		if (Fscale > 0.225f) {
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
		m_RuleLevel2D->GetSprite(2)->SetScale(Vscale);

		//�I������Ă��Ȃ��{�^���̊g�嗦�����ɖ߂��B
		m_RuleLevel2D->GetSprite(1)->SetScale(vscale);

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

			//�u���ǂ�v�{�^�����I�΂ꂽ�Ƃ��A
		 case back:
			 //�y�[�W��O�ɖ߂��B
			PageNum--;

			NextPageFlg = false;

			break;

			//�u���v�{�^�����I�΂ꂽ�Ƃ��A
		 case next:
			 //�y�[�W�����ɐi�߂�B
			PageNum++;

			NextPageFlg = true;

			break;
		};

		switch (PageNum)
		{
			//1�y�[�W��
		case OnePage:
			//���\��
			m_KeySpriteRender[0] = NewGO<SpriteRender>(2);
			m_KeySpriteRender[0]->SetPosition({ 300.0f,-30.0f,0.0f });
			m_KeySpriteRender[0]->Init("Assets/Level2D/KeyGet.dds", 150.0f, 150.0f);
			//�ԃ{�[��
			m_KeySpriteRender[1] = NewGO<SpriteRender>(2);
			m_KeySpriteRender[1]->SetPosition({ -300.0f,-100.0f,0.0f });
			m_KeySpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//Start!
			m_KeySpriteRender[2] = NewGO<SpriteRender>(1);
			m_KeySpriteRender[2]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_KeySpriteRender[2]->Init("Assets/image/Start!!.dds", 350.0f, 350.0f);
			m_KeySpriteRender[2]->SetScale({ 1.3f,1.3f,1.3f });
			m_KeySpriteRender[2]->Deactivate();		//��\��
			//Get
			m_KeySpriteRender[3] = NewGO<SpriteRender>(1);
			m_KeySpriteRender[3]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_KeySpriteRender[3]->Init("Assets/image/Get.dds", 350.0f, 350.0f);
			m_KeySpriteRender[3]->SetScale({ 1.3f,1.3f,1.3f });
			m_KeySpriteRender[3]->Deactivate();		//��\��
			//Goal
			m_KeySpriteRender[4] = NewGO<SpriteRender>(1);
			m_KeySpriteRender[4]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_KeySpriteRender[4]->Init("Assets/image/Goal.dds", 350.0f, 350.0f);
			m_KeySpriteRender[4]->SetScale({ 1.3f,1.3f,1.3f });
			m_KeySpriteRender[4]->Deactivate();		//��\��
			//1/4�\��
			m_QuarterSpriteRender[0] = NewGO<SpriteRender>(2);
			m_QuarterSpriteRender[0]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_QuarterSpriteRender[0]->Init("Assets/image/OneQuarter.dds", 500.0f, 500.0f);
			for (int i = 0; i < 6; i++)
			{
				DeleteGO(m_InryokuSpriteRender[i]);		//�����̓X�v���C�g�폜
			}
			DeleteGO(m_QuarterSpriteRender[1]);		//2/4�X�v���C�g�폜

			break;

			//2�y�[�W��
		case TwoPage:

			//�E���\��
			m_InryokuSpriteRender[0] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[0]->SetPosition({ 100.0f,-30.0f,0.0f });
			m_InryokuSpriteRender[0]->Init("Assets/image/Yazirusi01.dds", 800.0f, 400.0f);
			m_InryokuSpriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });		//�������ɂ���
			//�ԃ{�[���\��
			m_InryokuSpriteRender[1] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[1]->SetPosition({ -300.0f,50.0f,0.0f });
			m_InryokuSpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//�{�[���\��
			m_InryokuSpriteRender[2] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[2]->SetPosition({ -300.0f,-100.0f,0.0f });
			m_InryokuSpriteRender[2]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//�}�O�l�b�g(��)�\��
			m_InryokuSpriteRender[3] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[3]->SetPosition({ 300.0f,50.0f,0.0f });
			m_InryokuSpriteRender[3]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_InryokuSpriteRender[3]->SetScale({ -1.2,-1.2,1.2 });		//�����傫������(+���])
			//�}�O�l�b�g(��)�\��
			m_InryokuSpriteRender[4] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[4]->SetPosition({ 300.0f,-100.0f,0.0f });
			m_InryokuSpriteRender[4]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_InryokuSpriteRender[4]->SetScale({ 1.2,1.2,1.2 });		//�����傫������
			//���͕����\��
			m_InryokuSpriteRender[5] = NewGO<SpriteRender>(1);
			m_InryokuSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_InryokuSpriteRender[5]->Init("Assets/image/Inryoku.dds", 350.0f, 350.0f);
			m_InryokuSpriteRender[5]->SetScale({ 1.3,1.3,1.3 });		//�����傫������
			//2/4�\��
			m_QuarterSpriteRender[1] = NewGO<SpriteRender>(2);
			m_QuarterSpriteRender[1]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_QuarterSpriteRender[1]->Init("Assets/image/TwoQuarters.dds", 500.0f, 500.0f);

			//1�y�[�W��
			if (NextPageFlg)
			{
				for (int i = 0; i < 5; i++)
				{
					DeleteGO(m_KeySpriteRender[i]);		//���Ɛԃ{�[���X�v���C�g�폜
				}
				DeleteGO(m_QuarterSpriteRender[0]);		//1/4�X�v���C�g�폜
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_SekiryokuSpriteRender[i]);		//���˗̓X�v���C�g�폜
				}
				DeleteGO(m_QuarterSpriteRender[2]);		//3/4�X�v���C�g�폜
			}

			break;

			//3�y�[�W��
		case ThreePage:

			//�����\��
			m_SekiryokuSpriteRender[0] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[0]->SetPosition({ 100.0f,-30.0f,0.0f });
			m_SekiryokuSpriteRender[0]->Init("Assets/image/Yazirusi02.dds", 800.0f, 400.0f);
			m_SekiryokuSpriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });		//�������ɂ���
			//�ԃ{�[���\��
			m_SekiryokuSpriteRender[1] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[1]->SetPosition({ 125.0f,50.0f,0.0f });
			m_SekiryokuSpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//�{�[���\��
			m_SekiryokuSpriteRender[2] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[2]->SetPosition({ 125.0f,-100.0f,0.0f });
			m_SekiryokuSpriteRender[2]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//�}�O�l�b�g(��)�\��
			m_SekiryokuSpriteRender[3] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[3]->SetPosition({ 300.0f,50.0f,0.0f });
			m_SekiryokuSpriteRender[3]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_SekiryokuSpriteRender[3]->SetScale({ 1.2,1.2,1.2 });
			//�}�O�l�b�g(��)�\��
			m_SekiryokuSpriteRender[4] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[4]->SetPosition({ 300.0f,-100.0f,0.0f });
			m_SekiryokuSpriteRender[4]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);		//�����傫������
			m_SekiryokuSpriteRender[4]->SetScale({ -1.2,-1.2,1.2 });		//�����傫������(+���])
			//�˗͕����\��
			m_SekiryokuSpriteRender[5] = NewGO<SpriteRender>(1);
			m_SekiryokuSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_SekiryokuSpriteRender[5]->Init("Assets/image/Sekiryoku.dds", 350.0f, 350.0f);
			m_SekiryokuSpriteRender[5]->SetScale({ 1.3,1.3,1.3 });		//�����傫������
			//3/4�\��
			m_QuarterSpriteRender[2] = NewGO<SpriteRender>(2);
			m_QuarterSpriteRender[2]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_QuarterSpriteRender[2]->Init("Assets/image/ThreeQuarters.dds", 500.0f, 500.0f);
			if (NextPageFlg)
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_InryokuSpriteRender[i]);		//�����̓X�v���C�g�폜
				}
				DeleteGO(m_QuarterSpriteRender[1]);		//2/4�X�v���C�g�폜
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_DeathSpriteRender[i]);		//���ʏ��X�v���C�g�폜
				}
				DeleteGO(m_QuarterSpriteRender[3]);		//4/4�X�v���C�g�폜
			}

			break;

			//4�y�[�W��
		case FourPage:
			//�ԃ{�[���摜�\��
			m_DeathSpriteRender[0] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[0]->SetPosition({ -250.0f,50.0f,0.0f });
			m_DeathSpriteRender[0]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//�{�[���摜�\��
			m_DeathSpriteRender[1] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[1]->SetPosition({ -250.0f,-100.0f,0.0f });
			m_DeathSpriteRender[1]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//���ʏ��摜�\��
			m_DeathSpriteRender[2] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[2]->SetPosition({ 300.0f,-30.0f,0.0f });
			m_DeathSpriteRender[2]->SetScale({ 1.2f,1.2f,1.2f });		//������������������傫������
			m_DeathSpriteRender[2]->Init("Assets/image/DeathFloor.dds", 350.0f, 350.0f);
			//�o�c(1)�摜�\��
			m_DeathSpriteRender[3] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[3]->SetPosition({ 230.0f,50.0f,0.0f });
			m_DeathSpriteRender[3]->SetScale({ 0.5f,0.5f,0.5f });		//������������������傫������
			m_DeathSpriteRender[3]->Init("Assets/image/Batu.dds", 350.0f, 350.0f);
			m_DeathSpriteRender[3]->Deactivate();		//��\��
			//�o�c(2)�摜�\��
			m_DeathSpriteRender[4] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[4]->SetPosition({ 230.0f,-100.0f,0.0f });
			m_DeathSpriteRender[4]->SetScale({ 0.5f,0.5f,0.5f });		//������������������傫������
			m_DeathSpriteRender[4]->Init("Assets/image/Batu.dds", 350.0f, 350.0f);
			m_DeathSpriteRender[4]->Deactivate();		//��\��
			//Dame�摜�\��
			m_DeathSpriteRender[5] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_DeathSpriteRender[5]->SetScale({ 1.5f,1.5f,1.5f });		//������������������傫������
			m_DeathSpriteRender[5]->Init("Assets/image/Dame.dds", 350.0f, 350.0f);
			m_DeathSpriteRender[5]->Deactivate();		//��\��
			//4/4�\��
			m_QuarterSpriteRender[3] = NewGO<SpriteRender>(2);
			m_QuarterSpriteRender[3]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_QuarterSpriteRender[3]->Init("Assets/image/FourQuarters.dds", 500.0f, 500.0f);

			for (int i = 0; i < 6; i++)
			{
				DeleteGO(m_SekiryokuSpriteRender[i]);		//���˗̓X�v���C�g�폜
			}
			DeleteGO(m_QuarterSpriteRender[2]);		//3/4�X�v���C�g�폜

			break;
		}
	}

	//��ɌĂ΂��
	switch (PageNum)
	{
	 //�^�C�g���ɖ߂�B
	 case ZeroPage:

		//�N���X�̔j��
		DeleteGO(this);

		//�^�C�g����ʂ���X�^�[�g
		NewGO<TitleScene>(0);

		break;

	 case OnePage:
		 OnePageTimer++;
		 if (OnePageTimer < 110)
		 {
			 m_KeySpriteRender[2]->Activate();		//�\��
			 //�{�[���̈ʒu���E�ɂ��炵�Ă����B
			 OnePageBallPos += 5;
		 }
		 //���̏ꏊ�܂ōs������A
		 else if(110<=OnePageTimer&& OnePageTimer <=200)
		 {
			 m_KeySpriteRender[2]->Deactivate();		//��\��
			 m_KeySpriteRender[3]->Activate();		//�\��

			 KeyPos.y += 1.0f;
			 m_KeySpriteRender[0]->SetPosition({ KeyPos });		//���̈ʒu�X�V
		 }
		 else if (200 < OnePageTimer && OnePageTimer < 310)
		 {
			 m_KeySpriteRender[3]->Activate();		//�\��

			 //�{�[���̈ʒu�����ɂ��炵�Ă����B
			 OnePageBallPos -= 5;
			 m_KeySpriteRender[0]->SetPosition({ OnePageBallPos,KeyPos.y,KeyPos.z });		//���̈ʒu�X�V
		 }
		 else if (310 <= OnePageTimer && OnePageTimer<=400)
		 {
			 m_KeySpriteRender[3]->Deactivate();		//��\��
			 m_KeySpriteRender[4]->Activate();		//�\��
		 }
		 else
		 {
			 m_KeySpriteRender[4]->Deactivate();		//�\��
			 m_KeySpriteRender[2]->Activate();		//�\��
			 //���̎����グ����y���W��߂��B(������)
			 KeyPos = { 300.0f,-30.0f,0.0f };
			 m_KeySpriteRender[0]->SetPosition({ KeyPos });		//���̈ʒu�X�V
			 //�^�C�}�[�����������ď��߂�if���ɖ߂�
			 OnePageTimer = 0;
		 }

		 m_KeySpriteRender[1]->SetPosition({ OnePageBallPos,-30.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V

		 break;

	 case TwoPage:

		 TwoPageTimer++;
		 if (TwoPageTimer < 108)
		 {
			 //�{�[���̈ʒu���E�ɂ��炵�Ă����B
			 TwoPageBallPos += 4;
		 }
		 else if(108<=TwoPageTimer&&TwoPageTimer <= 200)
		 {
			 //�Ȃɂ����Ȃ�
		 }
		 else
		 {
			 TwoPageBallPos = -300.0f;//�{�[�����͂��߂̈ʒu�Ɏ����Ă����B
			 //�^�C�}�[�����������ď��߂�if���ɖ߂�
			 TwoPageTimer = 0;
		 }

		 m_InryokuSpriteRender[1]->SetPosition({ TwoPageBallPos,50.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V
		 m_InryokuSpriteRender[2]->SetPosition({ TwoPageBallPos,-100.0f,0.0f });		//�{�[���̈ʒu�X�V

		break;

	 case ThreePage:

		 ThreePageTimer++;
		 if (ThreePageTimer < 108)
		 {
			 //�{�[���̈ʒu���E�ɂ��炵�Ă����B
			 ThreePageBallPos -= 4;
		 }
		 else if (108 <= ThreePageTimer && ThreePageTimer <= 200)
		 {
			 //�Ȃɂ����Ȃ�
		 }
		 else
		 {
			 ThreePageBallPos =  125.0f;//�{�[�����͂��߂̈ʒu�Ɏ����Ă����B
			 //�^�C�}�[�����������ď��߂�if���ɖ߂�
			 ThreePageTimer = 0;
		 }

		 m_SekiryokuSpriteRender[1]->SetPosition({ ThreePageBallPos,50.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V
		 m_SekiryokuSpriteRender[2]->SetPosition({ ThreePageBallPos,-100.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V

		break;

	 case FourPage:
		 FourPageTimer++;
		 if (FourPageTimer < 85)
		 {
			 //�{�[���̈ʒu���E�ɂ��炵�Ă����B
			 FourPageBallPos +=5;
		 }
		 else
		 {
			 m_DeathSpriteRender[3]->Activate();		//�\��
			 m_DeathSpriteRender[4]->Activate();		//�\��
			 m_DeathSpriteRender[5]->Activate();		//�\��

			 if (FourPageTimer > 200)
			 {
				 FourPageBallPos = -250.0f;		//�{�[�����͂��߂̈ʒu�Ɏ����Ă����B
				 FourPageTimer = 0;		//�^�C�}�[���������ď��if�ɖ߂�B
				 m_DeathSpriteRender[3]->Deactivate();		//��\��
				 m_DeathSpriteRender[4]->Deactivate();		//��\��
				 m_DeathSpriteRender[5]->Deactivate();		//��\��
			 }
		 }
		 m_DeathSpriteRender[0]->SetPosition({ FourPageBallPos,50.0f,0.0f });		//�ԃ{�[���̈ʒu�X�V
		 m_DeathSpriteRender[1]->SetPosition({ FourPageBallPos,-100.0f,0.0f });		//�{�[���̈ʒu�X�V
			break;

	 //�^�C�g���ɖ߂�B
	 case FivePage:

		 DeleteGO(this);

		 //�^�C�g����ʂ���X�^�[�g
		 NewGO<TitleScene>(0);

		 break;
	}
}