#pragma once

#include "HID/GamePad.h"
#include "../GameTemplate/Game/GameTime.h"

class GraphicsEngine;

enum GameState {
	State_Game,		//ゲーム中
	State_Pause,	//ポーズ中
	State_Dead,		//死んだときのステート
	State_Free		//それ以外の、ユーザーが決めて良いステート
};

class TkEngine {
public:
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~TkEngine();
	/// <summary>
	/// フレームの開始時に呼ばれる処理。
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// フレームの終了時に呼ばれる処理。
	/// </summary>
	void EndFrame();

	void SetGameState(GameState state) {
		m_gameState = state;
	}

	GameState GetGameState() {
		return m_gameState;
	}
	/// <summary>
	/// ゲームエンジンの初期化。
	/// </summary>
	void Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight);

	const int GetRate()const {
		return m_rate;
	}
private:
	GraphicsEngine* m_graphicsEngine = nullptr;		//グラフィックエンジン。
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//ゲームパッド。
	GameTime m_gameTime;
	int m_rate = 0;

	GameState m_gameState = State_Game;
	
};

extern TkEngine* g_engine;	//TKエンジン。