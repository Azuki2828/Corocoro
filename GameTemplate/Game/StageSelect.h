#pragma once
class StageSelectLevel2D;
class Game;

class StageSelect:public IGameObject
{
public:
	bool Start();
	~StageSelect();
	void Update();
private:
	StageSelectLevel2D* sprite = nullptr;

	//移動効果音のサウンドソース
	CSoundSource* CursorMooveSound = nullptr;
	//決定効果音のサウンドソース
	CSoundSource* DecisionSound = nullptr;
	//BGMのサウンドソース
	CSoundSource* BGMSound = nullptr;

	int NowSelect = 1;	//列挙の値を格納する変数。はじめは「けってい」ボタンの1。
		//ボタンを選択するための列挙型
	enum Select {
		BackButton,
		KetteiButton,
	};

		//画像の大きさを決める変数
	Vector3 Vscale = { 0.0f,0.0f,0.0f };
	float Fscale = 0.23f;
	float Fscale1 = 0.18f;
	bool ScaleUpFlag = true;

	//ボタンの初期の大きさ。
	Vector3 vscale = { 0.23f,0.23f,0.23f };
	Vector3 vscale1 = { 0.18f,0.18f,0.18f };

	//現在選択されているステージ番号
	int NowSelectStage = 1;

	enum StageNumber
	{
		Stagenull,		//StageOneが1になるように合わせるため用意されたStagenull(使わない)
		StageOne,
		StageTwo,
		StageThree,
		FinalStage		//FinalStageにマイナス1することでステージの総数を求める。
	};

	SpriteRender* m_StageSpriteRender[3][2] = { nullptr };		//ステージ文字スプライトレンダー
	Game* m_game = nullptr;
};