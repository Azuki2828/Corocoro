#pragma once

class Player;

class Magnet : public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;
	void SetState_N() { mState = State_N; }
	void SetState_S() { mState = State_S; }
	void Init(const char* magnetName)
	{
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(magnetName);
		m_skinModelRender->Init(true, false);
	}
private:

	//プレイヤーに力を与える関数。
	void SetMagnetPower()const;


	mutable Vector3 m_length;
	Vector3 m_pos;

	typedef enum {
		State_N,
		State_S,
	}Magnet_State;

	Magnet_State mState;

	Player* m_player = nullptr;

	SkinModelRender* m_skinModelRender = nullptr;
};

