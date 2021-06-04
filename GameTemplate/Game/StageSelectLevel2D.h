#pragma once
#include "level2D/Level2D.h"

class StageSelectLevel2D : public IGameObject
{
private:
	bool Start() override;
	~StageSelectLevel2D();
	void Update() override;

public:
	SpriteRender* GetSprite(int num) {
		return m_sprite[num];
	}
	void Render(RenderContext& rc) override;

private:
	Level2D m_level2D;		//レベル2D。
	SpriteRender* m_sprite[8];		//スプライトレンダー
};