#pragma once

class PlayerManager;

class Magnet : public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;
private:

	//�v���C���[�ɗ͂�^����֐��B
	void SetMagnetPower()const;


	mutable Vector3 m_length;
	Vector3 m_pos;

	typedef enum {
		State_N,
		State_S,
	}Magnet_State;

	Magnet_State mState;

	PlayerManager* m_player = nullptr;
};

