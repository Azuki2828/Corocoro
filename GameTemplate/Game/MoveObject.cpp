#include "stdafx.h"
#include "MoveObject.h"

bool MoveObject::Start() {
	
	m_skinModelRender = NewGO<SkinModelRender>(0);
	return true;
}

void MoveObject::Update() {
	static Vector3 moveSpeed = (moveRange_back - moveRange_front) /= 100.0f;
	m_pos += moveSpeed;
	if (m_pos.x > moveRange_back.x) {
		m_pos.x = moveRange_back.x;
		moveSpeed *= -1.0f;
	}
	if (m_pos.x < moveRange_front.x) {
		m_pos.x = moveRange_front.x;
		moveSpeed *= -1.0f;
	}
}