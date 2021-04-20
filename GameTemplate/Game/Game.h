#pragma once

class Player;
class Background;
class MainCamera;
class GameTime;
class Key;
class SaveData;

class Game : public IGameObject
{
public:
	float m_resulttime = 0;
	int m_timer = 0;
	bool Start()override final;
	~Game();
	void Update()override final;

public: //Getä÷êî
	float GetTime()
	{
		return m_time;
	}

	bool GetStartFlg() {
		return m_startsoundflg;
	}

private:
	FontRender* m_fontRender = nullptr;
	FontRender* m_recordfontRender = nullptr;
	GameTime* m_gametime = nullptr;
	float m_time = 0;
	CSoundSource* m_sound = nullptr;
	bool m_startsoundflg = true;
	bool doorbreakSoundFlg = true;


	Player* m_player = nullptr;
	Background* m_backGround = nullptr;
	MainCamera* m_camera = nullptr;
	DirectionLight* m_dirLight = nullptr;
	SaveData* m_savedata = nullptr;
	SaveData* m_besttime = nullptr;
	
};

