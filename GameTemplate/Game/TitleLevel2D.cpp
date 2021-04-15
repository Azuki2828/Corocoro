#include "stdafx.h"
#include "TitleLevel2D.h"


bool TitleLevel2D::Start()
{


	//TitleSceneレベルを読み込む。
	m_level2D.Init("Assets/level2D/TitleScene.casl", [&](Level2DObjectData& objdata) {
		//名前がBackScreenだったら、
		if (objdata.EqualObjectName("BackScreen")) {

			SpriteInitData data;
			//DDSファイル(画像データ)のファイルパスを指定する。
			data.m_ddsFilePath[0] = objdata.ddsFilePath;
			//Sprite表示用のシェーダーのファイルパスを指定する。
			data.m_fxFilePath = "Assets/shader/sprite.fx";
			//スプライトの幅と高さを取得する。
			data.m_width = objdata.width;
			data.m_height = objdata.height;
			data.m_alphaBlendMode = AlphaBlendMode_Trans;

			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite.Init(data);

			//座標を取得する。
			m_position = objdata.position;
			//大きさを設定する。
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//名前がTitleだったら、
		else if (objdata.EqualObjectName("Title")) {

			SpriteInitData data;
			//DDSファイル(画像データ)のファイルパスを指定する。
			data.m_ddsFilePath[0] = objdata.ddsFilePath;
			//Sprite表示用のシェーダーのファイルパスを指定する。
			data.m_fxFilePath = "Assets/shader/sprite.fx";
			//スプライトの幅と高さを取得する。
			data.m_width = objdata.width;
			data.m_height = objdata.height;
			data.m_alphaBlendMode = AlphaBlendMode_Trans;

			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite.Init(data);

			//座標を取得する。
			m_position = objdata.position;
			//大きさを設定する。
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//名前がStartだったら、
		else if (objdata.EqualObjectName("Start")) {

			SpriteInitData data;
			//DDSファイル(画像データ)のファイルパスを指定する。
			data.m_ddsFilePath[0] = objdata.ddsFilePath;
			//Sprite表示用のシェーダーのファイルパスを指定する。
			data.m_fxFilePath = "Assets/shader/sprite.fx";
			//スプライトの幅と高さを取得する。
			data.m_width = objdata.width;
			data.m_height = objdata.height;
			data.m_alphaBlendMode = AlphaBlendMode_Trans;

			//Sprite初期化オブジェクトを使用して、Spriteを初期化する
			m_sprite.Init(data);

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

void TitleLevel2D::Update()
{
	m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//レベル2DクラスのSpriteの更新処理。
	m_level2D.Update();
}

void TitleLevel2D::Render(RenderContext& rc)
{
	m_sprite.Draw(rc);
	//レベル2DクラスのSpriteの描画処理。
	m_level2D.Draw(rc);
}