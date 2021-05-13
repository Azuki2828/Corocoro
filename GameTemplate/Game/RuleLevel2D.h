#pragma once
#include "level2D/Level2D.h"

class RuleLevel2D:public IGameObject
{
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
	SpriteRender* m_sprite[4];		//�X�v���C�g�����_�[
};