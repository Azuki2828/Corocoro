#pragma once

class Game;
class SaveData;

class Result : public IGameObject
{
public:

	float m_result;
	bool Start();
	bool finishFlg = false;
	float GetTime()		//Gameからとってくる
	{
		return m_time;
	}
	FontRender* m_fontRender;		//今回のタイムを表示するためのフォントレンダー
	Game* m_game;
	float m_time;

};

