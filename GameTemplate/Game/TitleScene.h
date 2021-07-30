#pragma once
class TitleLevel2D;

class TitleScene : public IGameObject
{
private:
	~TitleScene();
	bool Start() override;
	void Update() override;
private:
	//ボタンを選択するための列挙型
	enum Select {
		StartButton,
		RuleButton,
		EndButton,
	};
	bool m_scaleUpFlag = true;		//拡大縮小するフラグ
	float m_ButtonScale = 0.0f;		//ボタンの拡大率
	int m_nowSelect = 0;			//選択項目

	//それぞれのクラスのポインタ

	TitleLevel2D* m_titleLevel2D = nullptr;
};