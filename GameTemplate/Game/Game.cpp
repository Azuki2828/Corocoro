#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "MainCamera.h"

bool Game::Start() {

	//地形を生成。
	m_backGround = NewGO<Background>(0,"background");
	//プレイヤーを生成。
	m_player = NewGO<Player>(0, "player");
	//カメラを生成。
	m_camera = NewGO<MainCamera>(0);

	return true;
}

void Game::Update() {

}