#include "stdafx.h"
#include "TitleLevel2D.h"

namespace {
	const char* TITLE_LEVEL_2D_NAME = "Assets/level2D/TitleScene.casl";
	const char* SPRITE_NAME_BACK_GROUND = "eheheNS";
	const char* SPRITE_NAME_TITLE = "Title";
	const char* SPRITE_NAME_START = "Start";
	const char* SPRITE_NAME_RULE_BUTTON = "RuleButton";
	const char* SPRITE_NAME_SETTING_BUTTON = "Setting";
	const char* SPRITE_NAME_END = "End";
}
bool TitleLevel2D::Start()
{
	//TitleSceneレベルを読み込む。
	m_level2D.Init(TITLE_LEVEL_2D_NAME, [&](Level2DObjectData& objdata) {

		//名前がeheheNSだったら、(背景画)
		if (objdata.EqualObjectName(SPRITE_NAME_BACK_GROUND)) {

			m_spriteRender[enTitleSprite_BackScreen] = NewGO<SpriteRender>(enPriority_Zeroth);
			m_spriteRender[enTitleSprite_BackScreen]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enTitleSprite_BackScreen]->SetPosition(objdata.position);
			m_spriteRender[enTitleSprite_BackScreen]->SetScale(objdata.scale);

			return true;
		}
		//名前がTitleだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_TITLE)) {

			m_spriteRender[enTitleSprite_TitleLogo] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enTitleSprite_TitleLogo]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enTitleSprite_TitleLogo]->SetPosition(objdata.position);
			m_spriteRender[enTitleSprite_TitleLogo]->SetScale(objdata.scale);

			return true;
		}
		//名前がStartだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_START)) {

			m_spriteRender[enTitleSprite_StartButton] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enTitleSprite_StartButton]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enTitleSprite_StartButton]->SetPosition(objdata.position);
			m_spriteRender[enTitleSprite_StartButton]->SetScale(objdata.scale);

			return true;
		}
		//名前がRuleだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_RULE_BUTTON)) {

			m_spriteRender[enTitleSprite_RuleButton] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enTitleSprite_RuleButton]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enTitleSprite_RuleButton]->SetPosition(objdata.position);
			m_spriteRender[enTitleSprite_RuleButton]->SetScale(objdata.scale);

			return true;
		}
		//もし名前Settingだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_SETTING_BUTTON)) {
		
			return true;
		}
		else if (objdata.EqualObjectName(SPRITE_NAME_END)) {

			m_spriteRender[enTitleSprite_EndButton] = NewGO<SpriteRender>(enPriority_First);
			m_spriteRender[enTitleSprite_EndButton]->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			m_spriteRender[enTitleSprite_EndButton]->SetPosition(objdata.position);
			m_spriteRender[enTitleSprite_EndButton]->SetScale(objdata.scale);

			return true;
		}


		return false;
	});

	//Start関数のreturn true;
	return true;
}

TitleLevel2D::~TitleLevel2D()
{
	for (auto& i : m_spriteRender) {
		if (i != nullptr) {
			DeleteGO(i);
		}
	}
}

void TitleLevel2D::Update()
{
	//m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void TitleLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}