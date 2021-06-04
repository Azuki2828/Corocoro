#pragma once
#include "Level.h"
/// <summary>
/// 背景クラス。
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
	float m_deathPosY = 0.0f;					//死ぬY座標。ステージによってポジションは異なる。
	Model m_model;								//モデル
	PhysicsStaticObject m_physicsStaticObject;	//静的物理オブジェクト・
	Level m_level;								//レベル
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
	FontRender* m_fontRender = nullptr;
	CSoundSource* m_gameBGMSound = nullptr;		//BGM用サウンドソース


	/**
	 * @brief それぞれのクラスのポインタ
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

