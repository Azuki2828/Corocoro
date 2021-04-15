#pragma once

class Player;
class Background;
class MainCamera;
class GameTime;
class Key;

class Game : public IGameObject
{
public:
	bool Start()override final;
	void Update()override final;

private:
	FontRender* m_fontRender = nullptr;
	GameTime* m_gametime = nullptr;
	float time = 0;
	CSoundSource* m_sound = nullptr;
	bool m_startsoundflg = true;
	int m_timer = 0;
	bool doorbreakSoundFlg = true;		


	Player* m_player = nullptr;
	Background* m_backGround = nullptr;
	MainCamera* m_camera = nullptr;
	
};

