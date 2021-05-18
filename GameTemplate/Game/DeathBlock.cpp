#include "stdafx.h"
#include "DeathBlock.h"
#include "Player.h"
#include "MainCamera.h"
#include "Key.h"

bool DeathBlock::Start() {

	m_player = FindGO<Player>("player");
	m_key = FindGO<Key>("key");
	m_skinModelRender->SetPosition(m_pos);
	auto mainCamera = FindGO<MainCamera>("maincamera");
	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, -2.0f);
		m_rotZ.Apply(m_ligData.m_directionLigData[0].Dir);
		});

	Vector3 ghostPos;
	ghostPos = m_pos;
	ghostPos.x += 50.0f;
	ghostPos.y += 50.0f;
	m_ghostBox.CreateBox(
		ghostPos,	//�������͍��W�B
		Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 100.0f, 100.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);
	return true;
}

void DeathBlock::Update() {
	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

		if (m_ghostBox.IsSelf(contactObject) == true) {
			//m_ghostObject�ƂԂ�����
			//m_pointLig->SetActiveFlag(true);	//�|�C���g���C�g������B
			//m_ghostBox.SetPosition({ 700.0f,405.0f,0.0f });
			if (m_player->GetKeyFlg()) {
				m_player->SetPosition(m_key->GetKeyPos());
			}
			else {
				m_player->SetPosition(m_startPos);
			}
			m_player->ClearPower();

			//g_engine->SetGameState(GameState::State_Dead);
		}
	});
}