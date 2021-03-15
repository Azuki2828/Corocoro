#pragma once

class Player;

class Key : public IGameObject
{
public:
	bool Start()override final;

	//鍵を初期化する関数。
	void InitKey(const char* name);

	//ドアを初期化する関数。
	void InitDoor(const char* name);

	//鍵の座標を設定する関数。
	void SetPositionKey(Vector3 pos) { m_keyPos = pos; }

	//ドアの座標を設定する関数。
	void SetPositionDoor(Vector3 pos) { m_doorPos = pos; }

	void Update()override final;
private:
	bool getKeyFlg = false;
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	PhysicsStaticObject m_physicsStaticObject;

	Player* m_player = nullptr;
	Vector3 m_keyPos;		//鍵の座標。
	Vector3 m_doorPos;		//ドアの座標。
};

