#pragma once
#include "level2D/Level2D.h"

//�X�v���C�g�̔ԍ�
enum {
	enSprite_Rule,
	enSprite_Back,
	enSprite_Next,
	enSprite_BackGround,

	enRuleSprite_Num

};
class RuleLevel2D:public IGameObject
{
private:
	bool Start();
	~RuleLevel2D();
	void Update();
public:
	/**
	 * @brief �X�v���C�g���擾����֐��B
	 * @param num �X�v���C�g�ԍ�
	 * @return �X�v���C�g
	*/
	SpriteRender* GetSprite(int num) {
		return m_sprite[num];
	}
	/**
	 * @brief �\���֐��B
	 * @param rc �����_�[�R���e�L�X�g
	*/
	void Render(RenderContext& rc) override;

private:
	Level2D m_level2D;		//���x��2D�B

	//���ꂼ��̃N���X�̃|�C���^

	SpriteRender* m_sprite[enRuleSprite_Num] = { nullptr };
};