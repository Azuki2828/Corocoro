#pragma once

class Player;

class Key : public IGameObject
{
public:
	bool Start()override final;

	//��������������֐��B
	void InitKey(const char* name);

	//�h�A������������֐��B
	void InitDoor(const char* name);

	//���̍��W��ݒ肷��֐��B
	void SetPositionKey(Vector3 pos) { m_keyPos = pos; }

	//�h�A�̍��W��ݒ肷��֐��B
	void SetPositionDoor(Vector3 pos) { m_doorPos = pos; }

	void Update()override final;
private:
	bool getKeyFlg = false;
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	PhysicsStaticObject m_physicsStaticObject;

	Player* m_player = nullptr;
	Vector3 m_keyPos;		//���̍��W�B
	Vector3 m_doorPos;		//�h�A�̍��W�B
};

