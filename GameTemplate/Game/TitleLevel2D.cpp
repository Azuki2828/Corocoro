#include "stdafx.h"
#include "TitleLevel2D.h"


bool TitleLevel2D::Start()
{
	//TitleScene���x����ǂݍ��ށB
	m_level2D.Init("Assets/level2D/TitleScene.casl", [&](Level2DObjectData& objdata) {

		//���O��BackScreen��������A
		if (objdata.EqualObjectName("BackScreen")) {

			m_sprite = NewGO<SpriteRender>(0);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite->SetPosition(objdata.position);
			m_sprite->SetScale(objdata.scale);

			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//���O��Title��������A
		else if (objdata.EqualObjectName("Title")) {

			m_sprite1 = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite1->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite1->SetPosition(objdata.position);
			m_sprite1->SetScale(objdata.scale);


			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//���O��Start��������A
		else if (objdata.EqualObjectName("Start")) {

			m_sprite3 = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite3->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite3->SetPosition(objdata.position);
			m_sprite3->SetScale(objdata.scale);

			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//���O��Rule��������A
		else if (objdata.EqualObjectName("Rule")) {

			m_sprite4 = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite4->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite4->SetPosition(objdata.position);
			m_sprite4->SetScale(objdata.scale);


			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//�������OSetting��������A
		else if (objdata.EqualObjectName("Setting")) {

			m_sprite5 = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite5->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite5->SetPosition(objdata.position);
			m_sprite5->SetScale(objdata.scale);


			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		else if (objdata.EqualObjectName("End")) {

			m_sprite6 = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite6->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite6->SetPosition(objdata.position);
			m_sprite6->SetScale(objdata.scale);


			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}


		return false;
	});

	//Start�֐���return true;
	return true;
}

TitleLevel2D::~TitleLevel2D()
{
	//�Q�[����ʂɑJ�ڂ���Ƃ��ɉ摜��j���B

	DeleteGO(m_sprite);
	DeleteGO(m_sprite1);
	DeleteGO(m_sprite2);
	DeleteGO(m_sprite3);
	DeleteGO(m_sprite4);
	DeleteGO(m_sprite5);
	DeleteGO(m_sprite6);
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