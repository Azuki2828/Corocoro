#include "stdafx.h"
#include "ResultLevel2D.h"

bool ResultLevel2D::Start() {

	//TitleScene���x����ǂݍ��ށB
	m_level2D.Init("Assets/level2D/ResultScene.casl", [&](Level2DObjectData& objdata) {

		//���O��Result��������A
		if (objdata.EqualObjectName("Result")) {

			m_sprite[0] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[0]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[0]->SetPosition(objdata.position);
			m_sprite[0]->SetScale(objdata.scale);

			return true;
		}
		//���O��GrayBack��������A
		else if (objdata.EqualObjectName("GrayBack")) {

			m_sprite[1] = NewGO<SpriteRender>(0);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[1]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[1]->SetPosition(objdata.position);
			m_sprite[1]->SetScale(objdata.scale);

			return true;
		}
		//���O��time��������A
		else if (objdata.EqualObjectName("time")) {

			m_sprite[2] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[2]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[2]->SetPosition(objdata.position);
			m_sprite[2]->SetScale(objdata.scale);

			return true;
		}
		//���O��ten1��������A
		else if (objdata.EqualObjectName("ten1")) {

			m_sprite[3] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[3]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[3]->SetPosition(objdata.position);
			m_sprite[3]->SetScale(objdata.scale);

			return true;
		}
		//���O��second1��������A
		else if (objdata.EqualObjectName("second1")) {

			m_sprite[4] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[4]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[4]->SetPosition(objdata.position);
			m_sprite[4]->SetScale(objdata.scale);

			return true;
		}
		//���O��top��������A
		else if (objdata.EqualObjectName("top")) {

			m_sprite[5] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[5]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[5]->SetPosition(objdata.position);
			m_sprite[5]->SetScale(objdata.scale);

			return true;
		}
		//���O��ten2��������A
		else if (objdata.EqualObjectName("ten2")) {

			m_sprite[6] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[6]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[6]->SetPosition(objdata.position);
			m_sprite[6]->SetScale(objdata.scale);

			return true;
		}
		//���O��second2��������A
		else if (objdata.EqualObjectName("second2")) {

			m_sprite[7] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[7]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[7]->SetPosition(objdata.position);
			m_sprite[7]->SetScale(objdata.scale);

			return true;
		}
		//���O��titlebutton��������A
		else if (objdata.EqualObjectName("titlebutton")) {

			m_sprite[8] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[8]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[8]->SetPosition(objdata.position);
			m_sprite[8]->SetScale(objdata.scale);
			//�{�^�������甼�����ɂ��Ă����B
			m_sprite[8]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//���O��Start��������A
		else if (objdata.EqualObjectName("End")) {

			m_sprite[9] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[9]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[9]->SetPosition(objdata.position);
			m_sprite[9]->SetScale(objdata.scale);
			//�{�^�������甼�����ɂ��Ă����B
			m_sprite[9]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}

	});

	//Start�֐���return true;
	return true;
}

ResultLevel2D::~ResultLevel2D() {
	//�^�C�g����ʂɖ߂�Ƃ��ɉ摜��S�Ĕj���B
	for (int i = 0; i < 10; i++) {
		DeleteGO(m_sprite[i]);
	}
}

void ResultLevel2D::Update() {
	//���x��2D�N���X��Sprite�̍X�V�����B
	m_level2D.Update();
}

void ResultLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}