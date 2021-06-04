#include "stdafx.h"
#include "Game.h"
#include "RuleScene.h"
#include "RuleLevel2D.h"
#include "TitleScene.h"

namespace{
	const int NUM_HOGE = 10;
	const float MOVE_SPEED = 100;
	const int BAR = 10;
}
bool RuleScene::Start()
{
	//ルール画面表示
	m_sprite = NewGO<RuleLevel2D>(0,"RuleLevel2D");

	//BGM再生
	SoundManager::GetInstance()->Play(BGM_Title);

	//はじめだけStart関数でNewGOする
	//鍵
	m_keySpriteRender[0] = NewGO<SpriteRender>(2);
	m_keySpriteRender[0]->SetPosition({ 300.0f,-30.0f,0.0f });
	m_keySpriteRender[0]->Init("Assets/Level2D/KeyGet.dds", 150.0f, 150.0f);
	//赤ボール
	m_keySpriteRender[1] = NewGO<SpriteRender>(2);
	m_keySpriteRender[1]->SetPosition({ -300.0f,-30.0f,0.0f });
	m_keySpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
	//Start!
	m_keySpriteRender[2] = NewGO<SpriteRender>(1);
	m_keySpriteRender[2]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_keySpriteRender[2]->Init("Assets/image/Start!!.dds", 350.0f, 350.0f);
	m_keySpriteRender[2]->SetScale({1.3f,1.3f,1.3f});
	//Get
	m_keySpriteRender[3] = NewGO<SpriteRender>(1);
	m_keySpriteRender[3]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_keySpriteRender[3]->Init("Assets/image/Get.dds", 350.0f, 350.0f);
	m_keySpriteRender[3]->SetScale({ 1.3f,1.3f,1.3f });
	m_keySpriteRender[3]->Deactivate();		//非表示
	//Goal
	m_keySpriteRender[4] = NewGO<SpriteRender>(1);
	m_keySpriteRender[4]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_keySpriteRender[4]->Init("Assets/image/Goal.dds", 350.0f, 350.0f);
	m_keySpriteRender[4]->SetScale({ 1.3f,1.3f,1.3f });
	m_keySpriteRender[4]->Deactivate();		//非表示
	//1/4
	m_quarterSpriteRender[0] = NewGO<SpriteRender>(2);
	m_quarterSpriteRender[0]->SetPosition({ 0.0f,-280.0f,0.0f });
	m_quarterSpriteRender[0]->Init("Assets/image/OneQuarter.dds", 500.0f, 500.0f);

	//スタート関数のreturn true;
	return true;
}

RuleScene::~RuleScene()
{
	//ルール画面のレベルを削除。
	DeleteGO(m_sprite);

	for (int i = 0; i < 6; i++)
	{
		DeleteGO(m_deathSpriteRender[i]);
		m_deathSpriteRender[i] = nullptr;
	}
	DeleteGO(m_quarterSpriteRender[3]);
	for (int i = 0; i < 5; i++)
	{
		DeleteGO(m_keySpriteRender[i]);
		m_keySpriteRender[i] = nullptr;
	}
	DeleteGO(m_quarterSpriteRender[0]);
	m_quarterSpriteRender[0] = nullptr;

	//タイトルBGMを削除。
	SoundManager::GetInstance()->Release(BGM_Title);
}

void RuleScene::Update()
{
	//ボタンを全て半透明にする。
	for (int i = 1; i < 3; i++) {
		m_sprite->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

	//右入力or左入力されたら、
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「もどる」(0番)だったら、
		if (m_nowSelect == 0) {
			//選択を右に1つずらす。
			m_nowSelect += 1;
		}
		//現在セレクトされているボタンが「つぎ」(1番)だったら、
		else {
			//選択を左に1つずらす。
			m_nowSelect -= 1;
		}
		//移動効果音鳴らす。
		SoundManager::GetInstance()->Play(SE_CursolMove);
	}

	//現在選択しているボタンの強調表示
	switch (m_nowSelect) {

		//「はじめる」ボタンが選ばれているとき、
	 case back:
		//ボタンを不透明度100％にする。
		 m_sprite->GetSprite(1)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (m_scale < 0.20f) {
			m_scaleUpFlg = true;
		}
		//大きさが最大になったとき、
		if (m_scale > 0.225f) {
			m_scaleUpFlg = false;
		}

		if (m_scaleUpFlg == true) {
			//拡大
			m_scale += 0.0005f;
		}
		if (m_scaleUpFlg == false) {
			//縮小
			m_scale -= 0.0005f;
		}
		//スプライトに反映。
		m_scale2 = { m_scale,m_scale,m_scale };
		m_sprite->GetSprite(1)->SetScale(m_scale2);

		//選択されていないボタンの拡大率を元に戻す。
		m_sprite->GetSprite(2)->SetScale(m_scale3);

		break;

		//「あそびかた」ボタンが選ばれているとき、
	 case next:
		//ボタンを不透明度100％にする。
		 m_sprite->GetSprite(2)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		//大きさが最小になったとき、
		if (m_scale < 0.20f) {
			m_scaleUpFlg = true;
		}
		//大きさが最大になったとき、
		if (m_scale > 0.225f) {
			m_scaleUpFlg = false;
		}

		if (m_scaleUpFlg == true) {
			//拡大
			m_scale += 0.0005f;
		}
		if (m_scaleUpFlg == false) {
			//縮小
			m_scale -= 0.0005f;
		}
		//スプライトに反映。
		m_scale2 = { m_scale,m_scale,m_scale };
		m_sprite->GetSprite(2)->SetScale(m_scale2);

		//選択されていないボタンの拡大率を元に戻す。
		m_sprite->GetSprite(1)->SetScale(m_scale3);

		break;
	};

	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。
		SoundManager::GetInstance()->Play(SE_DecisionButton);

		switch (m_nowSelect) {

			//「もどる」ボタンが選ばれたとき、
		 case back:
			 //ページを前に戻す。
			 m_pageNum--;

			m_nextPageFlg = false;

			break;

			//「つぎ」ボタンが選ばれたとき、
		 case next:
			 //ページを次に進める。
			 m_pageNum++;

			m_nextPageFlg = true;

			break;
		};

		switch (m_pageNum)
		{
			//1ページ目
		case OnePage:
			m_keySpriteRender[0] = NewGO<SpriteRender>(2);
			m_keySpriteRender[0]->SetPosition({ 300.0f,-30.0f,0.0f });
			m_keySpriteRender[0]->Init("Assets/Level2D/KeyGet.dds", 150.0f, 150.0f);

			m_keySpriteRender[1] = NewGO<SpriteRender>(2);
			m_keySpriteRender[1]->SetPosition({ -300.0f,-100.0f,0.0f });
			m_keySpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);

			m_keySpriteRender[2] = NewGO<SpriteRender>(1);
			m_keySpriteRender[2]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_keySpriteRender[2]->Init("Assets/image/Start!!.dds", 350.0f, 350.0f);
			m_keySpriteRender[2]->SetScale({ 1.3f,1.3f,1.3f });
			m_keySpriteRender[2]->Deactivate();		//非表示

			m_keySpriteRender[3] = NewGO<SpriteRender>(1);
			m_keySpriteRender[3]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_keySpriteRender[3]->Init("Assets/image/Get.dds", 350.0f, 350.0f);
			m_keySpriteRender[3]->SetScale({ 1.3f,1.3f,1.3f });
			m_keySpriteRender[3]->Deactivate();		//非表示

			m_keySpriteRender[4] = NewGO<SpriteRender>(1);
			m_keySpriteRender[4]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_keySpriteRender[4]->Init("Assets/image/Goal.dds", 350.0f, 350.0f);
			m_keySpriteRender[4]->SetScale({ 1.3f,1.3f,1.3f });
			m_keySpriteRender[4]->Deactivate();		//非表示
			m_quarterSpriteRender[0] = NewGO<SpriteRender>(2);
			m_quarterSpriteRender[0]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_quarterSpriteRender[0]->Init("Assets/image/OneQuarter.dds", 500.0f, 500.0f);
			
			for (int i = 0; i < 6; i++)
			{
				DeleteGO(m_inryokuSpriteRender[i]);		//矢印引力スプライト削除
				m_inryokuSpriteRender[i] = nullptr;
			}
			DeleteGO(m_quarterSpriteRender[1]);		//2/4スプライト削除
			m_quarterSpriteRender[1] = nullptr;

			break;

			//2ページ目
		case TwoPage:

			//右矢印表示
			m_inryokuSpriteRender[0] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[0]->SetPosition({ 100.0f,-30.0f,0.0f });
			m_inryokuSpriteRender[0]->Init("Assets/image/Yazirusi01.dds", 800.0f, 400.0f);
			m_inryokuSpriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });		//半透明にする
			//赤ボール表示
			m_inryokuSpriteRender[1] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[1]->SetPosition({ -300.0f,50.0f,0.0f });
			m_inryokuSpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//青ボール表示
			m_inryokuSpriteRender[2] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[2]->SetPosition({ -300.0f,-100.0f,0.0f });
			m_inryokuSpriteRender[2]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//マグネット(上)表示
			m_inryokuSpriteRender[3] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[3]->SetPosition({ 300.0f,50.0f,0.0f });
			m_inryokuSpriteRender[3]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_inryokuSpriteRender[3]->SetScale({ -1.2,-1.2,1.2 });		//少し大きくする(+反転)
			//マグネット(下)表示
			m_inryokuSpriteRender[4] = NewGO<SpriteRender>(2);
			m_inryokuSpriteRender[4]->SetPosition({ 300.0f,-100.0f,0.0f });
			m_inryokuSpriteRender[4]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_inryokuSpriteRender[4]->SetScale({ 1.2,1.2,1.2 });		//少し大きくする
			//引力文字表示
			m_inryokuSpriteRender[5] = NewGO<SpriteRender>(1);
			m_inryokuSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_inryokuSpriteRender[5]->Init("Assets/image/Inryoku.dds", 350.0f, 350.0f);
			m_inryokuSpriteRender[5]->SetScale({ 1.3,1.3,1.3 });		//少し大きくする
			//2/4表示
			m_quarterSpriteRender[1] = NewGO<SpriteRender>(2);
			m_quarterSpriteRender[1]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_quarterSpriteRender[1]->Init("Assets/image/TwoQuarters.dds", 500.0f, 500.0f);

			//1ページ目
			if (m_nextPageFlg)
			{
				for (int i = 0; i < 5; i++)
				{
					DeleteGO(m_keySpriteRender[i]);		//鍵と赤ボールスプライト削除
					m_keySpriteRender[i] = nullptr;
				}
				DeleteGO(m_quarterSpriteRender[0]);		//1/4スプライト削除
				m_quarterSpriteRender[0] = nullptr;
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_sekiryokuSpriteRender[i]);		//矢印斥力スプライト削除
					m_sekiryokuSpriteRender[i] = nullptr;
				}
				DeleteGO(m_quarterSpriteRender[2]);		//3/4スプライト削除
				m_quarterSpriteRender[2] = nullptr;
			}

			break;

			//3ページ目
		case ThreePage:

			//左矢印表示
			m_sekiryokuSpriteRender[0] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[0]->SetPosition({ 100.0f,-30.0f,0.0f });
			m_sekiryokuSpriteRender[0]->Init("Assets/image/Yazirusi02.dds", 800.0f, 400.0f);
			m_sekiryokuSpriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });		//半透明にする
			//赤ボール表示
			m_sekiryokuSpriteRender[1] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[1]->SetPosition({ 125.0f,50.0f,0.0f });
			m_sekiryokuSpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//青ボール表示
			m_sekiryokuSpriteRender[2] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[2]->SetPosition({ 125.0f,-100.0f,0.0f });
			m_sekiryokuSpriteRender[2]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//マグネット(上)表示
			m_sekiryokuSpriteRender[3] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[3]->SetPosition({ 300.0f,50.0f,0.0f });
			m_sekiryokuSpriteRender[3]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_sekiryokuSpriteRender[3]->SetScale({ 1.2,1.2,1.2 });
			//マグネット(下)表示
			m_sekiryokuSpriteRender[4] = NewGO<SpriteRender>(2);
			m_sekiryokuSpriteRender[4]->SetPosition({ 300.0f,-100.0f,0.0f });
			m_sekiryokuSpriteRender[4]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);		//少し大きくする
			m_sekiryokuSpriteRender[4]->SetScale({ -1.2,-1.2,1.2 });		//少し大きくする(+反転)
			//斥力文字表示
			m_sekiryokuSpriteRender[5] = NewGO<SpriteRender>(1);
			m_sekiryokuSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_sekiryokuSpriteRender[5]->Init("Assets/image/Sekiryoku.dds", 350.0f, 350.0f);
			m_sekiryokuSpriteRender[5]->SetScale({ 1.3,1.3,1.3 });		//少し大きくする
			//3/4表示
			m_quarterSpriteRender[2] = NewGO<SpriteRender>(2);
			m_quarterSpriteRender[2]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_quarterSpriteRender[2]->Init("Assets/image/ThreeQuarters.dds", 500.0f, 500.0f);
			if (m_nextPageFlg)
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_inryokuSpriteRender[i]);		//矢印引力スプライト削除
					m_inryokuSpriteRender[i] = nullptr;
				}
				DeleteGO(m_quarterSpriteRender[1]);		//2/4スプライト削除
				m_quarterSpriteRender[1] = nullptr;
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_deathSpriteRender[i]);		//死ぬ床スプライト削除
					m_deathSpriteRender[i] = nullptr;
				}
				DeleteGO(m_quarterSpriteRender[3]);		//4/4スプライト削除
				m_quarterSpriteRender[3] = nullptr;
			}

			break;

			//4ページ目
		case FourPage:
			//赤ボール画像表示
			m_deathSpriteRender[0] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[0]->SetPosition({ -250.0f,50.0f,0.0f });
			m_deathSpriteRender[0]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//青ボール画像表示
			m_deathSpriteRender[1] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[1]->SetPosition({ -250.0f,-100.0f,0.0f });
			m_deathSpriteRender[1]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//死ぬ床画像表示
			m_deathSpriteRender[2] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[2]->SetPosition({ 300.0f,-30.0f,0.0f });
			m_deathSpriteRender[2]->SetScale({ 1.2f,1.2f,1.2f });		//少し小さかったから大きさ調整
			m_deathSpriteRender[2]->Init("Assets/image/DeathFloor.dds", 350.0f, 350.0f);
			//バツ(1)画像表示
			m_deathSpriteRender[3] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[3]->SetPosition({ 230.0f,50.0f,0.0f });
			m_deathSpriteRender[3]->SetScale({ 0.5f,0.5f,0.5f });		//少し小さかったから大きさ調整
			m_deathSpriteRender[3]->Init("Assets/image/Batu.dds", 350.0f, 350.0f);
			m_deathSpriteRender[3]->Deactivate();		//非表示
			//バツ(2)画像表示
			m_deathSpriteRender[4] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[4]->SetPosition({ 230.0f,-100.0f,0.0f });
			m_deathSpriteRender[4]->SetScale({ 0.5f,0.5f,0.5f });		//少し小さかったから大きさ調整
			m_deathSpriteRender[4]->Init("Assets/image/Batu.dds", 350.0f, 350.0f);
			m_deathSpriteRender[4]->Deactivate();		//非表示
			//Dame画像表示
			m_deathSpriteRender[5] = NewGO<SpriteRender>(1);
			m_deathSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_deathSpriteRender[5]->SetScale({ 1.5f,1.5f,1.5f });		//少し小さかったから大きさ調整
			m_deathSpriteRender[5]->Init("Assets/image/Dame.dds", 350.0f, 350.0f);
			m_deathSpriteRender[5]->Deactivate();		//非表示
			//4/4表示
			m_quarterSpriteRender[3] = NewGO<SpriteRender>(2);
			m_quarterSpriteRender[3]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_quarterSpriteRender[3]->Init("Assets/image/FourQuarters.dds", 500.0f, 500.0f);

			for (int i = 0; i < 6; i++)
			{
				DeleteGO(m_sekiryokuSpriteRender[i]);		//矢印斥力スプライト削除
				m_sekiryokuSpriteRender[i] = nullptr;
			}
			DeleteGO(m_quarterSpriteRender[2]);		//3/4スプライト削除
			m_quarterSpriteRender[2] = nullptr;

			break;
		}
	}

	//常に呼ばれる
	switch (m_pageNum)
	{
	 //タイトルに戻る。
	 case ZeroPage:

		//クラスの破棄
		DeleteGO(this);

		//タイトル画面からスタート
		NewGO<TitleScene>(0);

		break;

	 case OnePage:
		 m_onePageTimer++;
		 if (m_onePageTimer < 110)
		 {
			 m_keySpriteRender[2]->Activate();		//表示
			 //ボールの位置を右にずらしていく。
			 m_onePageBallPos += 5;
		 }
		 //鍵の場所まで行ったら、
		 else if(110<= m_onePageTimer && m_onePageTimer <=200)
		 {
			 m_keySpriteRender[2]->Deactivate();		//非表示
			 m_keySpriteRender[3]->Activate();		//表示

			 m_keyPos.y += 1.0f;
			 m_keySpriteRender[0]->SetPosition({ m_keyPos });		//鍵の位置更新
		 }
		 else if (200 < m_onePageTimer && m_onePageTimer < 310)
		 {
			 m_keySpriteRender[3]->Activate();		//表示

			 //ボールの位置を左にずらしていく。
			 m_onePageBallPos -= 5;
			 m_keySpriteRender[0]->SetPosition({ m_onePageBallPos,m_keyPos.y,m_keyPos.z });		//鍵の位置更新
		 }
		 else if (310 <= m_onePageTimer && m_onePageTimer <=400)
		 {
			 m_keySpriteRender[3]->Deactivate();		//非表示
			 m_keySpriteRender[4]->Activate();		//表示
		 }
		 else
		 {
			 m_keySpriteRender[4]->Deactivate();		//表示
			 m_keySpriteRender[2]->Activate();		//表示
			 //鍵の持ち上げ分のy座標を戻す。(初期化)
			 m_keyPos = { 300.0f,-30.0f,0.0f };
			 m_keySpriteRender[0]->SetPosition({ m_keyPos });		//鍵の位置更新
			 //タイマーを初期化して初めのif文に戻る
			 m_onePageTimer = 0;
		 }

		 m_keySpriteRender[1]->SetPosition({ m_onePageBallPos,-30.0f,0.0f });		//赤ボールの位置更新

		 break;

	 case TwoPage:

		 m_twoPageTimer++;
		 if (m_twoPageTimer < 108)
		 {
			 //ボールの位置を右にずらしていく。
			 m_twoPageBallPos += 4;
		 }
		 else if(108<= m_twoPageTimer && m_twoPageTimer <= 200)
		 {
			 //なにもしない
		 }
		 else
		 {
			 m_twoPageBallPos = -300.0f;//ボールをはじめの位置に持っていく。
			 //タイマーを初期化して初めのif文に戻る
			 m_twoPageTimer = 0;
		 }

		 m_inryokuSpriteRender[1]->SetPosition({ m_twoPageBallPos,50.0f,0.0f });		//赤ボールの位置更新
		 m_inryokuSpriteRender[2]->SetPosition({ m_twoPageBallPos,-100.0f,0.0f });		//青ボールの位置更新

		break;

	 case ThreePage:

		 m_threePageTimer++;
		 if (m_threePageTimer < 108)
		 {
			 //ボールの位置を右にずらしていく。
			 m_threePageBallPos -= 4;
		 }
		 else if (108 <= m_threePageTimer && m_threePageTimer <= 200)
		 {
			 //なにもしない
		 }
		 else
		 {
			 m_threePageBallPos =  125.0f;//ボールをはじめの位置に持っていく。
			 //タイマーを初期化して初めのif文に戻る
			 m_threePageTimer = 0;
		 }

		 m_sekiryokuSpriteRender[1]->SetPosition({ m_threePageBallPos,50.0f,0.0f });		//赤ボールの位置更新
		 m_sekiryokuSpriteRender[2]->SetPosition({ m_threePageBallPos,-100.0f,0.0f });		//赤ボールの位置更新

		break;

	 case FourPage:
		 m_fourPageTimer++;
		 if (m_fourPageTimer < 85)
		 {
			 //ボールの位置を右にずらしていく。
			 m_fourPageBallPos += 5;
		 }
		 else
		 {
			 m_deathSpriteRender[3]->Activate();		//表示
			 m_deathSpriteRender[4]->Activate();		//表示
			 m_deathSpriteRender[5]->Activate();		//表示

			 if (m_fourPageTimer > 200)
			 {
				 m_fourPageBallPos = -250.0f;		//ボールをはじめの位置に持っていく。
				 m_fourPageTimer = 0;		//タイマー初期化して上のifに戻る。
				 m_deathSpriteRender[3]->Deactivate();		//非表示
				 m_deathSpriteRender[4]->Deactivate();		//非表示
				 m_deathSpriteRender[5]->Deactivate();		//非表示
			 }
		 }
		 m_deathSpriteRender[0]->SetPosition({ m_fourPageBallPos,50.0f,0.0f });		//赤ボールの位置更新
		 m_deathSpriteRender[1]->SetPosition({ m_fourPageBallPos,-100.0f,0.0f });		//青ボールの位置更新
			break;

	 //タイトルに戻る。
	 case FivePage:

		 DeleteGO(this);

		 //タイトル画面からスタート
		 NewGO<TitleScene>(0);

		 break;
	}
}