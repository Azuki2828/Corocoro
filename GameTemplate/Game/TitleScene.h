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
	bool ScaleUpFlag = true;
	float Fscale = 0.2f;
	int NowSelect = 0;
	Vector3 Vscale = { 0.2f,0.2f,0.2f };
	Vector3 vscale = { 0.2f,0.2f,0.2f };

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	TitleLevel2D* m_titleLevel2D = nullptr;
};