#pragma once
class Game;
class Result;
class Player;

class SaveData : public IGameObject
{
public:
	typedef struct {
		float record;
	}filesave_t;

	float  savetime;
	filesave_t Data;


	void FileSave();
	//void Save();
	void Load();
	//void Update();

	float m_time = 0.0f;
	
	Game* m_resulttime = 0;

	Game* m_game = nullptr;
	
	Result* m_result = nullptr;

	FontRender* m_fontRender;
	
};

