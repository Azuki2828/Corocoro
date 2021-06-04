#pragma once
#include "Level.h"
/// <summary>
/// �w�i�N���X�B
/// </summary>

class Level;
class Magnet;
class Key;
class Game;
class Player;
class DeathBlock;
class TreasureBox;
class Seesaw;
class GameLevel2D;

class BackGround : public IGameObject
{
private:
	bool Start() override;
	~BackGround();
	void Update() override;

public:
	void Render(RenderContext& rc) override;
	float GetDeathPosY() { return m_deathPosY; }
	void SetStart(bool flg) {
		m_seesawFlg = flg;
	}
	void LevelInit(const char* filePath);


private:
	bool m_seesawFlg = false;
	int m_stageNum = 0;
	int m_magnetNum = 0;
	float m_deathPosY = 0.0f;					//����Y���W�B�X�e�[�W�ɂ���ă|�W�V�����͈قȂ�B
	Model m_model;								//���f��
	PhysicsStaticObject m_physicsStaticObject;	//�ÓI�����I�u�W�F�N�g�E
	Level m_level;								//���x��
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[
	FontRender* m_fontRender = nullptr;
	CSoundSource* m_gameBGMSound = nullptr;		//BGM�p�T�E���h�\�[�X


	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	std::vector<Magnet*> m_magnet;
	std::vector<Seesaw*> m_seesaw;
	std::vector<DeathBlock*> m_deathBlock;
	Key* m_key = nullptr;
	TreasureBox* m_treasureBox = nullptr;
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	Player* m_skinModelRender = nullptr;
	GameLevel2D* m_level2D = nullptr;
};

