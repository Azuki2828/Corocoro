#pragma once

class Game;
class SaveData;

class Result : public IGameObject
{
public:

	float m_result;
	bool Start();
	bool finishFlg = false;
	float GetTime()		//Game����Ƃ��Ă���
	{
		return m_time;
	}
	FontRender* m_fontRender;		//����̃^�C����\�����邽�߂̃t�H���g�����_�[
	Game* m_game;
	float m_time;

};

