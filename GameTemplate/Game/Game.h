#pragma once

class Player;
class BackGround;
class MainCamera;
class GameTime;
class Key;
class SaveData;
class ResultScene;
class TreasureBox;

enum SoundList {
	BGM_Title,
	BGM_Game,
	BGM_GameUpTempo,
	SE_GameClear,
	SE_CursolMove,
	SE_DecisionButton,
	SE_CountDown,
	SE_NSChange,
	SE_KeyGet,
	SE_BoxOpen,
	SE_Death,
	SE_ReStart,

	Sound_Num
};

class Game : public IGameObject
{
private:
	bool Start()override final;
	~Game();
	void Update()override final;

public:
	float GetTime()
	{
		return m_time;
	}
	float GetBestTime() {
		return m_resultTime[m_stageNum - 1];
	}

	bool GetStartFlg() {
		return m_startSoundflg;
	}

	int GetGameStartTime() {
		return m_gameStartTime;
	}
	int GetStageNum() {
		return m_stageNum;
	}
	void SetStageNum(int num) {
		m_stageNum = num;
	}

	void SetHitPlayer(bool flg) {
		m_hitPlayer = flg;
	}

	bool GetGameFlg() {
		return m_gameStartFlg;
	}

	void SetResultTime(int num, float time) {
		m_resultTime[num] = time;
	}

private:
	bool m_treasureFlg = false;
	bool m_respawnEfk = false;
	bool m_gameFlg = false;
	bool deathFlg = false;
	bool m_hitPlayer = false;
	bool m_resetFlg = false;
	bool m_startSoundflg = true;
	bool m_gameStartFlg = false;
	bool m_countDownSprite = false;
	int m_countDownTimer = 0;
	int m_deathActiveState = 0; //デスブロックに触れたときのキャラクターのステートを保持
	int m_stageNum = 3;
	float m_time = 0.0f;
	float m_gameStartTime = 0.0f;
	float m_resultTime[4] = { 0.0f };
	float m_resultSceneTime = 0.0f;
	float m_timer = 0.0f;
	float m_playerTimer = 0.0f;
	Vector3 m_playerPos = Vector3::Zero;
	CPhysicsGhostObject m_ghostBox;

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	FontRender* m_fontRender = nullptr;
	GameTime* m_gametime = nullptr;
	Effect* m_effect = nullptr;
	Effect* m_efkRespawn = nullptr;
	Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
	MainCamera* m_camera = nullptr;
	DirectionLight* m_dirLight = nullptr;
	SaveData* m_saveData = nullptr;
	ResultScene* m_resultScene = nullptr;
	SpriteRender* m_sprite[4];
	Key* m_key = nullptr;
	TreasureBox* m_treasureBox = nullptr;
};

