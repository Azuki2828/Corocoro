#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "GameTime.h"
#include "MainCamera.h"
#include "Key.h"

bool Game::Start() {

	//�n�`�𐶐��B
	m_backGround = NewGO<Background>(0, "background");
	//�v���C���[�𐶐��B
	m_player = NewGO<Player>(0, "player");
	//�J�����𐶐��B
	m_camera = NewGO<MainCamera>(0);
	//�t�H���g�����_�[�𐶐�
	m_fontRender = NewGO<FontRender>(2);
	//���Ԍo�߂�\��
	m_fontRender->Init(L"Time", { .0f,0.0f });


	

	
	return true;
}

void Game::Update() {

	if (m_startsoundflg == true) {
		m_sound = NewGO<CSoundSource>(0);

		m_sound->Init(L"Assets/sound/CountDown.wav");	//�X�^�[�ƊJ�n���̌��ʉ�
		m_sound->SetVolume(1.0f);
		m_sound->Play(false);
		m_startsoundflg = false;
	}
	
	wchar_t text1[4][64];
	
	
	m_timer++;		//�X�^�[�g�̌��ʉ�����I�������^�C���v���J�n�̂��߂̃^�C��
	if (m_timer >= 200 && doorbreakSoundFlg == true) {
		time += GameTime::GameTimeFunc().GetFrameDeltaTime();
	}

	swprintf_s(text1[0], L"Time : %2.1f", time);
	m_fontRender->SetText(text1[0]);
	m_fontRender->SetPosition({ 350.0f, 350.0f });
	

	if (m_player->GetdoorbreakFlg() == true && doorbreakSoundFlg == true) {		
		doorbreakSoundFlg = false;			//�S�[��������v���I��

	}
		
}