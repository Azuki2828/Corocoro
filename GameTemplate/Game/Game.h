#pragma once

class Player;
class Background;
class MainCamera;
class GameTime;
class Key;
class SaveData;

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

	Sound_Num
};

class Game : public IGameObject
{
public:
	CPhysicsGhostObject m_ghostBox;
	float m_resulttime = 0;
	float m_timer = 0;
	bool Start()override final;
	~Game();
	void Update()override final;

public: //GetŠÖ”
	float GetTime()
	{
		return m_time;
	}
	float GetBestTime() {
		return m_resulttime;
	}

	bool GetStartFlg() {
		return m_startsoundflg;
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

private:
	int m_stageNum = 3;
	FontRender* m_fontRender = nullptr;
	FontRender* m_recordfontRender = nullptr;
	GameTime* m_gametime = nullptr;
	float m_time = 0;
	CSoundSource* m_sound = nullptr;
	bool m_startsoundflg = true;
	bool doorbreakSoundFlg = true;
	float m_gameStartTime = 0.0f;


	Player* m_player = nullptr;
	Background* m_backGround = nullptr;
	MainCamera* m_camera = nullptr;
	DirectionLight* m_dirLight = nullptr;
	SaveData* m_savedata = nullptr;
	SaveData* m_besttime = nullptr;

	bool KauntoDownSprite = false;
	int KauntoDownTimer = 0;
	SpriteRender* m_sprite[4];
};

