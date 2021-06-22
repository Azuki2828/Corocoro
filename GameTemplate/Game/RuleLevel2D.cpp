#include "stdafx.h"
#include "RuleLevel2D.h"

namespace {
	const char* LEVEL2D_NAME_RULE_SCENE = "Assets/level2D/Rule.casl";
	const char* SPRITE_NAME_RULE = "Rule";
	const char* SPRITE_NAME_BACK = "Back";
	const char* SPRITE_NAME_NEXT = "Next";
	const char* SPRITE_NAME_EHEHE = "eheheNS03";
}

bool RuleLevel2D::Start() {
	//TitleScene���x����ǂݍ��ށB
	m_level2D.Init(LEVEL2D_NAME_RULE_SCENE, [&](Level2DObjectData& objdata) {

		//���O��Rule��������A
		if (objdata.EqualObjectName(SPRITE_NAME_RULE)) {

			m_sprite[enSprite_Rule] = NewGO<SpriteRender>(enPriority_Zeroth);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[enSprite_Rule]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[enSprite_Rule]->SetPosition(objdata.position);
			m_sprite[enSprite_Rule]->SetScale(objdata.scale);

			return true;
		}
		//���O��Back��������A
		else if (objdata.EqualObjectName(SPRITE_NAME_BACK)) {

			m_sprite[enSprite_Back] = NewGO<SpriteRender>(enPriority_First);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[enSprite_Back]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[enSprite_Back]->SetPosition(objdata.position);
			m_sprite[enSprite_Back]->SetScale(objdata.scale);

			return true;
		}
		//���O��Next��������A
		else if (objdata.EqualObjectName(SPRITE_NAME_NEXT)) {

			m_sprite[enSprite_Next] = NewGO<SpriteRender>(enPriority_First);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[enSprite_Next]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[enSprite_Next]->SetPosition(objdata.position);
			m_sprite[enSprite_Next]->SetScale(objdata.scale);

			return true;
		}
		else if (objdata.EqualObjectName(SPRITE_NAME_EHEHE)) {
			m_sprite[enSprite_BackGround] = NewGO<SpriteRender>(enPriority_First);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite[enSprite_BackGround]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[enSprite_BackGround]->SetPosition(objdata.position);
			m_sprite[enSprite_BackGround]->SetScale(objdata.scale);

			return true;
		}

		return false;
	});

	return true;
}

RuleLevel2D::~RuleLevel2D()
{
	//�^�C�g����ʂɖ߂�Ƃ��ɉ摜��S�Ĕj���B
	for (int i = 0; i < enSprite_Num; i++) {
		DeleteGO(m_sprite[i]);
	}
}

void RuleLevel2D::Update()
{
	//���x��2D�N���X��Sprite�̍X�V�����B
	m_level2D.Update();
}

void RuleLevel2D::Render(RenderContext& rc)
{
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}