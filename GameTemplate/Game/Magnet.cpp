#include "stdafx.h"
#include "Magnet.h"
#include "Player.h"
#include "Key.h"
#include "Game.h"

bool Magnet::Start() {

	//座標を登録。

	m_skinModelRender->SetPosition(m_pos);
	m_key = FindGO<Key>("key");
	m_game = FindGO<Game>("game");

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

	SetMagnetTriggerBox(m_game->GetStageNum());
	m_player->GetRigidBody()->GetBody()->setIgnoreCollisionCheck(m_ghostBox.GetGhostObject(), true);
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
	//m_length = m_player->GetPosition() - m_pos;
	//
	////if (!m_key->GetdoorbreakFlg()) {
	//	//プレイヤーとの距離が６m以内だったら力を与える関数を呼び出す。
	//if (m_length.Length() <= 1000.0f) {
	//	SetMagnetPower();
	//}
	//}
	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {
		if (m_ghostBox.IsRegistPhysicsWorld() && m_ghostBox.IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった
			//m_pointLig->SetActiveFlag(true);	//ポイントライトをつける。
			m_ghostBox.SetPosition({ 700.0f,405.0f,0.0f });
		}
		});
	//m_skinModelRender->SetPosition(m_pos);

}

void Magnet::SetMagnetPower()const {

	//基礎磁力の強さ。
	float magnetPower = 20000.0f;

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

void Magnet::SetMagnetTriggerBox(int stageNum) {

	switch (stageNum) {		//ステージ番号

	case 1:


		switch (m_magnetNum) {		//磁石番号
		case 0:
			m_ghostBox.CreateBox(
				{ 500.0f, 405.0f, 0.0f },	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				{ 200.0f, 200.0f, 750.0f }	//第三引数はボックスのサイズ。
			);
			break;
		case 1:
			m_ghostBox.CreateBox(
				{ 500.0f, 405.0f, 0.0f },	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				{ 200.0f, 200.0f, 750.0f }	//第三引数はボックスのサイズ。
			);
			break;
		}

		break;
	}
}