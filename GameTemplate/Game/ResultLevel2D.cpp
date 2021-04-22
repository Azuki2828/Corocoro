#include "stdafx.h"
#include "ResultLevel2D.h"

bool ResultLevel2D::Start() {

	//TitleSceneレベルを読み込む。
	m_level2D.Init("Assets/level2D/ResultScene.casl", [&](Level2DObjectData& objdata) {

		//名前がResultだったら、
		if (objdata.EqualObjectName("Result")) {

			m_sprite[0] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[0]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[0]->SetPosition(objdata.position);
			m_sprite[0]->SetScale(objdata.scale);

			return true;
		}
		//名前がGrayBackだったら、
		else if (objdata.EqualObjectName("GrayBack")) {

			m_sprite[1] = NewGO<SpriteRender>(0);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[1]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[1]->SetPosition(objdata.position);
			m_sprite[1]->SetScale(objdata.scale);

			return true;
		}
		//名前がtimeだったら、
		else if (objdata.EqualObjectName("time")) {

			m_sprite[2] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[2]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[2]->SetPosition(objdata.position);
			m_sprite[2]->SetScale(objdata.scale);

			return true;
		}
		//名前がten1だったら、
		else if (objdata.EqualObjectName("ten1")) {

			m_sprite[3] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[3]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[3]->SetPosition(objdata.position);
			m_sprite[3]->SetScale(objdata.scale);

			return true;
		}
		//名前がsecond1だったら、
		else if (objdata.EqualObjectName("second1")) {

			m_sprite[4] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[4]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[4]->SetPosition(objdata.position);
			m_sprite[4]->SetScale(objdata.scale);

			return true;
		}
		//名前がtopだったら、
		else if (objdata.EqualObjectName("top")) {

			m_sprite[5] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[5]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[5]->SetPosition(objdata.position);
			m_sprite[5]->SetScale(objdata.scale);

			return true;
		}
		//名前がten2だったら、
		else if (objdata.EqualObjectName("ten2")) {

			m_sprite[6] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[6]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[6]->SetPosition(objdata.position);
			m_sprite[6]->SetScale(objdata.scale);

			return true;
		}
		//名前がsecond2だったら、
		else if (objdata.EqualObjectName("second2")) {

			m_sprite[7] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[7]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[7]->SetPosition(objdata.position);
			m_sprite[7]->SetScale(objdata.scale);

			return true;
		}
		//名前がtitlebuttonだったら、
		else if (objdata.EqualObjectName("titlebutton")) {

			m_sprite[8] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[8]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[8]->SetPosition(objdata.position);
			m_sprite[8]->SetScale(objdata.scale);
			//ボタンだから半透明にしておく。
			m_sprite[8]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}
		//名前がStartだったら、
		else if (objdata.EqualObjectName("End")) {

			m_sprite[9] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[9]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[9]->SetPosition(objdata.position);
			m_sprite[9]->SetScale(objdata.scale);
			//ボタンだから半透明にしておく。
			m_sprite[9]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });

			return true;
		}

	});

	//Start関数のreturn true;
	return true;
}

ResultLevel2D::~ResultLevel2D() {
	//タイトル画面に戻るときに画像を全て破棄。
	for (int i = 0; i < 10; i++) {
		DeleteGO(m_sprite[i]);
	}
}

void ResultLevel2D::Update() {
	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void ResultLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}