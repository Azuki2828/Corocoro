#pragma once
#include "level2D/Level2D.h"

/// <summary>
/// レベル2D処理のサンプルクラス。
/// </summary>
///
class GameScreenLevel2D : public IGameObject
{
public:


	//Keyクラスで使うためにpublicに置いている。
	bool NoGetKeyFlag = true;							//鍵を取得しているか取得していないかを判定する変数。
	SpriteRender* m_sprite;			//スプライト。
	SpriteRender* m_sprite1;			//スプライト。
	SpriteRender* m_sprite2;			//スプライト。
	SpriteRender* m_sprite3;			//スプライト。

private:

	bool Start() override;
	~GameScreenLevel2D();
	void Update() override;
	void Render(RenderContext& rc) override;

	Level2D m_level2D;		//レベル2D。

	Vector3 m_position;		//座標。
	Vector3 m_scale;		//大きさ。
};