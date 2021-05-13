#include "stdafx.h"
#include "RuleLevel2D.h"

bool RuleLevel2D::Start() {
	//TitleSceneレベルを読み込む。
	m_level2D.Init("Assets/level2D/Rule.casl", [&](Level2DObjectData& objdata) {

		//名前がRuleだったら、
		if (objdata.EqualObjectName("Rule")) {

			m_sprite[0] = NewGO<SpriteRender>(0);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[0]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[0]->SetPosition(objdata.position);
			m_sprite[0]->SetScale(objdata.scale);
			//m_sprite[0]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//名前がBackだったら、
		else if (objdata.EqualObjectName("Back")) {

			m_sprite[1] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[1]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[1]->SetPosition(objdata.position);
			m_sprite[1]->SetScale(objdata.scale);
			//m_sprite[1]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//名前がNextだったら、
		else if (objdata.EqualObjectName("Next")) {

			m_sprite[2] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[2]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[2]->SetPosition(objdata.position);
			m_sprite[2]->SetScale(objdata.scale);
			//m_sprite[2]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		else if (objdata.EqualObjectName("eheheNS03")) {
			m_sprite[3] = NewGO<SpriteRender>(0);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
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
	//タイトル画面に戻るときに画像を全て破棄。
	for (int i = 0; i < 4; i++) {
		DeleteGO(m_sprite[i]);
	}
}

void RuleLevel2D::Update()
{
	//m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void RuleLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}