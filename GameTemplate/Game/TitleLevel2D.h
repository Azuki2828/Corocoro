#pragma once
#include "level2D/Level2D.h"


/// <summary>
/// レベル2D処理のサンプルクラス。
/// </summary>

class TitleLevel2D : public IGameObject
{
		bool Start() override;
		~TitleLevel2D();
		void Update() override;
		void Render(RenderContext& rc) override;
	private:
		Level2D m_level2D;		//レベル2D。
		SpriteRender* m_sprite;		//スプライト。
		SpriteRender* m_sprite1;		//スプライト。
		SpriteRender* m_sprite2;		//スプライト。
		SpriteRender* m_sprite3;		//スプライト。
		SpriteRender* m_sprite4;		//スプライト。
		SpriteRender* m_sprite5;		//スプライト。
		SpriteRender* m_sprite6;		//スプライト。
		Vector3 m_position;		//座標。
		Vector3 m_scale;		//大きさ。
};