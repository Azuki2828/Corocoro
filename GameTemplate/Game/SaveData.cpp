#include "stdafx.h"
#include "SaveData.h"
#include "Game.h"
#include "ResultScene.h"

namespace {
	const float INIT_DATA_SCORE = 999.9f;

	const char* SAVE_DATA_NAME = "Save_Data.dat";
	const char* FILE_TYPE_WB = "wb";
	const char* FILE_TYPE_RB = "rb";
	const int ELEMENT_COUNT = 1;
}

void SaveData::Save()
{
	m_result = FindGO<ResultScene>(NAME_RESULT_SCENE);

	float Record = m_result->GetTime();
	m_stageNum = m_result->GetStageNum();
	if (m_data.record[m_stageNum] >= Record) {
		m_newRecordFlg = true;

		//êVãLò^Çì¸ÇÍë÷Ç¶ÇÈ
		m_data.record[m_stageNum] = Record;
	}


	filesave_t data = { m_data.record[Stage_One],m_data.record[Stage_Two],m_data.record[Stage_Three],m_data.record[Stage_Four] };
	FILE* fp = fopen(SAVE_DATA_NAME, FILE_TYPE_WB);
	if (fp == NULL) {

	}
	fwrite(&data, sizeof(data), ELEMENT_COUNT, fp);
	fclose(fp);
}

void SaveData::Load() {

	m_game = FindGO<Game>(NAME_GAME);

	const char* pname = SAVE_DATA_NAME;
	FILE* fp = fopen(SAVE_DATA_NAME, FILE_TYPE_RB);

	if ((fp = fopen(pname, FILE_TYPE_RB)) == NULL) {

		FILE* fp = fopen(SAVE_DATA_NAME, FILE_TYPE_WB);

		float Record = INIT_DATA_SCORE;
		m_time = Record;
		for (int i = 0; i < Stage_Num; i++) {
			m_data.record[i] = Record;
		}
		if (fp == NULL) {

		}
		fwrite(&m_data, sizeof(m_data), ELEMENT_COUNT, fp);
		for (int i = 0; i < Stage_Num; i++) {
			m_game->SetResultTime(i, m_data.record[i]);
		}
		fclose(fp);
	}
	else {
		fread(&m_data, sizeof(m_data), ELEMENT_COUNT, fp);
		for (int i = 0; i < Stage_Num; i++) {
			m_game->SetResultTime(i, m_data.record[i]);
		}

		fclose(fp);
	}
}