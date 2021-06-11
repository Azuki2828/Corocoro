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

namespace {
	const int STAGE_NUM = 4;										//�X�e�[�W�̑���

	//�I�u�W�F�N�g�̖��O
	enum ObjectName{
		enObject_Key,
		enObject_KeyGround,
		enObject_TreasureBox,
		enObject_DeathBlock,
		enObject_Seesaw,
		enObject_Magnet_N100_100,
		enObject_Magnet_S100_100,
		enObject_Magnet_N100_200_Triangle,
		enObject_Magnet_S100_200_Triangle,
		enObject_Magnet_NUnder100_200_Triangle,
		enObject_Magnet_SUnder100_200_Triangle,
		enObject_Magnet_N100_Under200_Triangle,
		enObject_Magnet_S100_Under200_Triangle,
		enObject_Magnet_NUnder100_Under200_Triangle,
		enObject_Magnet_SUnder100_Under200_Triangle
	};

	//�X�e�[�W���Ƃ̃X�^�[�g�n�_
	const Vector3 STAGE_START_POS[STAGE_NUM] = {
		{ 300.0f,1200.0f,-300.0f },
		{ 300.0f,300.0f,-300.0f },
		{ 300.0f,1300.0f,-300.0f },
		{ 300.0f,1900.0f,-300.0f }
	};

	//�X�e�[�W���Ƃ̃t�@�C���p�X
	const char* STAGE_FILE_PATH[STAGE_NUM] = {
		"Assets/level/stage01_treasure.tkl",
		"Assets/level/stage02_treasure.tkl",
		"Assets/level/stage03_treasure.tkl",
		"Assets/level/stage04_treasure.tkl"
	};

	const float DEADLINE = -500.0f;										//�v���C���[�̎��ʍ���

	const float ADD_MAGNET_POS50 = 50.0f;								//���͂̔����n�_�𐳊m�Ɍ��߂邽�߂ɉ��Z����萔
	const float ADD_MAGNET_POS150 = 150.0f;								//���͂̔����n�_�𐳊m�Ɍ��߂邽�߂ɉ��Z����萔
	const Vector3 ADD_TREASURE_BOX_POS = { -75.0f,0.0f,-50.0f };		//���W�𐳂����ݒ肷�邽�߂ɉ��Z����萔
	const Vector3 TREASURE_BOX_SCALE_UP = { 2.5f,2.5f,2.5f };			//�󔠂ɐݒ肷��g�嗦
	const Vector3 ADD_EFFECT_POS = { 200.0f, -150.0f, -200.0f };		//���W��ݒ肷�邽�߂ɉ��Z����萔

	const char* GAME_BACKGROUND_UI = "Assets/image/eheheNS03.dds";		//�Q�[�����̔w�i�摜�̃t�@�C���p�X
	const Vector2 GAME_BACKGROUND_UI_WH = { 1300.0f, 750.0f };			//�Q�[�����̔w�i�摜�̕��ƍ���
}

class BackGround : public IGameObject
{
private:
	bool Start() override;
	~BackGround();
	void Update() override;

public:
	/**
	 * @brief �`��֐�
	 * @param rc �����_�[�R���e�L�X�g
	*/
	void Render(RenderContext& rc) override;

	/**
	 * @brief �v���C���[�̎��ʍ������擾����֐�
	 * @return �v���C���[�̎��ʍ���
	*/
	float GetDeathPosY() { return DEADLINE; }

	/**
	 * @brief �V�[�\�[�̍��W�Ɖ�]�����Z�b�g����t���O��ݒ肷��֐�
	 * @param flg �V�[�\�[���Z�b�g�t���O
	*/
	void SetStart(bool flg) {
		m_seesawFlg = flg;
	}
	
	/**
	 * @brief �X�e�[�W������������֐�
	 * @param filePath �X�e�[�W�̃t�@�C���p�X
	*/
	void LevelInit(const char* filePath);


	/**
	 * @brief �X�e�[�W�̃I�u�W�F�N�g�̖��O���擾����֐�
	 * @param objectNum �I�u�W�F�N�g�̔ԍ�
	 * @return �I�u�W�F�N�g�̖��O
	*/
	static inline const char* GetObjectName(int objectNum) {
		switch (objectNum) {
		case enObject_Key:
			return "Key_after";
			break;
		case enObject_KeyGround:
			return "KeyBox";
			break;
		case enObject_TreasureBox:
			return "TreasureBox";
			break;
		case enObject_DeathBlock:
			return "DeathBlock";
			break;
		case enObject_Seesaw:
			return "seesaw";
			break;
		case enObject_Magnet_N100_100:
			return "Magnet_N100_100";
			break;
		case enObject_Magnet_S100_100:
			return "Magnet_S100_100";
			break;
		case enObject_Magnet_N100_200_Triangle:
			return "Magnet_N100_200triangle";
			break;
		case enObject_Magnet_S100_200_Triangle:
			return "Magnet_S100_200triangle";
			break;
		case enObject_Magnet_NUnder100_200_Triangle:
			return "Magnet_N-100_200triangle";
			break;
		case enObject_Magnet_SUnder100_200_Triangle:
			return "Magnet_S-100_200triangle";
			break;
		case enObject_Magnet_N100_Under200_Triangle:
			return "Magnet_N100_-200triangle";
			break;
		case enObject_Magnet_S100_Under200_Triangle:
			return "Magnet_S100_-200triangle";
			break;
		case enObject_Magnet_NUnder100_Under200_Triangle:
			return "Magnet_N-100_-200triangle";
			break;
		case enObject_Magnet_SUnder100_Under200_Triangle:
			return "Magnet_S-100_-200triangle";
			break;
		default:
			MessageBoxA(nullptr, "�I�u�W�F�N�g��������܂���ł����B", "�G���[", MB_OK);
			std::abort();
		}
	}


private:
	bool m_seesawFlg = false;					//�V�[�\�[�̍��W�Ɖ�]�����Z�b�g����t���O
	int m_seesawNum = 0;						//�V�[�\�[�ԍ�
	int m_stageNum = 0;							//�X�e�[�W�ԍ�
	int m_magnetNum = 0;						//���Δԍ�
	int m_deathBlockNum = 0;					//�f�X�u���b�N�ԍ�

	Model m_model;								//���f��
	PhysicsStaticObject m_physicsStaticObject;	//�ÓI�����I�u�W�F�N�g
	Level m_level;								//�X�e�[�W


	//���ꂼ��̃N���X�̃|�C���^

	std::vector<Magnet*> m_magnet;
	std::vector<Seesaw*> m_seesaw;
	std::vector<DeathBlock*> m_deathBlock;
	Key* m_key = nullptr;
	TreasureBox* m_treasureBox = nullptr;
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	Player* m_skinModelRender = nullptr;
	GameLevel2D* m_level2D = nullptr;
	SpriteRender* m_spriteRender = nullptr;
	FontRender* m_fontRender = nullptr;
};

