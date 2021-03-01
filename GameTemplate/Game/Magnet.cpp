#include "stdafx.h"
#include "Magnet.h"
#include "PlayerManager.h"

bool Magnet::Start() {


	//自身の名前によってステートを分けて初期化する。
	if (strcmp(this->m_name.c_str(), "N_Magnet") == 0) {
		mState = State_N;
	}
	else if (strcmp(this->m_name.c_str(), "S_Magnet") == 0) {
		mState = State_S;
	}

	//プレイヤーのオブジェクトを探す。
	m_player = FindGO<PlayerManager>("player");
	return true;
}

void Magnet::Update() {
	
	//プレイヤーに向かって伸びるベクトル(長さ)。
	m_length = m_player->GetPosition() - m_pos;

	//プレイヤーとの距離が10m以内だったら力を与える関数を呼び出す。
	if (m_length.Length() <= 1000.0f) {
		SetMagnetPower();
	}
}

void Magnet::SetMagnetPower()const {


	//プレイヤーと自身の磁磁極が同じなら自身に向かって伸びるベクトルにする。
	if (mState != m_player->GetPlayerState()) {
		m_length *= -1.0f;
	}

	//力を定数倍する。
	float power = (1 / m_length.Length()) * 5.0f;

	//ベクトルを正規化する。
	m_length.Normalize();


	//プレイヤーに力を与える。
	m_player->ReceivePower(m_length * power);
}