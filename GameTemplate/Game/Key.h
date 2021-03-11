#pragma once

class Player;

class Key : public IGameObject
{
public:
	bool Start()override final;

	void InitKey(const char* name);
	void InitDoor(const char* name);
	void Update()override final;

	void SetPositionKey(Vector3 pos) { m_keyPos = pos; }
	void SetPositionDoor(Vector3 pos) { m_doorPos = pos; }
private:
	bool getKeyFlg = false;
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	PhysicsStaticObject m_physicsStaticObject;

	Player* m_player = nullptr;
	Vector3 m_keyPos;
	Vector3 m_doorPos;
};

