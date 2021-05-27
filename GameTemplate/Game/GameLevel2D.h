#pragma once
#include "level2D/Level2D.h"

/// <summary>
/// レベル2D処理のサンプルクラス。
/// </summary>
///
class GameLevel2D : public IGameObject
{
public:

	//デストラクタでDeleteGOをする必要があるかを確認するためのフラグ
	bool m_flagSprite = false;
	bool m_flagSprite1 = false;
	bool m_flagSprite2 = false;
	bool m_flagSprite3 = false;
	
	//Keyクラスで使うためにpublicに置いている。
	//↑関数作ってprivateで管理できるようにしてください。
	bool NoGetKeyFlag = true;							//鍵を取得しているか取得していないかを判定する変数。
	SpriteRender* m_sprite;			//スプライト。
	SpriteRender* m_sprite1;			//スプライト。
	SpriteRender* m_sprite2;			//スプライト。
	SpriteRender* m_sprite3;			//スプライト。

private:

	bool Start() override;
	~GameLevel2D();
	void Update() override;
	void Render(RenderContext& rc) override;

	Level2D m_level2D;		//レベル2D。

	Vector3 m_position;		//座標。
	Vector3 m_scale;		//大きさ。
};