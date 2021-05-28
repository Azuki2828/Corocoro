#pragma once
class Game;
class ResultScene;
class Player;

class SaveData : public IGameObject
{
public:
	typedef struct {
		float record[4];
	}filesave_t;

	float  savetime;
	filesave_t Data;



	void FileSave();
	//void Save();
	void Load();
	//void Update();

	bool m_NewrecordFlg = false;
	bool GetNewrecordFlg() { return m_NewrecordFlg; };

	float m_time = 0.0f;
	int m_stageNum;

	Game* m_resulttime = 0;

	Game* m_game = nullptr;

	ResultScene* m_result = nullptr;

	FontRender* m_fontRender;

};