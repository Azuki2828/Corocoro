#pragma once
class Player;
class Key;

class DeathBlock : public IGameObject
{
private:
	bool Start()override;
	void Update()override;
public:
	void SetStartPos(const Vector3& pos) {
		m_startPos = pos;
	}
	void SetPosition(const Vector3& pos) {
		m_pos = pos;
	}
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	//初期化関数。
	void Init(const char* name)
	{
		char filePathtkm[256];
		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->SetShadowReceiverFlag(true);
		m_skinModelRender->Init(true, false);
	}

private:
	int m_timer = 0;
	bool m_hitPlayer = false;
	int m_returnTimer = 0;
	Effect *m_death = nullptr;
	CSoundSource* DeathSound = nullptr;
	bool n_contactTestFlag = true;
	bool deathFlg = false;

	int deathActiveState = 0; //デスブロックに触れたときのキャラクターのステートを保持

public:
	Vector3 m_pos;
	Vector3 m_startPos = { 0.0f,0.0f,0.0f };
	Vector3 m_scale = g_vec3One;
	CPhysicsGhostObject m_ghostBox;
	SkinModelRender* m_skinModelRender = nullptr;
	Player* m_player = nullptr;
//	Player* m_skinMdelRender = nullptr;
	Key* m_key = nullptr;



};

