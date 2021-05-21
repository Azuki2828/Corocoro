#include "stdafx.h"
#include "DeathBlock.h"
#include "Player.h"
#include "MainCamera.h"
#include "Key.h"

bool DeathBlock::Start() {

	m_player = FindGO<Player>("player");
	m_key = FindGO<Key>("key");
	m_skinModelRender->SetPosition(m_pos);

	m_skinModelRender->SetScale(m_scale);

	m_death = NewGO<Effect>(0);
	m_death->Init(u"Assets/effect/death.efk");
	m_death->SetScale({ 100.0f,100.0f,100.0f });

	m_skinModelRender->SetScale(m_sca);
	auto mainCamera = FindGO<MainCamera>("maincamera");
	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, -2.0f);
		m_rotZ.Apply(m_ligData.m_directionLigData[0].Dir);
		});

	Vector3 ghostPos;
	ghostPos = m_pos;
	ghostPos.x += 50.0f * m_sca.x;
	ghostPos.y += 50.0f;

	ghostPos.z -= 200.0f;
	m_ghostBox.CreateBox(
		ghostPos,	//第一引数は座標。
		Quaternion::Identity,		//第二引数は回転クォータニオン。
		{ 100.0f * m_sca.x, 100.0f * m_sca.y, 400.0f * m_sca.z}	//第三引数はボックスのサイズ。
	);

	m_skinModelRender->UpdateWorldMatrix();
	return true;
}

void DeathBlock::Update() {

	Vector3 effPos;

	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {
		m_ligData.uvNoiseOffset += 0.01f;
		float t;
		m_ligData.uvNoiseOffset = modf(m_ligData.uvNoiseOffset, &t);
		if (m_ghostBox.IsSelf(contactObject) == true) {

			//m_ghostObjectとぶつかった
			//m_pointLig->SetActiveFlag(true);	//ポイントライトをつける。
			//m_ghostBox.SetPosition({ 700.0f,405.0f,0.0f });
			m_hitPlayer = true;
			effPos = m_player->GetPosition();
			//if (m_player->GetKeyFlg()) {
			//	m_player->SetPosition(m_key->GetKeyPos());
			//}
		}
		});

	if (m_hitPlayer)
	{
			//死ぬエフェクト再生と効果音
		if (m_player->Getrespawn() == false) {

			m_player->Setrespawn(true);
			m_death->SetPosition(effPos);
			deathActiveState = m_player->DeactivatePlayerModel();
			m_death->Play();
			deathFlg = true;

			DeathSound = NewGO<CSoundSource>(0);

			DeathSound->Init(L"Assets/sound/death.wav");
			DeathSound->SetVolume(0.5f);
			DeathSound->Play(false);	//ワンショット再生

			/*m_timer++;
			if (m_timer == 60) {
				g_engine->SetGameState(GameState::State_Game);
				m_timer = 0;*/
			}
			m_timer++;
			if (m_timer >= 90)
			{
				m_player->Setrespawn(false);
				m_timer = 0;
				m_hitPlayer = false;
				bool* flag = &m_hitPlayer;

			}
			else if (m_timer >= 80) {

				if (m_player->GetKeyFlg()) {
					m_player->SetPosition(m_key->GetKeyPos());
					m_player->ActivatePlayerModel(deathActiveState);
					deathFlg = false;
				}
				else {
					m_player->SetPosition(m_startPos);
					m_player->ActivatePlayerModel(deathActiveState);
					deathFlg = false;
				}
				//m_hitPlayer = false;

			}


			m_player->ClearPower();

			//g_engine->SetGameState(GameState::State_Dead);
	}
}

