#include "stdafx.h"
#include "ResultLevel2D.h"

bool ResultLevel2D::Start() {

	//レベルを初期化。
	m_level2D.Init("Assets/level2D/ResultScene.casl", [&](Level2DObjectData& objdata) {

		//名前がResultだったら、
		if (objdata.EqualObjectName(SPRITE_NAME_RESULT)) {

			HUD::GetHUD()->Init(enSprite_Result,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_Result, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_Result,objdata.scale);

			return true;
		}
		//名前がGrayBackだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_GRAY_BACK)) {

			HUD::GetHUD()->Init(enSprite_GrayBack,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_GrayBack, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_GrayBack, objdata.scale);

			return true;
		}
		//名前がtimeだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_TIME)) {

			HUD::GetHUD()->Init(enSprite_Time,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_Time, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_Time, objdata.scale);

			return true;
		}
		//名前がten1だったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_TEN1)) {

			HUD::GetHUD()->Init(enSprite_Ten1,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_Ten1, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_Ten1, objdata.scale);

			return true;
		}
		//名前がsecond1だったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_SECOND1)) {

			HUD::GetHUD()->Init(enSprite_Second1,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_Second1, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_Second1, objdata.scale);

			return true;
		}
		//名前がtopだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_TOP)) {

			HUD::GetHUD()->Init(enSprite_Top,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_Top, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_Top, objdata.scale);

			return true;
		}
		//名前がten2だったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_TEN2)) {

			HUD::GetHUD()->Init(enSprite_Ten2,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_Ten2, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_Ten2, objdata.scale);

			return true;
		}
		//名前がsecond2だったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_SECOND2)) {

			HUD::GetHUD()->Init(enSprite_Second2,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_Second2, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_Second2, objdata.scale);

			return true;
		}
		//名前がtitlebuttonだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_TITLE_BUTTON)) {

			HUD::GetHUD()->Init(enSprite_TitleButton,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_TitleButton, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_TitleButton, objdata.scale);
			HUD::GetHUD()->SetMulColor(enSprite_TitleButton, TRANSLUCENT_VALUE_HALF);

			return true;
		}
		//名前がEndだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_END_BUTTON)) {

			HUD::GetHUD()->Init(enSprite_EndButton,objdata.ddsFilePath, objdata.width, objdata.height);
			HUD::GetHUD()->SetPosition(enSprite_EndButton, objdata.position);
			HUD::GetHUD()->SetScale(enSprite_EndButton, objdata.scale);
			HUD::GetHUD()->SetMulColor(enSprite_EndButton, TRANSLUCENT_VALUE_HALF);

			return true;
		}

	});

	//Start関数のreturn true;
	return true;
}

ResultLevel2D::~ResultLevel2D() {
	
}

void ResultLevel2D::Update() {
	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void ResultLevel2D::Render(RenderContext& rc)
{
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}