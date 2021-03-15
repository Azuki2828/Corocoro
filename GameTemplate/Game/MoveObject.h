#pragma once
class MoveObject : IGameObject
{
public:
	bool Start();
	void SetMove(Vector3 front, Vector3 back) { moveRange_front = front, moveRange_back = back; }
	void Update();
private:
	Vector3 moveRange_front, moveRange_back;
	Vector3 m_pos;
	SkinModelRender* m_skinModelRender = nullptr;
};

