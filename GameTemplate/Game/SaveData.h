#pragma once
class Game;
class Result;

class SaveData : public IGameObject
{
public:
	typedef struct {
		float Record;
	}filesave;

	float  savetime;
	filesave Data;

	void FileSave();
	void Save();
	void Load();
	void Update();

	Game* game = nullptr;
	Result* m_result = nullptr;
	
};

