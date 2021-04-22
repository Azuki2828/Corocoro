#include "stdafx.h"
#include "GameLevel2D.h"

bool GameLevel2D::Start()
{
		//レベルを読み込む。
		m_level2D.Init("Assets/level2D/GameScreen_NoGetKey.casl", [&](Level2DObjectData& objdata) {

			//名前がGetKeyNOだったら。
			if (objdata.EqualObjectName("GetKeyNO")) {

				//SpriteInitData data;
				////DDSファイル(画像データ)のファイルパスを指定する。
				//data.m_ddsFilePath[0] = objdata.ddsFilePath;
				////Sprite表示用のシェーダーのファイルパスを指定する。
				//data.m_fxFilePath = "Assets/shader/sprite.fx";
				////スプライトの幅と高さを取得する。
				//data.m_width = objdata.width;
				//data.m_height = objdata.height;
				//data.m_alphaBlendMode = AlphaBlendMode_Trans;
				m_sprite = NewGO<SpriteRender>(0);
				//Sprite初期化オブジェクトを使用して、Spriteを初期化する
				m_sprite->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				m_sprite->SetPosition(objdata.position);
				m_sprite->SetScale(objdata.scale);

				return true;
			}
			//名前がTimeBackだったら。
			else if (objdata.EqualObjectName("TimeBack")) {


				//SpriteInitData data;
				////DDSファイル(画像データ)のファイルパスを指定する。
				//data.m_ddsFilePath[0] = objdata.ddsFilePath;
				////Sprite表示用のシェーダーのファイルパスを指定する。
				//data.m_fxFilePath = "Assets/shader/sprite.fx";
				////スプライトの幅と高さを取得する。
				//data.m_width = objdata.width;
				//data.m_height = objdata.height;
				//data.m_alphaBlendMode = AlphaBlendMode_Trans;
				m_sprite1 = NewGO<SpriteRender>(0);
				//Sprite初期化オブジェクトを使用して、Spriteを初期化する
				m_sprite1->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				m_sprite1->SetPosition(objdata.position);
				m_sprite1->SetScale(objdata.scale);

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
	DeleteGO(m_sprite);
	DeleteGO(m_sprite1);
}

void GameLevel2D::Update()
{

	//NoGetKeyがfalse、つまり鍵が取得されているとき、
	if (NoGetKeyFlag == false) {

		//レベルを読み込む。
		m_level2D.Init("Assets/level2D/GameScreen_YesGetKey.casl", [&](Level2DObjectData& objdata) {

			//名前がGetKeyNOだったら。
			if (objdata.EqualObjectName("KeyGet")) {

				SpriteInitData data;
				//DDSファイル(画像データ)のファイルパスを指定する。
				data.m_ddsFilePath[0] = objdata.ddsFilePath;
				//Sprite表示用のシェーダーのファイルパスを指定する。
				data.m_fxFilePath = "Assets/shader/sprite.fx";
				//スプライトの幅と高さを取得する。
				data.m_width = objdata.width;
				data.m_height = objdata.height;
				data.m_alphaBlendMode = AlphaBlendMode_Trans;

				m_sprite2 = NewGO<SpriteRender>(0);
				//Sprite初期化オブジェクトを使用して、Spriteを初期化する
				m_sprite2->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				m_sprite2->SetPosition(objdata.position);
				m_sprite2->SetScale(objdata.scale);

				return true;
			}
			//名前がTimeBackだったら。
			else if (objdata.EqualObjectName("TimeBack")) {
			
			
				SpriteInitData data;
				//DDSファイル(画像データ)のファイルパスを指定する。
				data.m_ddsFilePath[0] = objdata.ddsFilePath;
				//Sprite表示用のシェーダーのファイルパスを指定する。
				data.m_fxFilePath = "Assets/shader/sprite.fx";
				//スプライトの幅と高さを取得する。
				data.m_width = objdata.width;
				data.m_height = objdata.height;
				data.m_alphaBlendMode = AlphaBlendMode_Trans;
			
				m_sprite3 = NewGO<SpriteRender>(0);
				//Sprite初期化オブジェクトを使用して、Spriteを初期化する
				m_sprite3->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				m_sprite3->SetPosition(objdata.position);
				m_sprite3->SetScale(objdata.scale);
			
				return true;
			}

			//falseが画像出す。
			return false;
		});

		//trueにして抜ける
		NoGetKeyFlag = true;
	}


	//m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void GameLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}
