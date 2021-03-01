#pragma once

class Player;

class PlayerManager : public IGameObject
{
public:
	bool Start()override final;
	void Update()override final;
	const Vector3& GetPosition() { return m_position; }
	const int GetPlayerState()const { return pState; }
	void ChangeState();
	void ReceivePower(Vector3 pow) { m_power += pow; }
private:
	typedef enum {
		State_N,
		State_S,
	}Player_State;

	//プレイヤーのステート。
	Player_State pState = State_N;
	CharacterController m_charaCon;
	Player* m_player[2] = { nullptr };
	Vector3 m_position;
	Vector3 m_power;
};

