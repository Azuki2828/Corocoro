#pragma once
class Player;

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
	//èâä˙âªä÷êîÅB
	void Init(const char* name)
	{
		char filePathtkm[256];
		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->SetShadowReceiverFlag(true);
		m_skinModelRender->Init(true, false);
	}

	Vector3 m_pos;
	Vector3 m_startPos = { 0.0f,0.0f,0.0f };
	CPhysicsGhostObject m_ghostBox;
	SkinModelRender* m_skinModelRender = nullptr;
	Player* m_player = nullptr;
};

