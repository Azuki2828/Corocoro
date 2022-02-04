#pragma once
#include "level2D/Level2D.h"


/// <summary>
/// ���x��2D�����̃T���v���N���X�B
/// </summary>

enum TitleSprite {
	enTitleSprite_BackScreen,
	enTitleSprite_TitleLogo,
	enTitleSprite_StartButton,
	enTitleSprite_RuleButton,
	enTitleSprite_SettingButton,
	enTitleSprite_EndButton,

	enTitleSprite_Num
};

class TitleLevel2D : public IGameObject
{
private:
	bool Start() override;
	~TitleLevel2D();
	void Update() override;

public:
	void Render(RenderContext& rc) override;

	SpriteRender* GetTitleSprite(int spriteNum) {
		return m_spriteRender[spriteNum];
	}

private:
	Level2D m_level2D;		//���x��2D�B
	SpriteRender* m_spriteRender[enTitleSprite_Num] = { nullptr };
};