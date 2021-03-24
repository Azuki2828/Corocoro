#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "MainCamera.h"

bool Game::Start() {

	//�n�`�𐶐��B
	m_backGround = NewGO<Background>(0,"background");
	//�v���C���[�𐶐��B
	m_player = NewGO<Player>(0, "player");
	//�J�����𐶐��B
	m_camera = NewGO<MainCamera>(0);

	return true;
}

void Game::Update() {

}