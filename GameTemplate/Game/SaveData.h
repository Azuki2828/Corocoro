#pragma once
class Game;
class ResultScene;
class Player;

class SaveData : public IGameObject
{
public:
	void Save();
	void Load();
	bool GetNewrecordFlg() { return m_newRecordFlg; };

private:
	typedef struct {
		float record[Stage_Num];
	}filesave_t;

	bool m_newRecordFlg = false;
	int m_stageNum = 0;
	float m_time = 0.0f;
	filesave_t m_data;

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	Game* m_game = nullptr;
	ResultScene* m_result = nullptr;
	FontRender* m_fontRender = nullptr;
};