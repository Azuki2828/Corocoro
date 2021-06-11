#include "stdafx.h"
#include "MoveObject.h"

bool MoveObject::Start() {
	
	m_skinModelRender = NewGO<SkinModelRender>(enData_Zeroth);
	return true;
}

void MoveObject::Update() {

	//動く速さはどれも違うけど端に到達するタイミングは同じになるようにする。
	moveSpeed = (moveRange_back - moveRange_front) /= TIME_EQUAL;
	m_pos += moveSpeed;

	//設定された右端まできたら動く向きを逆にする。
	if (m_pos.x > moveRange_back.x) {
		m_pos.x = moveRange_back.x;
		moveSpeed *= REVERSE_VECTOR;
	}
	//設定された左端まできたら動く向きを逆にする。
	if (m_pos.x < moveRange_front.x) {
		m_pos.x = moveRange_front.x;
		moveSpeed *= REVERSE_VECTOR;
	}
}