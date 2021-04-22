#pragma once
#include "level2D/Level2D.h"

class ResultLevel2D : public IGameObject
{
public:
	bool Start();
	~ResultLevel2D();
	void Update();
	SpriteRender* GetSprite(int num) {
		return m_sprite[num];
	}
	void Render(RenderContext& rc) override;

private:
	Level2D m_level2D;		//レベル2D。
	SpriteRender* m_sprite[10];		//スプライトレンダー
};