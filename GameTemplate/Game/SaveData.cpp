#include "stdafx.h"
#include "SaveData.h"
#include "Game.h"
#include "Result.h"

void SaveData::FileSave()
{
	m_result = FindGO<Result>("result");

	float Record = m_result->m_result;	//‚¿‚å‚Á‚Æ‘Ò‚Á‚Ä‚Ä
}