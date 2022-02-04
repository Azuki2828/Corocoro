#include "stdafx.h"
#include "Result.h"
#include "Game.h"
#include "SaveData.h"

bool Result::Start()
{
	
	m_game = FindGO<Game>("game");
	m_time = m_game->GetTime();		//Gameで取得したタイム
	SaveData* savedata = FindGO<SaveData>("savedata");
	savedata->FileSave();	//タイムをセーブする
	m_fontRender = NewGO<FontRender>(2);
	m_fontRender->Init(L"Time", { .0f,0.0f });	//今回のタイムを表示するためのフォントレンダー


	wchar_t text1[64];
	//今回の経過時間を表示
	swprintf_s(text1, L"Time : %2.1f", m_time);
	m_fontRender->SetText(text1);
	m_fontRender->SetPosition({ 0.0f, 0.0f });
	return true;
}

