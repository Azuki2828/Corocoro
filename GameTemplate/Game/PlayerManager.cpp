#include "stdafx.h"
#include "Player.h"
#include "PlayerManager.h"

bool PlayerManager::Start() {
	
	//m_font = NewGO<FontRender>(1);
	//wchar_t numtext[2][64];
	//
	//swprintf_s(numtext[0], L"HP+%d", m_player[0]->GetActive());
	//swprintf_s(numtext[1], L"HP+%d", m_player[1]->GetActive());
	//m_font->Init(numtext[0]);
	m_player[0] = NewGO<Player>(0, "Player_N");
	m_player[1] = NewGO<Player>(0, "Player_S");
	
	m_player[0]->SetPlayerName(L"Player_N");
	m_player[1]->SetPlayerName(L"Player_S");

	m_player[1]->SetActiveFlag(false);

	m_charaCon.Init(40.0f, 100.0f, g_vec3Zero);
	m_position = m_charaCon.Execute(m_power, 1.0f);
	return true;
}

void PlayerManager::Update() {

	//m_position = m_player[1]->GetPosition();
	//Aƒ{ƒ^ƒ“‚ÅŽ¥‹É‚Ì•ÏŠ·
	if (g_pad[0]->IsTrigger(enButtonA)) {

		ChangeState();

		for (int i = 0; i < 2; i++) {
			//m_player[i]->ChangeState();

			if (m_player[i]->IsActive() == true) {
				m_player[i]->SetActiveFlag(false);
			}
			else {
				m_player[i]->SetActiveFlag(true);
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		
		m_player[i]->SetPosition(m_position);
	}
}

void PlayerManager::ChangeState() {
	if (pState == State_N) {
		pState = State_S;
	}
	else if (pState == State_S) {
		pState = State_N;
	}
}