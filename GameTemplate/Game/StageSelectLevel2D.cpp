#include "stdafx.h"
#include "StageSelectLevel2D.h"

bool StageSelectLevel2D::Start()
{
//StageSelect���x����ǂݍ��ށB
	m_level2D.Init("Assets/level2D/StageSelect.casl", [&](Level2DObjectData& objdata) {

		//���O��eheheNS03��������A
		if (objdata.EqualObjectName("eheheNS03")) {

			m_sprite[0] = NewGO<SpriteRender>(0);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[0]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[0]->SetPosition(objdata.position);
			m_sprite[0]->SetScale(objdata.scale);

			return true;
		}
		//���O��StageSelect��������A
		else if (objdata.EqualObjectName("StageSelect")) {

			m_sprite[1] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[1]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[1]->SetPosition(objdata.position);
			m_sprite[1]->SetScale(objdata.scale);

			return true;
		}
		//���O��LeftSelect��������A
		else if (objdata.EqualObjectName("LeftSelect")) {

			m_sprite[2] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[2]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[2]->SetPosition(objdata.position);
			m_sprite[2]->SetScale(objdata.scale);

			return true;
		}
		//���O��RightSelect��������A
		else if (objdata.EqualObjectName("RightSelect")) {

			m_sprite[3] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[3]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[3]->SetPosition(objdata.position);
			m_sprite[3]->SetScale(objdata.scale);

			return true;
		}
		//���O��Back��������A
		else if (objdata.EqualObjectName("Back")) {

			m_sprite[4] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[4]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[4]->SetPosition(objdata.position);
			m_sprite[4]->SetScale(objdata.scale);

			return true;
		}
		//���O��Kettei��������A
		else if (objdata.EqualObjectName("Kettei")) {

			m_sprite[5] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[5]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[5]->SetPosition(objdata.position);
			m_sprite[5]->SetScale(objdata.scale);

			return true;
		}
		//���O��LB��������A
		else if (objdata.EqualObjectName("LB")) {

			m_sprite[6] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[6]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[6]->SetPosition(objdata.position);
			m_sprite[6]->SetScale(objdata.scale);

			return true;
		}
		//���O��RB��������A
		else if (objdata.EqualObjectName("RB")) {

			m_sprite[7] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[7]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[7]->SetPosition(objdata.position);
			m_sprite[7]->SetScale(objdata.scale);

			return true;
		}
	});

	//Start�֐���return true;
	return true;
}

StageSelectLevel2D::~StageSelectLevel2D() {
	//�V�[���J�ڎ��ɉ摜��S�Ĕj���B
	for (int i = 0; i < 8; i++) {
		DeleteGO(m_sprite[i]);
	}
}

void StageSelectLevel2D::Update() {
	//���x��2D�N���X��Sprite�̍X�V�����B
	m_level2D.Update();
}

void StageSelectLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}