#pragma once
#include "level2D/Level2D.h"


/// <summary>
/// ���x��2D�����̃T���v���N���X�B
/// </summary>

class TitleLevel2D : public IGameObject
{
		bool Start() override;
		~TitleLevel2D();
		void Update() override;
		void Render(RenderContext& rc) override;
	private:
		Level2D m_level2D;		//���x��2D�B
		SpriteRender* m_sprite;		//�X�v���C�g�B
		SpriteRender* m_sprite1;		//�X�v���C�g�B
		SpriteRender* m_sprite2;		//�X�v���C�g�B
		SpriteRender* m_sprite3;		//�X�v���C�g�B
		SpriteRender* m_sprite4;		//�X�v���C�g�B
		SpriteRender* m_sprite5;		//�X�v���C�g�B
		SpriteRender* m_sprite6;		//�X�v���C�g�B
		Vector3 m_position;		//���W�B
		Vector3 m_scale;		//�傫���B
};