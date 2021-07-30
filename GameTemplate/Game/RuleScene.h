#pragma once
class RuleLevel2D;


class RuleScene : public IGameObject
{
private:
	bool Start();
	~RuleScene();
	void Update();
private:
	//選択ボタンのリスト
	enum ButtonSelect {
		back,
		next
	};

	//ページ番号
	enum PageSelect {
		OnePage,
		TwoPage,
		ThreePage,
		FourPage,

		Page_Num
	};

	enum Page1Sprite {
		Page1Sprite_Key,
		Page1Sprite_RedBall,
		Page1Sprite_Start,
		Page1Sprite_Get,
		Page1Sprite_Goal,
	};

	enum Page2Sprite {
		Page2Sprite_Arrow,
		Page2Sprite_Red_Ball,
		Page2Sprite_Blue_Ball,
		Page2Sprite_Magnet01,
		Page2Sprite_Magnet02,
		Page2Sprite_Inryoku,

		Page2Sprite_Num
	};
	bool m_scaleUpFlg = true;						//ボタンが拡大していくフラグ
	bool m_nextPageFlg = true;						//次のページにいくフラグ
	int m_pageNum = 0;								//選択中のページ番号
	int m_nowSelect = 0;							//列挙の値を格納する変数。はじめは「つぎ」ボタンの1。
	int m_onePageTimer = 0;							//1ページ目の管理時間
	int m_twoPageTimer = 0;							//2ページ目の管理時間
	int m_threePageTimer = 0;						//3ページ目の管理時間
	int m_fourPageTimer = 0;						//4ページ目の管理時間
	float m_scale = 0.2f;							
	float m_onePageBallPos = -300.0f;
	float m_twoPageBallPos = -300.0f;
	float m_threePageBallPos = 125.0f;
	float m_fourPageBallPos = -250.0f;
	Vector3 m_scale2 = { 0.2f,0.2f,0.2f };
	Vector3 m_scale3 = { 0.2f,0.2f,0.2f };
	Vector3 m_keyPos = { 300.0f,-30.0f,0.0f };

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	SpriteRender* m_page1SpriteRender[5] = { nullptr };		//鍵スプライトレンダー
	SpriteRender* m_inryokuSpriteRender[Page2Sprite_Num] = { nullptr };		//引力スプライトレンダー
	SpriteRender* m_sekiryokuSpriteRender[6] = { nullptr };		//斥力スプライトレンダー
	SpriteRender* m_deathSpriteRender[6] = { nullptr };		//デススプライトレンダー
	SpriteRender* m_quarterSpriteRender[Page_Num] = { nullptr };		//クオータースプライトレンダー
	RuleLevel2D* m_level2D = nullptr;
};