#include "stdafx.h"
#include "StageSelect.h"
#include "StageSelectLevel2D.h"
#include "Game.h"
#include "TitleScene.h"

bool StageSelect::Start()
{
	//ステージ選択画面表示
	sprite = NewGO<StageSelectLevel2D>(0, "StageSelectLevel2D");

	//BGM再生。
	SoundManager::GetInstance()->Play(BGM_Title);
	//BGMSound = NewGO<CSoundSource>(0);
	//BGMSound->Init(L"Assets/sound/TitleBGM.wav");
	//BGMSound->SetVolume(1.0f);
	//BGMSound->Play(true);		//ループ再生。

	//Stage1
	m_StageSpriteRender[0][0] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[0][0]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[0][0]->Init("Assets/image/Stage1.dds", 350.0f, 350.0f);
	m_StageSpriteRender[0][0]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[0][0]->Deactivate();		//非表示

	m_StageSpriteRender[0][1] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[0][1]->SetPosition({ 0.0f,0.0f,0.0f });
	m_StageSpriteRender[0][1]->Init("Assets/image/Stage01.dds", 1024.0f, 768.0f);
	m_StageSpriteRender[0][1]->SetScale({ 0.5f,0.5f,0.5f });
	m_StageSpriteRender[0][1]->Deactivate();		//非表示
	//Stage2
	m_StageSpriteRender[1][0] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[1][0]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[1][0]->Init("Assets/image/Stage2.dds", 350.0f, 350.0f);
	m_StageSpriteRender[1][0]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[1][0]->Deactivate();		//非表示

	m_StageSpriteRender[1][1] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[1][1]->SetPosition({ 0.0f,0.0f,0.0f });
	m_StageSpriteRender[1][1]->Init("Assets/image/Stage02.dds", 1024.0f, 768.0f);
	m_StageSpriteRender[1][1]->SetScale({ 0.5f,0.5f,0.5f });
	m_StageSpriteRender[1][1]->Deactivate();		//非表示
	//Stage3
	m_StageSpriteRender[2][0] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[2][0]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[2][0]->Init("Assets/image/Stage3.dds", 350.0f, 350.0f);
	m_StageSpriteRender[2][0]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[2][0]->Deactivate();		//非表示

	m_StageSpriteRender[2][1] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[2][1]->SetPosition({ 0.0f, 0.0f,0.0f });
	m_StageSpriteRender[2][1]->Init("Assets/image/Stage03.dds", 1024.0f, 768.0f);
	m_StageSpriteRender[2][1]->SetScale({ 0.5f,0.5f,0.5f });
	m_StageSpriteRender[2][1]->Deactivate();		//非表示

	//Stage4
	m_StageSpriteRender[3][0] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[3][0]->SetPosition({ 0.0f,-270.0f,0.0f });
	m_StageSpriteRender[3][0]->Init("Assets/image/Stage4.dds", 350.0f, 350.0f);
	m_StageSpriteRender[3][0]->SetScale({ 1.3f,1.3f,1.3f });
	m_StageSpriteRender[3][0]->Deactivate();		//非表示

	m_StageSpriteRender[3][1] = NewGO<SpriteRender>(1);
	m_StageSpriteRender[3][1]->SetPosition({ 0.0f, 0.0f,0.0f });
	m_StageSpriteRender[3][1]->Init("Assets/image/Stage04.dds", 1024.0f, 768.0f);
	m_StageSpriteRender[3][1]->SetScale({ 0.5f,0.5f,0.5f });
	m_StageSpriteRender[3][1]->Deactivate();		//非表示

	return true;
}

StageSelect::~StageSelect()
{
	DeleteGO(sprite);	//レベル削除
	SoundManager::GetInstance()->Release(BGM_Title);	//BGM削除
	for (int i = 0; i < (FinalStage-1); i++)
	{
		DeleteGO(m_StageSpriteRender[i][0]);
		DeleteGO(m_StageSpriteRender[i][1]);
	}
}

void StageSelect::Update()
{
	//右入力or左入力されたら、
	if (g_pad[0]->IsTrigger(enButtonRight) || g_pad[0]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「もどる」(0番)だったら、
		if (NowSelect % 2 == 0) {
			//選択を右に1つずらす。
			NowSelect = 1;
		}
		//現在セレクトされているボタンが「けってい」(1番)だったら、
		else {
			//選択を左に1つずらす。
			NowSelect = 0;
		}
		//移動効果音鳴らす。
		SoundManager::GetInstance()->Play(SE_CursolMove);
	}

	//ボタンを全て半透明にする。
	for (int i = 4; i < 6; i++) {
		sprite->GetSprite(i)->SetMulColor({ 1.0f,1.0f,1.0f,0.3f });
	}

	//現在選択しているボタンの強調表示
	switch (NowSelect) {

		//「もどる」ボタンが選ばれているとき、
	 case BackButton:
		//ボタンを不透明度100％にする。
		sprite->GetSprite(4)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (Fscale < 0.20f) {
			ScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (Fscale > 0.23f) {
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
		sprite->GetSprite(4)->SetScale(Vscale);

		//選択されていないボタンの拡大率を元に戻す。
		sprite->GetSprite(5)->SetScale(vscale1);

		break;

		//「けってい」ボタンが選ばれているとき、
	 case KetteiButton:
		//ボタンを不透明度100％にする。
		sprite->GetSprite(5)->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (Fscale1 < 0.15f) {
			ScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (Fscale1 > 0.18f) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//拡大
			Fscale1 += 0.0005f;
		}
		if (ScaleUpFlag == false) {
			//縮小
			Fscale1 -= 0.0005f;
		}
		//スプライトに反映。
		Vscale = { Fscale1,Fscale1,Fscale1 };
		sprite->GetSprite(5)->SetScale(Vscale);

		//選択されていないボタンの拡大率を元に戻す。
		sprite->GetSprite(4)->SetScale(vscale);

		break;
	};

	//ステージ選択

	//現在選択されているステージが1のとき、
	if (NowSelectStage == StageOne)
	{
		//左矢印を非表示する
		sprite->GetSprite(2)->Deactivate();
		//LBを非表示する
		sprite->GetSprite(6)->Deactivate();
	}
	//ステージ１以外の時、
	else
	{
		//左矢印を表示する
		sprite->GetSprite(2)->Activate();
		//LBを表示する
		sprite->GetSprite(6)->Activate();
	}
	//現在選択されているステージが最後のステージのとき、
	if (NowSelectStage == FinalStage-1)
	{
		//右矢印を非表示する
		sprite->GetSprite(3)->Deactivate();
		//RBを非表示する
		sprite->GetSprite(7)->Deactivate();
	}
	//最後のステージ以外の時、
	else
	{
		//右矢印を表示する
		sprite->GetSprite(3)->Activate();
		//RBを表示する
		sprite->GetSprite(7)->Activate();
	}

	//LBボタンが押されたら、(キーボードB)
	if (g_pad[0]->IsTrigger(enButtonLB1))
	{
		//ステージ1が選ばれていないときだけ1つ下にずらす
		if (NowSelectStage != StageOne)
		{
			//移動効果音鳴らす。
			SoundManager::GetInstance()->Play(SE_CursolMove);
			//ステージ番号を１つ下にずらす
			NowSelectStage -= 1;
		}
	}
	//RBボタンが押されたら、(キーボードの7)
	if (g_pad[0]->IsTrigger(enButtonRB1))
	{
		if (NowSelectStage != (FinalStage-1)) {
			//移動効果音鳴らす。
			SoundManager::GetInstance()->Play(SE_CursolMove);
			//ステージ番号を１つ上にずらす
			NowSelectStage += 1;
		}
	}
	//ステージ1,ステージ2などの文字画像表示
	switch (NowSelectStage)
	{
	case StageOne:
		m_StageSpriteRender[0][0]->Activate();			//表示
		m_StageSpriteRender[0][1]->Activate();			//表示
		m_StageSpriteRender[1][0]->Deactivate();		//非表示
		m_StageSpriteRender[1][1]->Deactivate();		//非表示
		break;
	case StageTwo:
		m_StageSpriteRender[0][0]->Deactivate();		//非表示
		m_StageSpriteRender[0][1]->Deactivate();		//非表示
		m_StageSpriteRender[1][0]->Activate();			//表示
		m_StageSpriteRender[1][1]->Activate();			//表示
		m_StageSpriteRender[2][0]->Deactivate();		//非表示
		m_StageSpriteRender[2][1]->Deactivate();		//非表示
		break;
	case StageThree:
		m_StageSpriteRender[1][0]->Deactivate();		//非表示
		m_StageSpriteRender[1][1]->Deactivate();		//非表示
		m_StageSpriteRender[2][0]->Activate();			//表示
		m_StageSpriteRender[2][1]->Activate();			//表示
		m_StageSpriteRender[3][0]->Deactivate();		//非表示
		m_StageSpriteRender[3][1]->Deactivate();		//非表示
		break;
	case StageFour:
		m_StageSpriteRender[2][0]->Deactivate();		//非表示
		m_StageSpriteRender[2][1]->Deactivate();		//非表示
		m_StageSpriteRender[3][0]->Activate();			//表示
		m_StageSpriteRender[3][1]->Activate();			//表示
		break;
	}

	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[0]->IsTrigger(enButtonA)) {
		//決定ボタン音再生。
		SoundManager::GetInstance()->Play(SE_DecisionButton);

		switch (NowSelect) {

			//「もどる」ボタンが選ばれているとき、
		 case BackButton:
			//タイトル画面に遷移。
			NewGO<TitleScene>(0);

			break;

			//「決定」ボタンが選ばれているとき、
		 case KetteiButton:
			 m_game = NewGO<Game>(0, "game");
			 //ゲーム画面に遷移
			 m_game->SetStageNum(4);
			break;
		};
		//クラスを削除。
		DeleteGO(this);
	}
}