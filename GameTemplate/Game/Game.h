#pragma once

class Player;
class Background;
class MainCamera;

class Game : public IGameObject
{
	bool Start()override final;
	~Game();
	void Update()override final;

	Player* m_player = nullptr;
	Background* m_backGround = nullptr;
	MainCamera* m_camera = nullptr;
	DirectionLight* m_dirLight = nullptr;
};

