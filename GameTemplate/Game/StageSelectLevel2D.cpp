#include "stdafx.h"
#include "StageSelectLevel2D.h"

bool StageSelectLevel2D::Start()
{
//StageSelectレベルを読み込む。
	m_level2D.Init("Assets/level2D/StageSelect.casl", [&](Level2DObjectData& objdata) {

		//名前がeheheNS03だったら、
		if (objdata.EqualObjectName("eheheNS03")) {

			m_sprite[0] = NewGO<SpriteRender>(0);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[0]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[0]->SetPosition(objdata.position);
			m_sprite[0]->SetScale(objdata.scale);

			return true;
		}
		//名前がStageSelectだったら、
		else if (objdata.EqualObjectName("StageSelect")) {

			m_sprite[1] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[1]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[1]->SetPosition(objdata.position);
			m_sprite[1]->SetScale(objdata.scale);

			return true;
		}
		//名前がLeftSelectだったら、
		else if (objdata.EqualObjectName("LeftSelect")) {

			m_sprite[2] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[2]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[2]->SetPosition(objdata.position);
			m_sprite[2]->SetScale(objdata.scale);

			return true;
		}
		//名前がRightSelectだったら、
		else if (objdata.EqualObjectName("RightSelect")) {

			m_sprite[3] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[3]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[3]->SetPosition(objdata.position);
			m_sprite[3]->SetScale(objdata.scale);

			return true;
		}
		//名前がBackだったら、
		else if (objdata.EqualObjectName("Back")) {

			m_sprite[4] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[4]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[4]->SetPosition(objdata.position);
			m_sprite[4]->SetScale(objdata.scale);

			return true;
		}
		//名前がKetteiだったら、
		else if (objdata.EqualObjectName("Kettei")) {

			m_sprite[5] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[5]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[5]->SetPosition(objdata.position);
			m_sprite[5]->SetScale(objdata.scale);

			return true;
		}
		//名前がLBだったら、
		else if (objdata.EqualObjectName("LB")) {

			m_sprite[6] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[6]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[6]->SetPosition(objdata.position);
			m_sprite[6]->SetScale(objdata.scale);

			return true;
		}
		//名前がRBだったら、
		else if (objdata.EqualObjectName("RB")) {

			m_sprite[7] = NewGO<SpriteRender>(1);
			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite[7]->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite[7]->SetPosition(objdata.position);
			m_sprite[7]->SetScale(objdata.scale);

			return true;
		}
	});

	//Start関数のreturn true;
	return true;
}

StageSelectLevel2D::~StageSelectLevel2D() {
	//シーン遷移時に画像を全て破棄。
	for (int i = 0; i < 8; i++) {
		DeleteGO(m_sprite[i]);
	}
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