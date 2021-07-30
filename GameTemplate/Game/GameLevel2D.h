#pragma once
#include "level2D/Level2D.h"


namespace {
	const char* GAME_SCREEN_NO_KEY_FILE_PATH = "Assets/level2D/GameScreen_NoGetKey.casl";		//鍵の点線スプライト
	const char* GAME_SCREEN_YES_KEY_FILE_PATH = "Assets/level2D/GameScreen_YesGetKey.casl";		//鍵取得スプライト
	const char* SPRITE_NAME_NO_GET_KEY = "GetKeyNO";											//caslファイルでの点線鍵の名前
	const char* SPRITE_NAME_YES_GET_KEY = "KeyGet";												//caslファイルでの鍵取得の名前
	const char* SPRITE_NAME_TIME_BACK = "TimeBack";												//caslファイルでの時間スプライトの名前									
}

class GameLevel2D : public IGameObject
{
private:
	~GameLevel2D();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
public:

	/**
	 * @brief 鍵の取得フラグを設定する関数。
	 * @param flg 鍵取得フラグ
	*/
	void SetKeyFlg(bool flg) {
		m_getKeyFlag = flg;
	}
	/**
	 * @brief 鍵を取得しているかどうか確かめる関数。
	 * @return 鍵取得フラグ
	*/
	bool GetKeyFlg() {
		return m_getKeyFlag;
	}

private:
	bool m_getKeyFlag = true;							//鍵を取得しているか取得していないかを判定する変数
	
	//デストラクタでDeleteGOをする必要があるかを確認するためのフラグ
	bool m_flagSprite = false;							//
	bool m_flagSprite1 = false;
	bool m_flagSprite2 = false;
	bool m_flagSprite3 = false;

	
	Level2D m_level2D;					//レベル2D
	Vector3 m_position = Vector3::Zero;	//座標
	Vector3 m_scale = Vector3::One;		//拡大率

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	SpriteRender* m_sprite;				//スプライト。
	SpriteRender* m_sprite1;			//スプライト。
	SpriteRender* m_sprite2;			//スプライト。
	SpriteRender* m_sprite3;			//スプライト。
};