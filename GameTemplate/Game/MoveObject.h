#pragma once
class MoveObject : IGameObject
{
public:
	bool Start();
	void SetMove(Vector3 front, Vector3 back) { moveRange_front = front, moveRange_back = back; }
	void Update();
private:
	Vector3 moveRange_front;	//移動範囲の左端。
	Vector3 moveRange_back;		//移動範囲の右端。
	Vector3 moveSpeed;			//動く速さ。
	Vector3 m_pos;				//座標。
	SkinModelRender* m_skinModelRender = nullptr;
};

