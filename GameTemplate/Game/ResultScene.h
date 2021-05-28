#pragma once
class ResultLevel2D;
class Game;
class SaveData;

class ResultScene : public IGameObject
{
public:
	~ResultScene();
	bool Start();
	void Update();
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
	FontRender* m_fontRender;		//今回のタイムを表示するためのフォントレンダー
	Game* m_game;
	float m_time;
	



private:
	int m_stageNum = 0;
	float nowTime = 0.0f;
	float bestTime = 0.0f;
	FontRender* m_nowTime = nullptr;
	FontRender* m_BestTime = nullptr;
	ResultLevel2D* sprite = nullptr;

	//移動効果音のサウンドソース
	CSoundSource* CursorMooveSound = nullptr;
	//決定効果音のサウンドソース
	CSoundSource* DecisionSound = nullptr;

	//ボタンを選択するための列挙型
	enum Select {
		TitleBackButton,
		EndButton,
	};
	int NowSelect = 0;	//列挙の値を格納する変数。はじめは「はじめる」ボタンの0。

	ResultLevel2D* m_resultLevel2D = nullptr;

	//画像の大きさを決める変数
	Vector3 Vscale = { 0.0f,0.0f,0.0f };
	float Fscale = 0.25f;
	float Fscale1 = 0.2f;
	bool ScaleUpFlag = true;

	//ボタンの初期の大きさ。
	Vector3 vscale = { 0.25f,0.25f,0.25f };
	Vector3 vscale1 = { 0.2f,0.2f,0.2f };

	//trueの時、新記録！表示。
	bool NewRecordFlg = false;
	//NewGOされるのを1回にするためのフラグ
	bool NewRecordFlgSub = true;
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
	float RecordPos = 1100.0f;
};