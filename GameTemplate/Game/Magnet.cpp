#include "stdafx.h"
#include "Magnet.h"
#include "Player.h"
#include "Key.h"

bool Magnet::Start() {

	//座標を登録。

	m_skinModelRender->SetPosition(m_pos);
	m_key = FindGO<Key>("key");

	/*
	名前分けしようとしてたときのやつ。
	////自身の名前によってステートを分けて初期化する。
	//if (strcmp(this->m_name.c_str(), "N_Magnet") == 0) {
	//	mState = State_N;
	//}
	//else if (strcmp(this->m_name.c_str(), "S_Magnet") == 0) {
	//	mState = State_S;
	//}

	*/
	
	//動く物体じゃないなら座標を更新して当たり判定を付ける。
	if (!moveFlg) {
		m_skinModelRender->UpdateWorldMatrix();
		m_physicsStaticObject.CreateFromModel(
			*m_skinModelRender->GetModel(),
			m_skinModelRender->GetModel()->GetWorldMatrix()
		);
		m_physicsStaticObject.SetFriction(10.0f);
	}


	//動く物体じゃないなら動く速さだけ設定。
	if (moveFlg) {
		moveSpeed = (moveRange_back - moveRange_front) /= 150.0f;
	}

	//プレイヤーのオブジェクトを探す。
	m_player = FindGO<Player>("player");
	return true;
}

void Magnet::Update() {
	
	//動く物体なら
	if (moveFlg) {


		m_pos += moveSpeed;

		//設定された右端まできたら動く向きを逆にする。
		if (m_pos.x > moveRange_back.x) {
			m_pos.x = moveRange_back.x;
		
		m_timer++;								//
		if (m_timer == 60) {					//<変更>動く磁石が1秒間一時停止するようにif文追加
			moveSpeed *= -1.0f;
			m_timer = 0;						//
			}
		}
		//設定された左端まできたら動く向きを逆にする。
		if (m_pos.x < moveRange_front.x) {
			m_pos.x = moveRange_front.x;

		m_timer++;								//
		if (m_timer == 60) {					//<変更>動く磁石が1秒間停止するようにif文追加
			moveSpeed *= -1.0f;
			m_timer = 0;						//
			}
		}
	}

	//座標を登録。
	m_skinModelRender->SetPosition(m_pos);
	//プレイヤーに向かって伸びるベクトル(長さ)。
	m_length = m_player->GetPosition() - m_pos;

	if (!m_key->GetdoorbreakFlg()) {
		//プレイヤーとの距離が６m以内だったら力を与える関数を呼び出す。
		if (m_length.Length() <= 1000.0f) {
			SetMagnetPower();
		}
	}

	//m_skinModelRender->SetPosition(m_pos);

}

void Magnet::SetMagnetPower()const {

	//基礎磁力の強さ。
	float magnetPower = 120000.0f;

	//プレイヤーと自身の磁磁極が同じなら自身に向かって伸びるベクトルにする。
	if (mState != m_player->GetPlayerState()) {
		m_length *= -1.0f;
	}

	//力を定数倍する。
	float power = (1 / m_length.Length()) * magnetPower;

	//強い磁石なら磁力を1.5倍に。
	if (plusFlg) {
		power *= 1.5f;
	}
	//ベクトルを正規化する。
	m_length.Normalize();

	//正規化したベクトルに磁力を掛ける。
	m_length *= power;

	//Z方向への力を０にする。
	m_length.z = 0.0f;

	//プレイヤーに力を与える。
	m_player->ReceivePower(m_length);
}