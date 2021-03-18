#pragma once
class MoveObject : IGameObject
{
public:
	bool Start();
	void SetMove(Vector3 front, Vector3 back) { moveRange_front = front, moveRange_back = back; }
	void Update();
private:
	Vector3 moveRange_front;	//�ړ��͈͂̍��[�B
	Vector3 moveRange_back;		//�ړ��͈͂̉E�[�B
	Vector3 moveSpeed;			//���������B
	Vector3 m_pos;				//���W�B
	SkinModelRender* m_skinModelRender = nullptr;
};

