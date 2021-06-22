#include "stdafx.h"
#include "TitleLevel2D.h"


bool TitleLevel2D::Start()
{
	//TitleScene���x����ǂݍ��ށB
	m_level2D.Init("Assets/level2D/TitleScene.casl", [&](Level2DObjectData& objdata) {

		//���O��eheheNS��������A(�w�i��)
		if (objdata.EqualObjectName("eheheNS")) {

			HUD::GetHUD()->Init(enSprite_EheheNS, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			HUD::GetHUD()->SetPosition(enSprite_EheheNS, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_EheheNS, objdata.scale);

			return true;
		}
		//���O��Title��������A
		else if (objdata.EqualObjectName("Title")) {

			HUD::GetHUD()->Init(enSprite_TitleLogo, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans, enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_TitleLogo, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_TitleLogo, objdata.scale);

			return true;
		}
		//���O��Start��������A
		else if (objdata.EqualObjectName("Start")) {

			HUD::GetHUD()->Init(enSprite_StartButton, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans, enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_StartButton, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_StartButton, objdata.scale);

			return true;
		}
		//���O��Rule��������A
		else if (objdata.EqualObjectName("RuleButton")) {

			HUD::GetHUD()->Init(enSprite_RuleButton, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans,enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_RuleButton, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_RuleButton, objdata.scale);

			return true;
		}
		//�������OSetting��������A
		else if (objdata.EqualObjectName("Setting")) {
		
			return true;
		}
		else if (objdata.EqualObjectName("End")) {

			HUD::GetHUD()->Init(enSprite_EndButton, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans,enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_EndButton, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_EndButton, objdata.scale);

			return true;
		}


		return false;
	});

	//Start�֐���return true;
	return true;
}

TitleLevel2D::~TitleLevel2D()
{
	HUD::GetHUD()->Deactivate(enSprite_EheheNS);
	HUD::GetHUD()->Deactivate(enSprite_TitleLogo);
	HUD::GetHUD()->Deactivate(enSprite_StartButton);
	HUD::GetHUD()->Deactivate(enSprite_RuleButton);
	HUD::GetHUD()->Deactivate(enSprite_EndButton);
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