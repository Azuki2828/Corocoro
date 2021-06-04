#pragma once
#include "level2D/Level2D.h"

class ResultLevel2D : public IGameObject
{
private:
	bool Start();
	~ResultLevel2D();
	void Update();

public:
	SpriteRender* GetSprite(int num) {
		return m_sprite[num];
	}
	void Render(RenderContext& rc) override;

private:
	Level2D m_level2D;		//���x��2D�B
	SpriteRender* m_sprite[10] = { nullptr };		//�X�v���C�g�����_�[
};