#pragma once

class Player;

class Camera : public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;

	Vector3 toCameraPos = { 0.0f,0.0f,250.0f };
	Vector3 m_pos, m_tar;

	Player* m_player = nullptr;
};

