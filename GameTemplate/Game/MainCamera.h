#pragma once

class Player;

class MainCamera : public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;

	Vector3 m_pos;
	Vector3 m_tar;
	Vector3 toPos;
	Quaternion m_rotY;
	Quaternion m_rotX;

	Player* m_player = nullptr;
};

