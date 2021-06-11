#pragma once
class StageSelectLevel2D;
class Game;

class StageSelect : public IGameObject
{
private:
	bool Start();
	~StageSelect();
	void Update();
private:
		//ボタンを選択するための列挙型
	enum Select {
		BackButton,
		KetteiButton,
	};

	enum StageNumber
	{
		StageOne,
		StageTwo,
		StageThree,
		StageFour,
		FinalStage		//FinalStageにマイナス1することでステージの総数を求める。
	};
	bool ScaleUpFlag = true;
	int NowSelectStage = 0;
	int NowSelect = 1;	//列挙の値を格納する変数。はじめは「けってい」ボタンの1。
	float Fscale = 0.23f;
	float Fscale1 = 0.18f;
	Vector3 Vscale = { 0.0f,0.0f,0.0f };
	Vector3 vscale = { 0.23f,0.23f,0.23f };
	Vector3 vscale1 = { 0.18f,0.18f,0.18f };


	/**
	 * @brief それぞれのクラスのポインタ
	*/

	StageSelectLevel2D* m_sprite = nullptr;
	SpriteRender* m_stageSpriteRender[4][2] = { nullptr };		//ステージ文字スプライトレンダー
	Game* m_game = nullptr;
};