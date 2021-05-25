#include "stdafx.h"
#include "TitleLevel2D.h"


bool TitleLevel2D::Start()
{
	//TitleScene���x����ǂݍ��ށB
	m_level2D.Init("Assets/level2D/TitleScene.casl", [&](Level2DObjectData& objdata) {

		//���O��eheheNS��������A(�w�i��)
		if (objdata.EqualObjectName("eheheNS")) {

			m_sprite[0] = NewGO<SpriteRender>(0);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[0]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[0]->SetPosition(objdata.position);
			m_sprite[0]->SetScale(objdata.scale);
			//m_sprite[0]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//���O��Title��������A
		else if (objdata.EqualObjectName("Title")) {

			m_sprite[1] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[1]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[1]->SetPosition(objdata.position);
			m_sprite[1]->SetScale(objdata.scale);
			//m_sprite[1]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//���O��Start��������A
		else if (objdata.EqualObjectName("Start")) {

			m_sprite[2] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[2]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[2]->SetPosition(objdata.position);
			m_sprite[2]->SetScale(objdata.scale);
			m_sprite[2]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//���O��Rule��������A
		else if (objdata.EqualObjectName("RuleButton")) {

			m_sprite[3] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[3]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[3]->SetPosition(objdata.position);
			m_sprite[3]->SetScale(objdata.scale);
			m_sprite[3]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//�������OSetting��������A
		//else if (objdata.EqualObjectName("Setting")) {
		//
		//	m_sprite[4] = NewGO<SpriteRender>(1);
		//	//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
		//	m_sprite[4]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
		//	m_sprite[4]->SetPosition(objdata.position);
		//	m_sprite[4]->SetScale(objdata.scale);
		//	m_sprite[4]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
		//
		//	return true;
		//}
		else if (objdata.EqualObjectName("End")) {

			m_sprite[4] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[4]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[4]->SetPosition(objdata.position);
			m_sprite[4]->SetScale(objdata.scale);
			m_sprite[4]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}


		return false;
	});

	//Start�֐���return true;
	return true;
}

TitleLevel2D::~TitleLevel2D()
{
	//�Q�[����ʂɑJ�ڂ���Ƃ��ɉ摜��S�Ĕj���B
	for (int i = 0; i < 5; i++) {
		DeleteGO(m_sprite[i]);
	}
}

void TitleLevel2D::Update()
{
	//m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//���x��2D�N���X��Sprite�̍X�V�����B
	m_level2D.Update();
}

void TitleLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}