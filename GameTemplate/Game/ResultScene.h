#pragma once
class ResultLevel2D;
class Game;
class SaveData;

class ResultScene : public IGameObject
{
private:
	~ResultScene();
	bool Start();
	void Update();

public:
	SaveData* NewrecordFlg = nullptr;


	float m_result;
	bool finishFlg = false;
	float GetTime()		//Gameからとってくる
	{
		return m_time;
	}

	void SetStageNum(int num) {
		m_stageNum = num;
	}

	int GetStageNum() {
		return m_stageNum;
	}
	
private:
	//ボタンを選択するための列挙型
	enum Select {
		TitleBackButton,
		EndButton,
	};
	bool m_scaleUpFlag = true;
	bool m_newRecordFlg = false;
	int m_nowSelect = 0;	//列挙の値を格納する変数。はじめは「はじめる」ボタンの0。
	int m_stageNum = 0;
	float m_time = 0.0f;
	float m_nowTime = 0.0f;
	float m_bestTime = 0.0f;
	float m_fontScale = 0.25f;
	float m_fontScale2 = 0.2f;
	float m_recordPos = 1100.0f;
	Vector3 m_scale = { 0.0f,0.0f,0.0f };
	Vector3 m_scale2 = { 0.25f,0.25f,0.25f };
	Vector3 m_scale3 = { 0.2f,0.2f,0.2f };

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	Game* m_game;
	ResultLevel2D* m_resultLevel2D = nullptr;
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
	FontRender* m_fontNowTime = nullptr;
	FontRender* m_fontBestTime = nullptr;
	FontRender* m_fontRender = nullptr;		//今回のタイムを表示するためのフォントレンダー
};