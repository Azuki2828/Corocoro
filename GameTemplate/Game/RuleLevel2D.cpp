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
	//TitleSceneレベルを読み込む。
	m_level2D.Init(LEVEL2D_NAME_RULE_SCENE, [&](Level2DObjectData& objdata) {

		//名前がRuleだったら、
		if (objdata.EqualObjectName(SPRITE_NAME_RULE)) {

			m_sprite[enSprite_Rule] = NewGO<SpriteRender>(enPriority_Zeroth);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[enSprite_Rule]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[enSprite_Rule]->SetPosition(objdata.position);
			m_sprite[enSprite_Rule]->SetScale(objdata.scale);

			return true;
		}
		//名前がBackだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_BACK)) {

			m_sprite[enSprite_Back] = NewGO<SpriteRender>(enPriority_First);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[enSprite_Back]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[enSprite_Back]->SetPosition(objdata.position);
			m_sprite[enSprite_Back]->SetScale(objdata.scale);

			return true;
		}
		//名前がNextだったら、
		else if (objdata.EqualObjectName(SPRITE_NAME_NEXT)) {

			m_sprite[enSprite_Next] = NewGO<SpriteRender>(enPriority_First);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[enSprite_Next]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[enSprite_Next]->SetPosition(objdata.position);
			m_sprite[enSprite_Next]->SetScale(objdata.scale);

			return true;
		}
		else if (objdata.EqualObjectName(SPRITE_NAME_EHEHE)) {
			m_sprite[enSprite_BackGround] = NewGO<SpriteRender>(enPriority_First);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
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
	//タイトル画面に戻るときに画像を全て破棄。
	for (int i = 0; i < enSprite_Num; i++) {
		DeleteGO(m_sprite[i]);
	}
}

void RuleLevel2D::Update()
{
	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void RuleLevel2D::Render(RenderContext& rc)
{
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}