#pragma once

class Game;
class SaveData;

class Result : public IGameObject
{
public:

	float m_result;
	bool Start();
	bool finishFlg = false;

};

