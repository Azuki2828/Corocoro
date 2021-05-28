#include "stdafx.h"
#include "SaveData.h"
#include "Game.h"
#include "ResultScene.h"

void SaveData::FileSave()
{
	m_result = FindGO<ResultScene>("resultscene");

	float Record = m_result->GetTime();
	m_stageNum = m_result->GetStageNum() - 1;
	//float Record = 1000.0f;
	if (Data.record[m_stageNum] >= Record) {
		m_NewrecordFlg = true;
		//新記録の文字を流す


		//新記録を入れ替える
		Data.record[m_stageNum] = Record;
		int a = 0;
	}


	filesave_t data = { Data.record[0],Data.record[1],Data.record[2],Data.record[3] };
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
			Data.record[i] = Record;
		}
		if (fp == NULL) {

		}
		fwrite(&Data, sizeof(Data), 1, fp);
		for (int i = 0; i < 4; i++) {
			m_game->m_resulttime[i] = Data.record[i];
		}
		fclose(fp);
	}
	else {
		fread(&Data, sizeof(Data), 1, fp);
		for (int i = 0; i < 4; i++) {
			m_game->m_resulttime[i] = Data.record[i];
		}

		fclose(fp);
	}
}