#include "stdafx.h"
#include "RuleLevel2D.h"

bool RuleLevel2D::Start() {
	//TitleScene���x����ǂݍ��ށB
	m_level2D.Init("Assets/level2D/Rule.casl", [&](Level2DObjectData& objdata) {

		//���O��Rule��������A
		if (objdata.EqualObjectName("Rule")) {

			m_sprite[0] = NewGO<SpriteRender>(0);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[0]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[0]->SetPosition(objdata.position);
			m_sprite[0]->SetScale(objdata.scale);
			//m_sprite[0]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//���O��Back��������A
		else if (objdata.EqualObjectName("Back")) {

			m_sprite[1] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[1]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[1]->SetPosition(objdata.position);
			m_sprite[1]->SetScale(objdata.scale);
			//m_sprite[1]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//���O��Next��������A
		else if (objdata.EqualObjectName("Next")) {

			m_sprite[2] = NewGO<SpriteRender>(1);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[2]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[2]->SetPosition(objdata.position);
			m_sprite[2]->SetScale(objdata.scale);
			//m_sprite[2]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		else if (objdata.EqualObjectName("eheheNS03")) {
			m_sprite[3] = NewGO<SpriteRender>(0);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[3]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[3]->SetPosition(objdata.position);
			m_sprite[3]->SetScale(objdata.scale);
			//m_sprite[3]->SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });

			return true;
		}

		return false;
	});

	return true;
}

RuleLevel2D::~RuleLevel2D()
{
	//�^�C�g����ʂɖ߂�Ƃ��ɉ摜��S�Ĕj���B
	for (int i = 0; i < 4; i++) {
		DeleteGO(m_sprite[i]);
	}
}

void RuleLevel2D::Update()
{
	//m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//���x��2D�N���X��Sprite�̍X�V�����B
	m_level2D.Update();
}

void RuleLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}