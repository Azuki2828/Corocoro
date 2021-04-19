#pragma once

class Game;
class SaveData;

class Result : public IGameObject
{
public:

	float m_result;
	bool Start();
	bool finishFlg = false;
	void Update();
	float GetTime()
	{
		return m_time;
	}
	FontRender* m_fontRender;
	Game* m_game;
	float m_time;

};

