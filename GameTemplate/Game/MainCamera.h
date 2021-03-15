#pragma once

class Player;

class MainCamera : public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;

	Vector3 m_pos;		//���_�B
	Vector3 m_tar;		//�����_�B
	//Vector3 toPos = { 0.0f,200.0f,-4000.0f };

	//�����_����̃x�N�g���B
	Vector3 toPos = { 0.0f,200.0f,-1800.0f };

	//��]�B
	Quaternion m_rotY;
	Quaternion m_rotX;

	Player* m_player = nullptr;
};

