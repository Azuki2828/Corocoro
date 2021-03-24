#pragma once

class Player;
class Background;
class MainCamera;

class Game : public IGameObject
{
	bool Start()override final;
	void Update()override final;

	Player* m_player = nullptr;
	Background* m_backGround = nullptr;
	MainCamera* m_camera = nullptr;
};

