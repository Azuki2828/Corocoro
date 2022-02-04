#include "stdafx.h"
#include "Result.h"
#include "Game.h"
#include "SaveData.h"

bool Result::Start()
{
	
	m_game = FindGO<Game>("game");
	m_time = m_game->GetTime();		//Game�Ŏ擾�����^�C��
	SaveData* savedata = FindGO<SaveData>("savedata");
	savedata->FileSave();	//�^�C�����Z�[�u����
	m_fontRender = NewGO<FontRender>(2);
	m_fontRender->Init(L"Time", { .0f,0.0f });	//����̃^�C����\�����邽�߂̃t�H���g�����_�[


	wchar_t text1[64];
	//����̌o�ߎ��Ԃ�\��
	swprintf_s(text1, L"Time : %2.1f", m_time);
	m_fontRender->SetText(text1);
	m_fontRender->SetPosition({ 0.0f, 0.0f });
	return true;
}

