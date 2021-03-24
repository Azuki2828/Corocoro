#include "stdafx.h"
#include "SaveData.h"
#include "Game.h"		//‚Ü‚¾Game‚Í‚È‚¢

void SaveData::Save() {

	m_result = FindGO<Result>("result");

	int maxscore = m_result->m_maxScore;		//result‚à‚È‚¢
	SaveData_t Data = { maxscore };
	FILE* fp = fopen("Save_Data.data", "wb");
	if (fp == NULL) {

	}
	fwrite(&Data, sizeof(Data), 1, fp);
	fclose(fp);
}

void SaveData::Load() {
	const char* pname = "Save_Data.data";
	FILE* fp = fopen("Save_Data.data", "rb");
	
	if ((fp = fopen(pname, "rb")) == NULL) {
		FILE* fp = fopen("Save_Data.data", "wb");
		int maxscore = 0;
		SaveData_t Data = { maxscore };
		if (fp == NULL) {
			
		}
		fwrite(&Data, sizeof(Data), 1, fp);
		fclose(fp);
	}
	else {
		fread(&Data, sizeof(Data), 1, fp);

		game->m_maxscore = Data,maxscore;

		fclose(fp);
		
	}
}
