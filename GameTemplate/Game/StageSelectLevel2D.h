#pragma once
#include "level2D/Level2D.h"

enum StageSelectSprite {
	enStageSelectSprite_BackScreen,
	enStageSelectSprite_StageSelectLogo,
	enStageSelectSprite_Select_Left,
	enStageSelectSprite_Select_Right,
	enStageSelectSprite_BackButton,
	enStageSelectSprite_DecisionButton,
	enStageSelectSprite_LB,
	enStageSelectSprite_RB,

	enStageSelectSprite_Num
};

class StageSelectLevel2D : public IGameObject
{
private:
	bool Start() override;
	~StageSelectLevel2D();
	void Update() override;

public:
	SpriteRender* GetSprite(int spriteNum) {
		return m_spriteRender[spriteNum];
	}
	Vector3 GetScale(int spriteNum) {
		return m_spriteRender[spriteNum]->GetScale();
	}
	void Render(RenderContext& rc) override;

private:
	Level2D m_level2D;		//レベル2D。
	SpriteRender* m_spriteRender[enStageSelectSprite_Num];		//スプライトレンダー
};