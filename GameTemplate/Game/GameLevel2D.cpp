#include "stdafx.h"
#include "GameLevel2D.h"

bool GameLevel2D::Start()
{
		//レベルを読み込む。
		m_level2D.Init(GAME_SCREEN_NO_KEY_FILE_PATH, [&](Level2DObjectData& objdata) {

			//名前がGetKeyNOだったら。
			if (objdata.EqualObjectName(SPRITE_NAME_NO_GET_KEY)) {

				HUD::GetHUD()->Init(enSprite_NoKey, objdata.ddsFilePath, objdata.width, objdata.height);
				HUD::GetHUD()->SetPosition(enSprite_NoKey, objdata.position);
				HUD::GetHUD()->SetScale(enSprite_NoKey, objdata.scale);


				//m_sprite = NewGO<SpriteRender>(enPriority_Zeroth);
				////Sprite初期化オブジェクトを使用して、Spriteを初期化する
				//m_sprite->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				//m_sprite->SetPosition(objdata.position);
				//m_sprite->SetScale(objdata.scale);

				m_flagSprite = true;

				return true;
			}
			//名前がTimeBackだったら。
			else if (objdata.EqualObjectName(SPRITE_NAME_TIME_BACK)) {

				HUD::GetHUD()->Init(enSprite_TimeBack, objdata.ddsFilePath, objdata.width, objdata.height);
				HUD::GetHUD()->SetPosition(enSprite_TimeBack, objdata.position);
				HUD::GetHUD()->SetScale(enSprite_TimeBack, objdata.scale);

				//m_sprite1 = NewGO<SpriteRender>(enPriority_Zeroth);
				////Sprite初期化オブジェクトを使用して、Spriteを初期化する
				//m_sprite1->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				//m_sprite1->SetPosition(objdata.position);
				//m_sprite1->SetScale(objdata.scale);

				m_flagSprite1 = true;

				return true;
			}


			//falseが画像出す。
			return false;
		});

	//Start関数のreturn true;
	return true;
}

GameLevel2D::~GameLevel2D()
{

	//スプライトを消去
	/*if (m_flagSprite) {
		DeleteGO(m_sprite);
		m_flagSprite = false;
	}
	if (m_flagSprite1) {
		DeleteGO(m_sprite1);
		m_flagSprite1 = false;
	}
	if (m_flagSprite2) {
		DeleteGO(m_sprite2);
		m_flagSprite2 = false;
	}
	if (m_flagSprite3) {
		DeleteGO(m_sprite3);
		m_flagSprite3 = false;
	}*/
}

void GameLevel2D::Update()
{

	//NoGetKeyがfalse、つまり鍵が取得されているとき、
	if (!m_getKeyFlag) {

		//レベルを読み込む。
		m_level2D.Init(GAME_SCREEN_YES_KEY_FILE_PATH, [&](Level2DObjectData& objdata) {

			//名前がGetKeyNOだったら。
			if (objdata.EqualObjectName(SPRITE_NAME_YES_GET_KEY)) {

				HUD::GetHUD()->Init(enSprite_YesKey, objdata.ddsFilePath, objdata.width, objdata.height);
				HUD::GetHUD()->SetPosition(enSprite_YesKey, objdata.position);
				HUD::GetHUD()->SetScale(enSprite_YesKey, objdata.scale);

				//m_sprite2 = NewGO<SpriteRender>(enPriority_Zeroth);
				////Sprite初期化オブジェクトを使用して、Spriteを初期化する
				//m_sprite2->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				//m_sprite2->SetPosition(objdata.position);
				//m_sprite2->SetScale(objdata.scale);

				m_flagSprite2 = true;

				//鍵の点線のやつを削除
				if (m_flagSprite) {
					HUD::GetHUD()->Deactivate(enSprite_NoKey);
					//DeleteGO(m_sprite);
					m_flagSprite = false;
				}

				return true;
			}
			//名前がTimeBackだったら。
			else if (objdata.EqualObjectName(SPRITE_NAME_TIME_BACK)) {

				//m_sprite3 = NewGO<SpriteRender>(enPriority_Zeroth);
				////Sprite初期化オブジェクトを使用して、Spriteを初期化する
				//m_sprite3->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				//m_sprite3->SetPosition(objdata.position);
				//m_sprite3->SetScale(objdata.scale);

				m_flagSprite3 = true;

				return true;
			}

			//falseが画像出す。
			return false;
		});

		//trueにして抜ける
		m_getKeyFlag = true;
	}


	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void GameLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}
