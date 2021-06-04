#include "stdafx.h"
#include "SaveData.h"
#include "Game.h"
#include "ResultScene.h"

void SaveData::Save()
{
	m_result = FindGO<ResultScene>("resultscene");

	float Record = m_result->GetTime();
	m_stageNum = m_result->GetStageNum() - 1;
	//float Record = 1000.0f;
	if (m_data.record[m_stageNum] >= Record) {
		m_newRecordFlg = true;
		//新記録の文字を流す


		//新記録を入れ替える
		m_data.record[m_stageNum] = Record;
		int a = 0;
	}


	filesave_t data = { m_data.record[0],m_data.record[1],m_data.record[2],m_data.record[3] };
	FILE* fp = fopen("Save_Data.dat", "wb");
	if (fp == NULL) {

	}
	fwrite(&data, sizeof(data), 1, fp);
	fclose(fp);
}

void SaveData::Load() {

	m_game = FindGO<Game>("game");

	const char* pname = "Save_Data.dat";
	FILE* fp = fopen("Save_Data.dat", "rb");

	if ((fp = fopen(pname, "rb")) == NULL) {

		FILE* fp = fopen("Save_Data.dat", "wb");

		float Record = 999.9f;
		m_time = Record;
		for (int i = 0; i < 4; i++) {
			m_data.record[i] = Record;
		}
		if (fp == NULL) {

		}
		fwrite(&m_data, sizeof(m_data), 1, fp);
		for (int i = 0; i < 4; i++) {
			m_game->SetResultTime(i, m_data.record[i]);
		}
		fclose(fp);
	}
	else {
		fread(&m_data, sizeof(m_data), 1, fp);
		for (int i = 0; i < 4; i++) {
			m_game->SetResultTime(i, m_data.record[i]);
		}

		fclose(fp);
	}
}