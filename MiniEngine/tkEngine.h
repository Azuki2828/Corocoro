#pragma once

#include "HID/GamePad.h"
#include "../GameTemplate/Game/GameTime.h"

class GraphicsEngine;

enum GameState {
	State_Game,		//�Q�[����
	State_Pause,	//�|�[�Y��
	State_Dead,		//���񂾂Ƃ��̃X�e�[�g
	State_Free		//����ȊO�́A���[�U�[�����߂ėǂ��X�e�[�g
};

class TkEngine {
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~TkEngine();
	/// <summary>
	/// �t���[���̊J�n���ɌĂ΂�鏈���B
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// �t���[���̏I�����ɌĂ΂�鏈���B
	/// </summary>
	void EndFrame();

	void SetGameState(GameState state) {
		m_gameState = state;
	}

	GameState GetGameState() {
		return m_gameState;
	}
	/// <summary>
	/// �Q�[���G���W���̏������B
	/// </summary>
	void Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight);

	const int GetRate()const {
		return m_rate;
	}
private:
	GraphicsEngine* m_graphicsEngine = nullptr;		//�O���t�B�b�N�G���W���B
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//�Q�[���p�b�h�B
	GameTime m_gameTime;
	int m_rate = 0;

	GameState m_gameState = State_Game;
	
};

extern TkEngine* g_engine;	//TK�G���W���B