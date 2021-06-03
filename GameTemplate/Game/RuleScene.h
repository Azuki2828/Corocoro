#pragma once
class RuleLevel2D;

class RuleScene : public IGameObject
{
public:
	bool Start();
	~RuleScene();
	void Update();

	RuleLevel2D* sprite = nullptr;

private:
	//BGMのサウンドソース
	CSoundSource* BGMSound = nullptr;
	//移動効果音のサウンドソース
	CSoundSource* CursorMooveSound = nullptr;
	//決定効果音のサウンドソース
	CSoundSource* DecisionSound = nullptr;

	RuleLevel2D* m_RuleLevel2D = nullptr;

	int NowSelect = 1;	//列挙の値を格納する変数。はじめは「つぎ」ボタンの1。

	enum ButtonSelect {
		back,
		next
	};

	enum PageSelect {
		ZeroPage,
		OnePage,
		TwoPage,
		ThreePage,
		FourPage,
		FivePage
	};
	//画像の大きさを決める変数
	Vector3 Vscale = { 0.2f,0.2f,0.2f };
	float Fscale = 0.2f;
	bool ScaleUpFlag = true;

	//ボタンの初期の大きさ。
	Vector3 vscale = { 0.2f,0.2f,0.2f };

	//今何ページ目のあそびかたを読んでいるのか。
	int PageNum = 1;

	bool NextPageFlg = true;
	
	SpriteRender* m_KeySpriteRender[5] = { nullptr };		//鍵スプライトレンダー
	SpriteRender* m_InryokuSpriteRender[5] = { nullptr };		//引力スプライトレンダー
	SpriteRender* m_SekiryokuSpriteRender[6] = { nullptr };		//斥力スプライトレンダー
	SpriteRender* m_DeathSpriteRender[6] = { nullptr };		//デススプライトレンダー
	SpriteRender* m_QuarterSpriteRender[4] = { nullptr };		//クオータースプライトレンダー

	int OnePageTimer = 0;
	float OnePageBallPos = -300.0f;
	Vector3 KeyPos = { 300.0f,-30.0f,0.0f };

	int TwoPageTimer = 0;
	float TwoPageBallPos = -300.0f;

	int ThreePageTimer = 0;
	float ThreePageBallPos = 125.0f;

	int FourPageTimer = 0;
	float FourPageBallPos = -250.0f;
};