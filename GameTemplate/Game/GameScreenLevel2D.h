#pragma once
#include "level2D/Level2D.h"

/// <summary>
/// ���x��2D�����̃T���v���N���X�B
/// </summary>
///
class GameScreenLevel2D : public IGameObject
{
	bool Start() override;
	~GameScreenLevel2D();
	void Update() override;
	void Render(RenderContext& rc) override;
private:
	Level2D m_level2D;		//���x��2D�B
	SpriteRender* m_sprite;			//�X�v���C�g�B
	SpriteRender* m_sprite1;			//�X�v���C�g�B
	Vector3 m_position;		//���W�B
	Vector3 m_scale;		//�傫���B
};