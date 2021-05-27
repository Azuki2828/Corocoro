#pragma once
#include "level2D/Level2D.h"

/// <summary>
/// ���x��2D�����̃T���v���N���X�B
/// </summary>
///
class GameLevel2D : public IGameObject
{
public:

	//�f�X�g���N�^��DeleteGO������K�v�����邩���m�F���邽�߂̃t���O
	bool m_flagSprite = false;
	bool m_flagSprite1 = false;
	bool m_flagSprite2 = false;
	bool m_flagSprite3 = false;
	
	//Key�N���X�Ŏg�����߂�public�ɒu���Ă���B
	//���֐������private�ŊǗ��ł���悤�ɂ��Ă��������B
	bool NoGetKeyFlag = true;							//�����擾���Ă��邩�擾���Ă��Ȃ����𔻒肷��ϐ��B
	SpriteRender* m_sprite;			//�X�v���C�g�B
	SpriteRender* m_sprite1;			//�X�v���C�g�B
	SpriteRender* m_sprite2;			//�X�v���C�g�B
	SpriteRender* m_sprite3;			//�X�v���C�g�B

private:

	bool Start() override;
	~GameLevel2D();
	void Update() override;
	void Render(RenderContext& rc) override;

	Level2D m_level2D;		//���x��2D�B

	Vector3 m_position;		//���W�B
	Vector3 m_scale;		//�傫���B
};