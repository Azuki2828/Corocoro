#pragma once
#include "Level.h"
/// <summary>
/// �w�i�N���X�B
/// </summary>

class Level;
class Magnet;
class Key;

class Background : public IGameObject
{
public:
	bool Start() override;
	~Background();
	void Update() override;
	void Render(RenderContext& rc)override;
	float GetDeathPosY() { return deathPosY; }

	//Key�N���X�ł����邽�߂�public�ɂ��Ă��܂��B
	CSoundSource* GameBGMSound = nullptr;		//BGM�p�T�E���h�\�[�X

private:
	float deathPosY;							//����Y���W�B�X�e�[�W�ɂ���ă|�W�V�����͈قȂ�B
	Model m_model;								//���f��
	PhysicsStaticObject m_physicsStaticObject;	//�ÓI�����I�u�W�F�N�g�E
	Level m_level;								//���x��
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[
	FontRender* m_fontRender = nullptr;

	std::vector<Magnet*> m_magnet;
	Key* m_key = nullptr;

};

