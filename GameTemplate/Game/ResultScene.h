#pragma once
class ResultLevel2D;
class Game;

class ResultScene : public IGameObject
{
public:
	~ResultScene();
	bool Start();
	void Update();
private:
	float nowTime = 0.0f;
	float bestTime = 0.0f;
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
	FontRender* m_fontRender = nullptr;
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
	Game* m_game = nullptr;
};