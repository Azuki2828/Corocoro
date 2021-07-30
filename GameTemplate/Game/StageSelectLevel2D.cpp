#include "stdafx.h"
#include "StageSelectLevel2D.h"

namespace {
	const char* STAGE_LEVEL_2D_NAME = "Assets/level2D/StageSelect.casl";
	const char* SPRITE_NAME_BACK_GROUND = "eheheNS03";
	const char* SPRITE_NAME_STAGE_SELECT = "StageSelect";
	const char* SPRITE_NAME_LEFT_SELECT = "LeftSelect";
	const char* SPRITE_NAME_RIGHT_SELECT = "RightSelect";
	const char* SPRITE_NAME_BACK = "Back";
	const char* SPRITE_NAME_DECISION = "Kettei";
	const char* SPRITE_NAME_LB = "LB";
	const char* SPRITE_NAME_RB = "RB";
}
bool StageSelectLevel2D::Start()
{
//StageSelectレベルを読み込む。
	m_level2D.Init(STAGE_LEVEL_2D_NAME, [&](Level2DObjectData& objdata) {

		//名前がeheheNS03だったら、
		if (objdata.EqualObjectName(SPRITE_NAME_BACK_GROUND)) {

			m_spriteRender[enStageSelectSprite_BackScreen] = NewGO<SpriteRender>(enPriority_Zeroth);
			m_spriteRender[enStageSelectSprite_BackScreen]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enStageSelectSprite_BackScreen]->SetPosition(objdata.position);
			m_spriteRender[enStageSelectSprite_BackScreen]->SetScale(objdata.scale);

			return true;
		}
		//名前がStageSelectだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_STAGE_SELECT)) {

			m_spriteRender[enStageSelectSprite_StageSelectLogo] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enStageSelectSprite_StageSelectLogo]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enStageSelectSprite_StageSelectLogo]->SetPosition(objdata.position);
			m_spriteRender[enStageSelectSprite_StageSelectLogo]->SetScale(objdata.scale);

			return true;
		}
		//名前がLeftSelectだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_LEFT_SELECT)) {

			m_spriteRender[enStageSelectSprite_Select_Left] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enStageSelectSprite_Select_Left]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enStageSelectSprite_Select_Left]->SetPosition(objdata.position);
			m_spriteRender[enStageSelectSprite_Select_Left]->SetScale(objdata.scale);

			return true;
		}
		//名前がRightSelectだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_RIGHT_SELECT)) {

			m_spriteRender[enStageSelectSprite_Select_Right] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enStageSelectSprite_Select_Right]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enStageSelectSprite_Select_Right]->SetPosition(objdata.position);
			m_spriteRender[enStageSelectSprite_Select_Right]->SetScale(objdata.scale);

			return true;
		}
		//名前がBackだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_BACK)) {

			m_spriteRender[enStageSelectSprite_BackButton] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enStageSelectSprite_BackButton]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enStageSelectSprite_BackButton]->SetPosition(objdata.position);
			m_spriteRender[enStageSelectSprite_BackButton]->SetScale(objdata.scale);

			return true;
		}
		//名前がKetteiだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_DECISION)) {

			m_spriteRender[enStageSelectSprite_DecisionButton] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enStageSelectSprite_DecisionButton]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enStageSelectSprite_DecisionButton]->SetPosition(objdata.position);
			m_spriteRender[enStageSelectSprite_DecisionButton]->SetScale(objdata.scale);

			return true;
		}
		//名前がLBだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_LB)) {

			m_spriteRender[enStageSelectSprite_LB] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enStageSelectSprite_LB]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enStageSelectSprite_LB]->SetPosition(objdata.position);
			m_spriteRender[enStageSelectSprite_LB]->SetScale(objdata.scale);

			return true;
		}
		//名前がRBだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_RB)) {

			m_spriteRender[enStageSelectSprite_RB] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enStageSelectSprite_RB]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enStageSelectSprite_RB]->SetPosition(objdata.position);
			m_spriteRender[enStageSelectSprite_RB]->SetScale(objdata.scale);

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