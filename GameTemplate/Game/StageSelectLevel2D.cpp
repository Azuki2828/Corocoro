#include "stdafx.h"
#include "StageSelectLevel2D.h"

bool StageSelectLevel2D::Start()
{
//StageSelectレベルを読み込む。
	m_level2D.Init("Assets/level2D/StageSelect.casl", [&](Level2DObjectData& objdata) {

		//名前がeheheNS03だったら、
		if (objdata.EqualObjectName("eheheNS03")) {

			HUD::GetHUD()->Init(enSprite_EheheNS03, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			HUD::GetHUD()->SetPosition(enSprite_EheheNS03, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_EheheNS03, objdata.scale);

			return true;
		}
		//名前がStageSelectだったら、
		else if (objdata.EqualObjectName("StageSelect")) {

			HUD::GetHUD()->Init(enSprite_StageSelect, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans, enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_StageSelect, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_StageSelect, objdata.scale);

			return true;
		}
		//名前がLeftSelectだったら、
		else if (objdata.EqualObjectName("LeftSelect")) {

			HUD::GetHUD()->Init(enSprite_LeftSelect, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans, enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_LeftSelect, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_LeftSelect, objdata.scale);

			return true;
		}
		//名前がRightSelectだったら、
		else if (objdata.EqualObjectName("RightSelect")) {

			HUD::GetHUD()->Init(enSprite_RightSelect, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans, enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_RightSelect, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_RightSelect, objdata.scale);

			return true;
		}
		//名前がBackだったら、
		else if (objdata.EqualObjectName("Back")) {

			HUD::GetHUD()->Init(enSprite_Back, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans, enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_Back, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_Back, objdata.scale);

			return true;
		}
		//名前がKetteiだったら、
		else if (objdata.EqualObjectName("Kettei")) {

			HUD::GetHUD()->Init(enSprite_Decision, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans, enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_Decision, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_Decision, objdata.scale);

			return true;
		}
		//名前がLBだったら、
		else if (objdata.EqualObjectName("LB")) {

			HUD::GetHUD()->Init(enSprite_LB, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans, enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_LB, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_LB, objdata.scale);

			return true;
		}
		//名前がRBだったら、
		else if (objdata.EqualObjectName("RB")) {

			HUD::GetHUD()->Init(enSprite_RB, objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans, enPriority_First);
			HUD::GetHUD()->SetPosition(enSprite_RB, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_RB, objdata.scale);

			return true;
		}
	});

	//Start関数のreturn true;
	return true;
}

StageSelectLevel2D::~StageSelectLevel2D() {
	
}

void StageSelectLevel2D::Update() {
	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void StageSelectLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}