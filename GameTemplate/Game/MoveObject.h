#pragma once
/**
 * @brief 
*/
class MoveObject : IGameObject
{
public:
	/**
	 * @brief 
	 * @return 
	*/
	bool Start();
	/**
	 * @brief 
	 * @param front 
	 * @param back 
	*/
	void SetMove(Vector3 front, Vector3 back) { moveRange_front = front, moveRange_back = back; }
	/**
	 * @brief 
	*/
	void Update();
private:
	Vector3 moveRange_front;	//�ړ��͈͂̍��[�B
	Vector3 moveRange_back;		//�ړ��͈͂̉E�[�B
	Vector3 moveSpeed;			//���������B
	Vector3 m_pos;				//���W�B
	SkinModelRender* m_skinModelRender = nullptr;
};

