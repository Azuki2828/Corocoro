#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "MainCamera.h"
#include "GameTime.h"

bool Game::Start() {

	m_dirLight = NewGO<DirectionLight>(0);
	m_dirLight->SetLigDirection();
	m_dirLight->SetLigColor();
	//プレイヤーを生成。
	m_player = NewGO<Player>(0, "player");
	//地形を生成。
	m_backGround = NewGO<Background>(0,"background");
	//カメラを生成。
	m_camera = NewGO<MainCamera>(0);

	return true;
}

void Game::Update() {

}