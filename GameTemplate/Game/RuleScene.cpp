#include "stdafx.h"
#include "RuleScene.h"
#include "RuleLevel2D.h"
#include "TitleScene.h"


bool RuleScene::Start()
{
	//ルール画面表示
	sprite = NewGO<RuleLevel2D>(0,"RuleLevel2D");
	m_RuleLevel2D = FindGO<RuleLevel2D>("RuleLevel2D");

	//BGM再生
	BGMSound = NewGO<CSoundSource>(0);
	BGMSound->Init(L"Assets/sound/TitleBGM.wav");
	BGMSound->SetVolume(1.0f);
	BGMSound->Play(true);		//ループ再生。

	//はじめだけStart関数でNewGOする
	//鍵
	m_KeySpriteRender[0] = NewGO<SpriteRender>(2);
	m_KeySpriteRender[0]->SetPosition({ 300.0f,-30.0f,0.0f });
	m_KeySpriteRender[0]->Init("Assets/Level2D/KeyGet.dds", 150.0f, 150.0f);
	//赤ボール
	m_KeySpriteRender[1] = NewGO<SpriteRender>(2);
	m_KeySpriteRender[1]->SetPosition({ -300.0f,-30.0f,0.0f });
	m_KeySpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
	//Start!
	m_KeySpriteRender[2] = NewGO<SpriteRender>(1);
	m_KeySpriteRender[2]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_KeySpriteRender[2]->Init("Assets/image/Start!!.dds", 350.0f, 350.0f);
	m_KeySpriteRender[2]->SetScale({1.3f,1.3f,1.3f});
	//Get
	m_KeySpriteRender[3] = NewGO<SpriteRender>(1);
	m_KeySpriteRender[3]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_KeySpriteRender[3]->Init("Assets/image/Get.dds", 350.0f, 350.0f);
	m_KeySpriteRender[3]->SetScale({ 1.3f,1.3f,1.3f });
	m_KeySpriteRender[3]->Deactivate();		//非表示
	//Goal
	m_KeySpriteRender[4] = NewGO<SpriteRender>(1);
	m_KeySpriteRender[4]->SetPosition({ 0.0f,-30.0f,0.0f });
	m_KeySpriteRender[4]->Init("Assets/image/Goal.dds", 350.0f, 350.0f);
	m_KeySpriteRender[4]->SetScale({ 1.3f,1.3f,1.3f });
	m_KeySpriteRender[4]->Deactivate();		//非表示
	//1/4
	m_QuarterSpriteRender[0] = NewGO<SpriteRender>(2);
	m_QuarterSpriteRender[0]->SetPosition({ 0.0f,-280.0f,0.0f });
	m_QuarterSpriteRender[0]->Init("Assets/image/OneQuarter.dds", 500.0f, 500.0f);

	//スタート関数のreturn true;
	return true;
}

RuleScene::~RuleScene()
{
	//ルール画面のレベルを削除。
	DeleteGO(sprite);

	for (int i = 0; i < 6; i++)
	{
		DeleteGO(m_DeathSpriteRender[i]);
	}
	DeleteGO(m_QuarterSpriteRender[3]);
	for (int i = 0; i < 5; i++)
	{
		DeleteGO(m_KeySpriteRender[i]);
	}
	DeleteGO(m_QuarterSpriteRender[0]);

	//タイトルBGMを削除。
	DeleteGO(BGMSound);
}

void RuleScene::Update()
{
	//ボタンを全て半透明にする。
	for (int i = 1; i < 3; i++) {
		m_RuleLevel2D->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

	//右入力or左入力されたら、
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「もどる」(0番)だったら、
		if (NowSelect  == 0) {
			//選択を右に1つずらす。
			NowSelect += 1;
		}
		//現在セレクトされているボタンが「つぎ」(1番)だったら、
		else {
			//選択を左に1つずらす。
			NowSelect -= 1;
		}
		//移動効果音鳴らす。
		CursorMooveSound = NewGO<CSoundSource>(0);
		CursorMooveSound->Init(L"Assets/sound/CursorMoove.wav");
		CursorMooveSound->SetVolume(1.0f);
		CursorMooveSound->Play(false);		//ワンショット再生。
	}

	//現在選択しているボタンの強調表示
	switch (NowSelect) {

		//「はじめる」ボタンが選ばれているとき、
	 case back:
		//ボタンを不透明度100％にする。
		m_RuleLevel2D->GetSprite(1)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (Fscale < 0.20f) {
			ScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (Fscale > 0.225f) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//拡大
			Fscale += 0.0005f;
		}
		if (ScaleUpFlag == false) {
			//縮小
			Fscale -= 0.0005f;
		}
		//スプライトに反映。
		Vscale = { Fscale,Fscale,Fscale };
		m_RuleLevel2D->GetSprite(1)->SetScale(Vscale);

		//選択されていないボタンの拡大率を元に戻す。
		m_RuleLevel2D->GetSprite(2)->SetScale(vscale);

		break;

		//「あそびかた」ボタンが選ばれているとき、
	 case next:
		//ボタンを不透明度100％にする。
		m_RuleLevel2D->GetSprite(2)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		//大きさが最小になったとき、
		if (Fscale < 0.20f) {
			ScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (Fscale > 0.225f) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//拡大
			Fscale += 0.0005f;
		}
		if (ScaleUpFlag == false) {
			//縮小
			Fscale -= 0.0005f;
		}
		//スプライトに反映。
		Vscale = { Fscale,Fscale,Fscale };
		m_RuleLevel2D->GetSprite(2)->SetScale(Vscale);

		//選択されていないボタンの拡大率を元に戻す。
		m_RuleLevel2D->GetSprite(1)->SetScale(vscale);

		break;
	};

	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {

		//決定ボタン音再生。
		DecisionSound = NewGO<CSoundSource>(0);
		DecisionSound->Init(L"Assets/sound/DecisionButton.wav");
		DecisionSound->SetVolume(1.0f);
		DecisionSound->Play(false);		//1ショット再生。

		switch (NowSelect) {

			//「もどる」ボタンが選ばれたとき、
		 case back:
			 //ページを前に戻す。
			PageNum--;

			NextPageFlg = false;

			break;

			//「つぎ」ボタンが選ばれたとき、
		 case next:
			 //ページを次に進める。
			PageNum++;

			NextPageFlg = true;

			break;
		};

		switch (PageNum)
		{
			//1ページ目
		case OnePage:
			//鍵表示
			m_KeySpriteRender[0] = NewGO<SpriteRender>(2);
			m_KeySpriteRender[0]->SetPosition({ 300.0f,-30.0f,0.0f });
			m_KeySpriteRender[0]->Init("Assets/Level2D/KeyGet.dds", 150.0f, 150.0f);
			//赤ボール
			m_KeySpriteRender[1] = NewGO<SpriteRender>(2);
			m_KeySpriteRender[1]->SetPosition({ -300.0f,-100.0f,0.0f });
			m_KeySpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//Start!
			m_KeySpriteRender[2] = NewGO<SpriteRender>(1);
			m_KeySpriteRender[2]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_KeySpriteRender[2]->Init("Assets/image/Start!!.dds", 350.0f, 350.0f);
			m_KeySpriteRender[2]->SetScale({ 1.3f,1.3f,1.3f });
			m_KeySpriteRender[2]->Deactivate();		//非表示
			//Get
			m_KeySpriteRender[3] = NewGO<SpriteRender>(1);
			m_KeySpriteRender[3]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_KeySpriteRender[3]->Init("Assets/image/Get.dds", 350.0f, 350.0f);
			m_KeySpriteRender[3]->SetScale({ 1.3f,1.3f,1.3f });
			m_KeySpriteRender[3]->Deactivate();		//非表示
			//Goal
			m_KeySpriteRender[4] = NewGO<SpriteRender>(1);
			m_KeySpriteRender[4]->SetPosition({ 0.0f,-30.0f,0.0f });
			m_KeySpriteRender[4]->Init("Assets/image/Goal.dds", 350.0f, 350.0f);
			m_KeySpriteRender[4]->SetScale({ 1.3f,1.3f,1.3f });
			m_KeySpriteRender[4]->Deactivate();		//非表示
			//1/4表示
			m_QuarterSpriteRender[0] = NewGO<SpriteRender>(2);
			m_QuarterSpriteRender[0]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_QuarterSpriteRender[0]->Init("Assets/image/OneQuarter.dds", 500.0f, 500.0f);
			for (int i = 0; i < 6; i++)
			{
				DeleteGO(m_InryokuSpriteRender[i]);		//矢印引力スプライト削除
			}
			DeleteGO(m_QuarterSpriteRender[1]);		//2/4スプライト削除

			break;

			//2ページ目
		case TwoPage:

			//右矢印表示
			m_InryokuSpriteRender[0] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[0]->SetPosition({ 100.0f,-30.0f,0.0f });
			m_InryokuSpriteRender[0]->Init("Assets/image/Yazirusi01.dds", 800.0f, 400.0f);
			m_InryokuSpriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });		//半透明にする
			//赤ボール表示
			m_InryokuSpriteRender[1] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[1]->SetPosition({ -300.0f,50.0f,0.0f });
			m_InryokuSpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//青ボール表示
			m_InryokuSpriteRender[2] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[2]->SetPosition({ -300.0f,-100.0f,0.0f });
			m_InryokuSpriteRender[2]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//マグネット(上)表示
			m_InryokuSpriteRender[3] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[3]->SetPosition({ 300.0f,50.0f,0.0f });
			m_InryokuSpriteRender[3]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_InryokuSpriteRender[3]->SetScale({ -1.2,-1.2,1.2 });		//少し大きくする(+反転)
			//マグネット(下)表示
			m_InryokuSpriteRender[4] = NewGO<SpriteRender>(2);
			m_InryokuSpriteRender[4]->SetPosition({ 300.0f,-100.0f,0.0f });
			m_InryokuSpriteRender[4]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_InryokuSpriteRender[4]->SetScale({ 1.2,1.2,1.2 });		//少し大きくする
			//引力文字表示
			m_InryokuSpriteRender[5] = NewGO<SpriteRender>(1);
			m_InryokuSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_InryokuSpriteRender[5]->Init("Assets/image/Inryoku.dds", 350.0f, 350.0f);
			m_InryokuSpriteRender[5]->SetScale({ 1.3,1.3,1.3 });		//少し大きくする
			//2/4表示
			m_QuarterSpriteRender[1] = NewGO<SpriteRender>(2);
			m_QuarterSpriteRender[1]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_QuarterSpriteRender[1]->Init("Assets/image/TwoQuarters.dds", 500.0f, 500.0f);

			//1ページ目
			if (NextPageFlg)
			{
				for (int i = 0; i < 5; i++)
				{
					DeleteGO(m_KeySpriteRender[i]);		//鍵と赤ボールスプライト削除
				}
				DeleteGO(m_QuarterSpriteRender[0]);		//1/4スプライト削除
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_SekiryokuSpriteRender[i]);		//矢印斥力スプライト削除
				}
				DeleteGO(m_QuarterSpriteRender[2]);		//3/4スプライト削除
			}

			break;

			//3ページ目
		case ThreePage:

			//左矢印表示
			m_SekiryokuSpriteRender[0] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[0]->SetPosition({ 100.0f,-30.0f,0.0f });
			m_SekiryokuSpriteRender[0]->Init("Assets/image/Yazirusi02.dds", 800.0f, 400.0f);
			m_SekiryokuSpriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });		//半透明にする
			//赤ボール表示
			m_SekiryokuSpriteRender[1] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[1]->SetPosition({ 125.0f,50.0f,0.0f });
			m_SekiryokuSpriteRender[1]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//青ボール表示
			m_SekiryokuSpriteRender[2] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[2]->SetPosition({ 125.0f,-100.0f,0.0f });
			m_SekiryokuSpriteRender[2]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//マグネット(上)表示
			m_SekiryokuSpriteRender[3] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[3]->SetPosition({ 300.0f,50.0f,0.0f });
			m_SekiryokuSpriteRender[3]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);
			m_SekiryokuSpriteRender[3]->SetScale({ 1.2,1.2,1.2 });
			//マグネット(下)表示
			m_SekiryokuSpriteRender[4] = NewGO<SpriteRender>(2);
			m_SekiryokuSpriteRender[4]->SetPosition({ 300.0f,-100.0f,0.0f });
			m_SekiryokuSpriteRender[4]->Init("Assets/image/MagnetNS.dds", 350.0f, 350.0f);		//少し大きくする
			m_SekiryokuSpriteRender[4]->SetScale({ -1.2,-1.2,1.2 });		//少し大きくする(+反転)
			//斥力文字表示
			m_SekiryokuSpriteRender[5] = NewGO<SpriteRender>(1);
			m_SekiryokuSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_SekiryokuSpriteRender[5]->Init("Assets/image/Sekiryoku.dds", 350.0f, 350.0f);
			m_SekiryokuSpriteRender[5]->SetScale({ 1.3,1.3,1.3 });		//少し大きくする
			//3/4表示
			m_QuarterSpriteRender[2] = NewGO<SpriteRender>(2);
			m_QuarterSpriteRender[2]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_QuarterSpriteRender[2]->Init("Assets/image/ThreeQuarters.dds", 500.0f, 500.0f);
			if (NextPageFlg)
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_InryokuSpriteRender[i]);		//矢印引力スプライト削除
				}
				DeleteGO(m_QuarterSpriteRender[1]);		//2/4スプライト削除
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					DeleteGO(m_DeathSpriteRender[i]);		//死ぬ床スプライト削除
				}
				DeleteGO(m_QuarterSpriteRender[3]);		//4/4スプライト削除
			}

			break;

			//4ページ目
		case FourPage:
			//赤ボール画像表示
			m_DeathSpriteRender[0] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[0]->SetPosition({ -250.0f,50.0f,0.0f });
			m_DeathSpriteRender[0]->Init("Assets/image/RedBall.dds", 350.0f, 350.0f);
			//青ボール画像表示
			m_DeathSpriteRender[1] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[1]->SetPosition({ -250.0f,-100.0f,0.0f });
			m_DeathSpriteRender[1]->Init("Assets/image/BlueBall.dds", 350.0f, 350.0f);
			//死ぬ床画像表示
			m_DeathSpriteRender[2] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[2]->SetPosition({ 300.0f,-30.0f,0.0f });
			m_DeathSpriteRender[2]->SetScale({ 1.2f,1.2f,1.2f });		//少し小さかったから大きさ調整
			m_DeathSpriteRender[2]->Init("Assets/image/DeathFloor.dds", 350.0f, 350.0f);
			//バツ(1)画像表示
			m_DeathSpriteRender[3] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[3]->SetPosition({ 230.0f,50.0f,0.0f });
			m_DeathSpriteRender[3]->SetScale({ 0.5f,0.5f,0.5f });		//少し小さかったから大きさ調整
			m_DeathSpriteRender[3]->Init("Assets/image/Batu.dds", 350.0f, 350.0f);
			m_DeathSpriteRender[3]->Deactivate();		//非表示
			//バツ(2)画像表示
			m_DeathSpriteRender[4] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[4]->SetPosition({ 230.0f,-100.0f,0.0f });
			m_DeathSpriteRender[4]->SetScale({ 0.5f,0.5f,0.5f });		//少し小さかったから大きさ調整
			m_DeathSpriteRender[4]->Init("Assets/image/Batu.dds", 350.0f, 350.0f);
			m_DeathSpriteRender[4]->Deactivate();		//非表示
			//Dame画像表示
			m_DeathSpriteRender[5] = NewGO<SpriteRender>(1);
			m_DeathSpriteRender[5]->SetPosition({ -50.0f,-30.0f,0.0f });
			m_DeathSpriteRender[5]->SetScale({ 1.5f,1.5f,1.5f });		//少し小さかったから大きさ調整
			m_DeathSpriteRender[5]->Init("Assets/image/Dame.dds", 350.0f, 350.0f);
			m_DeathSpriteRender[5]->Deactivate();		//非表示
			//4/4表示
			m_QuarterSpriteRender[3] = NewGO<SpriteRender>(2);
			m_QuarterSpriteRender[3]->SetPosition({ 0.0f,-280.0f,0.0f });
			m_QuarterSpriteRender[3]->Init("Assets/image/FourQuarters.dds", 500.0f, 500.0f);

			for (int i = 0; i < 6; i++)
			{
				DeleteGO(m_SekiryokuSpriteRender[i]);		//矢印斥力スプライト削除
			}
			DeleteGO(m_QuarterSpriteRender[2]);		//3/4スプライト削除

			break;
		}
	}

	//常に呼ばれる
	switch (PageNum)
	{
	 //タイトルに戻る。
	 case ZeroPage:

		//クラスの破棄
		DeleteGO(this);

		//タイトル画面からスタート
		NewGO<TitleScene>(0);

		break;

	 case OnePage:
		 OnePageTimer++;
		 if (OnePageTimer < 110)
		 {
			 m_KeySpriteRender[2]->Activate();		//表示
			 //ボールの位置を右にずらしていく。
			 OnePageBallPos += 5;
		 }
		 //鍵の場所まで行ったら、
		 else if(110<=OnePageTimer&& OnePageTimer <=200)
		 {
			 m_KeySpriteRender[2]->Deactivate();		//非表示
			 m_KeySpriteRender[3]->Activate();		//表示

			 KeyPos.y += 1.0f;
			 m_KeySpriteRender[0]->SetPosition({ KeyPos });		//鍵の位置更新
		 }
		 else if (200 < OnePageTimer && OnePageTimer < 310)
		 {
			 m_KeySpriteRender[3]->Activate();		//表示

			 //ボールの位置を左にずらしていく。
			 OnePageBallPos -= 5;
			 m_KeySpriteRender[0]->SetPosition({ OnePageBallPos,KeyPos.y,KeyPos.z });		//鍵の位置更新
		 }
		 else if (310 <= OnePageTimer && OnePageTimer<=400)
		 {
			 m_KeySpriteRender[3]->Deactivate();		//非表示
			 m_KeySpriteRender[4]->Activate();		//表示
		 }
		 else
		 {
			 m_KeySpriteRender[4]->Deactivate();		//表示
			 m_KeySpriteRender[2]->Activate();		//表示
			 //鍵の持ち上げ分のy座標を戻す。(初期化)
			 KeyPos = { 300.0f,-30.0f,0.0f };
			 m_KeySpriteRender[0]->SetPosition({ KeyPos });		//鍵の位置更新
			 //タイマーを初期化して初めのif文に戻る
			 OnePageTimer = 0;
		 }

		 m_KeySpriteRender[1]->SetPosition({ OnePageBallPos,-30.0f,0.0f });		//赤ボールの位置更新

		 break;

	 case TwoPage:

		 TwoPageTimer++;
		 if (TwoPageTimer < 108)
		 {
			 //ボールの位置を右にずらしていく。
			 TwoPageBallPos += 4;
		 }
		 else if(108<=TwoPageTimer&&TwoPageTimer <= 200)
		 {
			 //なにもしない
		 }
		 else
		 {
			 TwoPageBallPos = -300.0f;//ボールをはじめの位置に持っていく。
			 //タイマーを初期化して初めのif文に戻る
			 TwoPageTimer = 0;
		 }

		 m_InryokuSpriteRender[1]->SetPosition({ TwoPageBallPos,50.0f,0.0f });		//赤ボールの位置更新
		 m_InryokuSpriteRender[2]->SetPosition({ TwoPageBallPos,-100.0f,0.0f });		//青ボールの位置更新

		break;

	 case ThreePage:

		 ThreePageTimer++;
		 if (ThreePageTimer < 108)
		 {
			 //ボールの位置を右にずらしていく。
			 ThreePageBallPos -= 4;
		 }
		 else if (108 <= ThreePageTimer && ThreePageTimer <= 200)
		 {
			 //なにもしない
		 }
		 else
		 {
			 ThreePageBallPos =  125.0f;//ボールをはじめの位置に持っていく。
			 //タイマーを初期化して初めのif文に戻る
			 ThreePageTimer = 0;
		 }

		 m_SekiryokuSpriteRender[1]->SetPosition({ ThreePageBallPos,50.0f,0.0f });		//赤ボールの位置更新
		 m_SekiryokuSpriteRender[2]->SetPosition({ ThreePageBallPos,-100.0f,0.0f });		//赤ボールの位置更新

		break;

	 case FourPage:
		 FourPageTimer++;
		 if (FourPageTimer < 85)
		 {
			 //ボールの位置を右にずらしていく。
			 FourPageBallPos +=5;
		 }
		 else
		 {
			 m_DeathSpriteRender[3]->Activate();		//表示
			 m_DeathSpriteRender[4]->Activate();		//表示
			 m_DeathSpriteRender[5]->Activate();		//表示

			 if (FourPageTimer > 200)
			 {
				 FourPageBallPos = -250.0f;		//ボールをはじめの位置に持っていく。
				 FourPageTimer = 0;		//タイマー初期化して上のifに戻る。
				 m_DeathSpriteRender[3]->Deactivate();		//非表示
				 m_DeathSpriteRender[4]->Deactivate();		//非表示
				 m_DeathSpriteRender[5]->Deactivate();		//非表示
			 }
		 }
		 m_DeathSpriteRender[0]->SetPosition({ FourPageBallPos,50.0f,0.0f });		//赤ボールの位置更新
		 m_DeathSpriteRender[1]->SetPosition({ FourPageBallPos,-100.0f,0.0f });		//青ボールの位置更新
			break;

	 //タイトルに戻る。
	 case FivePage:

		 DeleteGO(this);

		 //タイトル画面からスタート
		 NewGO<TitleScene>(0);

		 break;
	}
}