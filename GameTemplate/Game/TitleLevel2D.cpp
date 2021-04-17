#include "stdafx.h"
#include "TitleLevel2D.h"


bool TitleLevel2D::Start()
{
	//TitleSceneレベルを読み込む。
	m_level2D.Init("Assets/level2D/TitleScene.casl", [&](Level2DObjectData& objdata) {

		//名前がBackScreenだったら、
		if (objdata.EqualObjectName("BackScreen")) {

			m_sprite = NewGO<SpriteRender>(0);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite->SetPosition(objdata.position);
			m_sprite->SetScale(objdata.scale);

			//座標を取得する。
			m_position = objdata.position;
			//大きさを設定する。
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//名前がTitleだったら、
		else if (objdata.EqualObjectName("Title")) {

			m_sprite1 = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite1->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite1->SetPosition(objdata.position);
			m_sprite1->SetScale(objdata.scale);


			//座標を取得する。
			m_position = objdata.position;
			//大きさを設定する。
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//名前がStartだったら、
		else if (objdata.EqualObjectName("Start")) {

			m_sprite3 = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite3->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite3->SetPosition(objdata.position);
			m_sprite3->SetScale(objdata.scale);

			//座標を取得する。
			m_position = objdata.position;
			//大きさを設定する。
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//名前がRuleだったら、
		else if (objdata.EqualObjectName("Rule")) {

			m_sprite4 = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite4->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite4->SetPosition(objdata.position);
			m_sprite4->SetScale(objdata.scale);


			//座標を取得する。
			m_position = objdata.position;
			//大きさを設定する。
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//もし名前Settingだったら、
		else if (objdata.EqualObjectName("Setting")) {

			m_sprite5 = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite5->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite5->SetPosition(objdata.position);
			m_sprite5->SetScale(objdata.scale);


			//座標を取得する。
			m_position = objdata.position;
			//大きさを設定する。
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		else if (objdata.EqualObjectName("End")) {

			m_sprite6 = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite6->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite6->SetPosition(objdata.position);
			m_sprite6->SetScale(objdata.scale);


			//座標を取得する。
			m_position = objdata.position;
			//大きさを設定する。
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}


		return false;
	});

	//Start関数のreturn true;
	return true;
}

TitleLevel2D::~TitleLevel2D()
{
	//ゲーム画面に遷移するときに画像を破棄。

	DeleteGO(m_sprite);
	DeleteGO(m_sprite1);
	DeleteGO(m_sprite2);
	DeleteGO(m_sprite3);
	DeleteGO(m_sprite4);
	DeleteGO(m_sprite5);
	DeleteGO(m_sprite6);
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