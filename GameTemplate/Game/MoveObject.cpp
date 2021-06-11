#include "stdafx.h"
#include "MoveObject.h"

bool MoveObject::Start() {
	
	m_skinModelRender = NewGO<SkinModelRender>(enData_Zeroth);
	return true;
}

void MoveObject::Update() {

	//���������͂ǂ���Ⴄ���ǒ[�ɓ��B����^�C�~���O�͓����ɂȂ�悤�ɂ���B
	moveSpeed = (moveRange_back - moveRange_front) /= TIME_EQUAL;
	m_pos += moveSpeed;

	//�ݒ肳�ꂽ�E�[�܂ł����瓮���������t�ɂ���B
	if (m_pos.x > moveRange_back.x) {
		m_pos.x = moveRange_back.x;
		moveSpeed *= REVERSE_VECTOR;
	}
	//�ݒ肳�ꂽ���[�܂ł����瓮���������t�ɂ���B
	if (m_pos.x < moveRange_front.x) {
		m_pos.x = moveRange_front.x;
		moveSpeed *= REVERSE_VECTOR;
	}
}