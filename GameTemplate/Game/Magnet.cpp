#include "stdafx.h"
#include "Magnet.h"
#include "Player.h"

bool Magnet::Start() {

	m_skinModelRender->SetPosition(m_pos);
	////自身の名前によってステートを分けて初期化する。
	//if (strcmp(this->m_name.c_str(), "N_Magnet") == 0) {
	//	mState = State_N;
	//}
	//else if (strcmp(this->m_name.c_str(), "S_Magnet") == 0) {
	//	mState = State_S;
	//}
	if (!moveFlg) {
		m_skinModelRender->UpdateWorldMatrix();
		m_physicsStaticObject.CreateFromModel(
			*m_skinModelRender->GetModel(),
			m_skinModelRender->GetModel()->GetWorldMatrix()
		);
	}

	if (moveFlg) {
		moveSpeed = (moveRange_back - moveRange_front) /= 150.0f;
	}
	//プレイヤーのオブジェクトを探す。
	m_player = FindGO<Player>("player");
	return true;
}

void Magnet::Update() {
	

	if (moveFlg) {
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
	m_skinModelRender->SetPosition(m_pos);
	//プレイヤーに向かって伸びるベクトル(長さ)。
	m_length = m_player->GetPosition() - m_pos;

	//プレイヤーとの距離が10m以内だったら力を与える関数を呼び出す。
	if (m_length.Length() <= 600.0f) {
		SetMagnetPower();
	}

	//m_skinModelRender->SetPosition(m_pos);

}

void Magnet::SetMagnetPower()const {

	float magnetPower = 60.0f;

	//プレイヤーと自身の磁磁極が同じなら自身に向かって伸びるベクトルにする。
	if (mState != m_player->GetPlayerState()) {
		m_length *= -1.0f;
	}

	//力を定数倍する。
	float power = (1 / m_length.Length()) * magnetPower;

	if (plusFlg) {
		power *= 1.5f;
	}
	//ベクトルを正規化する。
	m_length.Normalize();

	m_length *= power;
	m_length.z = 0.0f;

	//プレイヤーに力を与える。
	m_player->ReceivePower(m_length);
}