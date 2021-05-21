#include "stdafx.h"
#include "DeathBlock.h"
#include "Player.h"
#include "Key.h"

bool DeathBlock::Start() {

	m_player = FindGO<Player>("player");
	m_key = FindGO<Key>("key");
	m_skinModelRender->SetPosition(m_pos);
	m_skinModelRender->SetScale(m_scale);

	m_death = NewGO<Effect>(0);
	m_death->Init(u"Assets/effect/death.efk");
	m_death->SetScale({ 100,100.0f,100.0f });

	Vector3 ghostPos;
	ghostPos = m_pos;
	ghostPos.x += 50.0f;
	ghostPos.y += 50.0f;
	Vector3 ghostScale = { 100.0f, 100.0f, 400.0f };
	ghostScale.x *= m_scale.x;
	ghostScale.y *= m_scale.y;
	ghostScale.z *= m_scale.z;

	m_ghostBox.CreateBox(
		ghostPos,	//第一引数は座標。
		Quaternion::Identity,		//第二引数は回転クォータニオン。
		ghostScale	//第三引数はボックスのサイズ。
	);
	return true;
}

void DeathBlock::Update()
{
	if (n_contactTestFlag)
	{
		PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

			if (m_ghostBox.IsSelf(contactObject) == true) {
				//m_ghostObjectとぶつかった
				//m_pointLig->SetActiveFlag(true);	//ポイントライトをつける。
				//m_ghostBox.SetPosition({ 700.0f,405.0f,0.0f });
				m_hitPlayer = true;
			}
		});
	}

	if (m_hitPlayer)
	{
			//死ぬエフェクト再生と効果音
		if (m_player->Getrespawn() == false) {


			Vector3 effPos = m_player->GetPosition();
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
		}
	}
