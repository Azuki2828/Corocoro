#pragma once
class Result;
class Game;
class SaveData	: public IGameObject
{
public:
	void Save();
	void Load();

	typedef struct {
		int maxscore;	//�ō��L�^��ۑ�
	}SaveData_t;

	SaveData_t Data;
	Game* game = nullptr;		//�܂�Game�͂Ȃ�
	Result* m_result = nullptr;	//�܂�Result�͂Ȃ�
};

