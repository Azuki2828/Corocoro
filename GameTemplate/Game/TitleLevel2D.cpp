#include "stdafx.h"
#include "TitleLevel2D.h"


bool TitleLevel2D::Start()
{
	//TitleSceneレベルを読み込む。
	m_level2D.Init("Assets/level2D/TitleScene.casl", [&](Level2DObjectData& objdata) {

		//名前がeheheNSだったら、(背景画)
		if (objdata.EqualObjectName("eheheNS")) {

			m_sprite[0] = NewGO<SpriteRender>(0);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[0]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[0]->SetPosition(objdata.position);
			m_sprite[0]->SetScale(objdata.scale);
			//m_sprite[0]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//名前がTitleだったら、
		else if (objdata.EqualObjectName("Title")) {

			m_sprite[1] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[1]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[1]->SetPosition(objdata.position);
			m_sprite[1]->SetScale(objdata.scale);
			//m_sprite[1]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//名前がStartだったら、
		else if (objdata.EqualObjectName("Start")) {

			m_sprite[2] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[2]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[2]->SetPosition(objdata.position);
			m_sprite[2]->SetScale(objdata.scale);
			m_sprite[2]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//名前がRuleだったら、
		else if (objdata.EqualObjectName("RuleButton")) {

			m_sprite[3] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[3]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[3]->SetPosition(objdata.position);
			m_sprite[3]->SetScale(objdata.scale);
			m_sprite[3]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//もし名前Settingだったら、
		//else if (objdata.EqualObjectName("Setting")) {
		//
		//	m_sprite[4] = NewGO<SpriteRender>(1);
		//	//Sprite初期化オブジェクトを使用して、Spriteを初期化する
		//	m_sprite[4]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
		//	m_sprite[4]->SetPosition(objdata.position);
		//	m_sprite[4]->SetScale(objdata.scale);
		//	m_sprite[4]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
		//
		//	return true;
		//}
		else if (objdata.EqualObjectName("End")) {

			m_sprite[4] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[4]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[4]->SetPosition(objdata.position);
			m_sprite[4]->SetScale(objdata.scale);
			m_sprite[4]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}


		return false;
	});

	//Start関数のreturn true;
	return true;
}

TitleLevel2D::~TitleLevel2D()
{
	//ゲーム画面に遷移するときに画像を全て破棄。
	for (int i = 0; i < 5; i++) {
		DeleteGO(m_sprite[i]);
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