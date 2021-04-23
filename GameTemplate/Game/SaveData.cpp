#include "stdafx.h"
#include "SaveData.h"
#include "Game.h"
#include "ResultScene.h"

void SaveData::FileSave()
{
	m_result = FindGO<ResultScene>("resultscene");

	float Record = m_result->GetTime();
	//float Record = 1000.0f;
	if (Data.record >= Record) {
		Data.record = Record;
	}


	filesave_t data = { Data.record };
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

		float Record = 1000.0f;
		m_time = Record;
		Data.record = Record;
		if (fp == NULL) {

		}
		fwrite(&Data, sizeof(Data), 1, fp);
		fclose(fp);
	}
	else {
		fread(&Data, sizeof(Data), 1, fp);
		m_game->m_resulttime = Data.record;

		fclose(fp);
	}
}