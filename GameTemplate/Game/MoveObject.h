#pragma once

namespace {

	const float TIME_EQUAL = 100.0f;
}

class MoveObject : IGameObject
{
private:
	bool Start() override;
	void Update() override;

public:

	void SetMove(Vector3 front, Vector3 back) { moveRange_front = front, moveRange_back = back; }
	
private:
	Vector3 moveRange_front = Vector3::Zero;	//�ړ��͈͂̍��[�B
	Vector3 moveRange_back = Vector3::Zero;		//�ړ��͈͂̉E�[�B
	Vector3 moveSpeed = Vector3::Zero;			//���������B
	Vector3 m_pos = Vector3::Zero;				//���W�B

	SkinModelRender* m_skinModelRender = nullptr;
};

