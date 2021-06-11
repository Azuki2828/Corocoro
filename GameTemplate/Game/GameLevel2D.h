#pragma once
#include "level2D/Level2D.h"


namespace {
	const char* GAME_SCREEN_NO_KEY_FILE_PATH = "Assets/level2D/GameScreen_NoGetKey.casl";
	const char* GAME_SCREEN_YES_KEY_FILE_PATH = "Assets/level2D/GameScreen_YesGetKey.casl";
	const char* SPRITE_NO_GET_KEY_FILE_PATH = "GetKeyNO";
	const char* SPRITE_YES_GET_KEY_FILE_PATH = "KeyGet";
	const char* SPRITE_TIME_BACK = "TimeBack";
}

class GameLevel2D : public IGameObject
{
private:
	~GameLevel2D();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
public:

	void SetKeyFlg(bool flg) {
		m_getKeyFlag = flg;
	}
	bool GetKeyFlg() {
		return m_getKeyFlag;
	}

private:
	//デストラクタでDeleteGOをする必要があるかを確認するためのフラグ
	bool m_getKeyFlag = true;							//鍵を取得しているか取得していないかを判定する変数。
	bool m_flagSprite = false;
	bool m_flagSprite1 = false;
	bool m_flagSprite2 = false;
	bool m_flagSprite3 = false;

	
	//Keyクラスで使うためにpublicに置いている。
	//↑関数作ってprivateで管理できるようにしてください。
	Level2D m_level2D;		//レベル2D。
	Vector3 m_position = Vector3::Zero;	//座標。
	Vector3 m_scale = Vector3::One;		//大きさ。

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	SpriteRender* m_sprite;			//スプライト。
	SpriteRender* m_sprite1;			//スプライト。
	SpriteRender* m_sprite2;			//スプライト。
	SpriteRender* m_sprite3;			//スプライト。
};