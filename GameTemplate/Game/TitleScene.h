#pragma once
class TitleLevel2D;

class TitleScene : public IGameObject
{
public:
	//TitleScene();		Start関数の方を使う。
	~TitleScene();
	bool Start();
	void Update();
private:
	TitleLevel2D* sprite = nullptr;

	//タイトルBGMのサウンドソース
	CSoundSource* TitleBGMSound = nullptr;
	//移動効果音のサウンドソース
	CSoundSource* CursorMooveSound = nullptr;
	//決定効果音のサウンドソース
	CSoundSource* DecisionSound = nullptr;


	//ボタンを選択するための列挙型
	enum Select {
		StartButton,
		RuleButton,
		SettingButton,
		EndButton,
	};
	int NowSelect = 0;	//列挙の値を格納する変数。はじめは「はじめる」ボタンの0。

	TitleLevel2D* m_titleLevel2D = nullptr;


};