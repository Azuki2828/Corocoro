#include "stdafx.h"
#include "DeathBlock.h"
#include "Player.h"

bool DeathBlock::Start() {

	m_player = FindGO<Player>("player");
	m_skinModelRender->SetPosition(m_pos);

	Vector3 ghostPos;
	ghostPos = m_pos;
	ghostPos.x += 50.0f;
	ghostPos.y += 50.0f;
	m_ghostBox.CreateBox(
		ghostPos,	//第一引数は座標。
		Quaternion::Identity,		//第二引数は回転クォータニオン。
		{ 100.0f, 100.0f, 400.0f }	//第三引数はボックスのサイズ。
	);
	return true;
}

void DeathBlock::Update() {
	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

		if (m_ghostBox.IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった
			//m_pointLig->SetActiveFlag(true);	//ポイントライトをつける。
			//m_ghostBox.SetPosition({ 700.0f,405.0f,0.0f });
			if (m_player->GetKeyFlg()) {
				m_player->SetPosition()
			}
			m_player->SetPosition(m_startPos);
			m_player->ClearPower();
		}
		});
}