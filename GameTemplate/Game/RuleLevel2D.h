#pragma once
#include "level2D/Level2D.h"

class RuleLevel2D:public IGameObject
{
	enum {
		enSprite_Rule,
		enSprite_Back,
		enSprite_Next,
		enSprite_BackGround,

		enSprite_Num
	};
public:
	bool Start();
	~RuleLevel2D();
	void Update();
	SpriteRender* GetSprite(int num) {
		return m_sprite[num];
	}
	void Render(RenderContext& rc) override;

private:
	Level2D m_level2D;		//���x��2D�B
	SpriteRender* m_sprite[enSprite_Num];		//�X�v���C�g�����_�[
};