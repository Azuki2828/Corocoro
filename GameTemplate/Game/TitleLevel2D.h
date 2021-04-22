#pragma once
#include "level2D/Level2D.h"


/// <summary>
/// レベル2D処理のサンプルクラス。
/// </summary>

class TitleLevel2D : public IGameObject
{
public:
		bool Start() override;
		~TitleLevel2D();
		void Update() override;
		SpriteRender* GetSprite(int num) {
			return m_sprite[num];
		}
		void Render(RenderContext& rc) override;

	private:
		Level2D m_level2D;		//レベル2D。
		SpriteRender* m_sprite[6];		//スプライトレンダー
};