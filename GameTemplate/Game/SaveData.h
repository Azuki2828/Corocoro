#pragma once
class Result;
class Game;
class SaveData	: public IGameObject
{
public:
	void Save();
	void Load();

	typedef struct {
		int maxscore;	//Å‚‹L˜^‚ğ•Û‘¶
	}SaveData_t;

	SaveData_t Data;
	Game* game = nullptr;		//‚Ü‚¾Game‚Í‚È‚¢
	Result* m_result = nullptr;	//‚Ü‚¾Result‚Í‚È‚¢
};

