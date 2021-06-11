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

namespace {
	const int STAGE_NUM = 4;										//ステージの総数

	//オブジェクトの名前
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

	//ステージごとのスタート地点
	const Vector3 STAGE_START_POS[STAGE_NUM] = {
		{ 300.0f,1200.0f,-300.0f },
		{ 300.0f,300.0f,-300.0f },
		{ 300.0f,1300.0f,-300.0f },
		{ 300.0f,1900.0f,-300.0f }
	};

	//ステージごとのファイルパス
	const char* STAGE_FILE_PATH[STAGE_NUM] = {
		"Assets/level/stage01_treasure.tkl",
		"Assets/level/stage02_treasure.tkl",
		"Assets/level/stage03_treasure.tkl",
		"Assets/level/stage04_treasure.tkl"
	};

	const float DEADLINE = -500.0f;										//プレイヤーの死ぬ高さ

	const float ADD_MAGNET_POS50 = 50.0f;								//磁力の発生地点を正確に決めるために加算する定数
	const float ADD_MAGNET_POS150 = 150.0f;								//磁力の発生地点を正確に決めるために加算する定数
	const Vector3 ADD_TREASURE_BOX_POS = { -75.0f,0.0f,-50.0f };		//座標を正しく設定するために加算する定数
	const Vector3 TREASURE_BOX_SCALE_UP = { 2.5f,2.5f,2.5f };			//宝箱に設定する拡大率
	const Vector3 ADD_EFFECT_POS = { 200.0f, -150.0f, -200.0f };		//座標を設定するために加算する定数

	const char* GAME_BACKGROUND_UI = "Assets/image/eheheNS03.dds";		//ゲーム中の背景画像のファイルパス
	const Vector2 GAME_BACKGROUND_UI_WH = { 1300.0f, 750.0f };			//ゲーム中の背景画像の幅と高さ
}

class BackGround : public IGameObject
{
private:
	bool Start() override;
	~BackGround();
	void Update() override;

public:
	/**
	 * @brief 描画関数
	 * @param rc レンダーコンテキスト
	*/
	void Render(RenderContext& rc) override;

	/**
	 * @brief プレイヤーの死ぬ高さを取得する関数
	 * @return プレイヤーの死ぬ高さ
	*/
	float GetDeathPosY() { return DEADLINE; }

	/**
	 * @brief シーソーの座標と回転をリセットするフラグを設定する関数
	 * @param flg シーソーリセットフラグ
	*/
	void SetStart(bool flg) {
		m_seesawFlg = flg;
	}
	
	/**
	 * @brief ステージを初期化する関数
	 * @param filePath ステージのファイルパス
	*/
	void LevelInit(const char* filePath);


	/**
	 * @brief ステージのオブジェクトの名前を取得する関数
	 * @param objectNum オブジェクトの番号
	 * @return オブジェクトの名前
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
			MessageBoxA(nullptr, "オブジェクトが見つかりませんでした。", "エラー", MB_OK);
			std::abort();
		}
	}


private:
	bool m_seesawFlg = false;					//シーソーの座標と回転をリセットするフラグ
	int m_seesawNum = 0;						//シーソー番号
	int m_stageNum = 0;							//ステージ番号
	int m_magnetNum = 0;						//磁石番号
	int m_deathBlockNum = 0;					//デスブロック番号

	Model m_model;								//モデル
	PhysicsStaticObject m_physicsStaticObject;	//静的物理オブジェクト
	Level m_level;								//ステージ


	//それぞれのクラスのポインタ

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

