#include "stdafx.h"
#include "StageSelect.h"
#include "StageSelectLevel2D.h"
#include "Game.h"
#include "TitleScene.h"

bool StageSelect::Start()
{
	//ステージ選択画面表示
	m_sprite = NewGO<StageSelectLevel2D>(enPriority_Zeroth, NAME_STAGE_SELECT_LEVEL2D);

	//BGM再生。
	SoundManager::GetInstance()->Play(enBGM_Title);

	//Stage1
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->SetPosition(SPRITE_STAGE_NUM_POS);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->Init(SPRITE_NAME_STAGE_NUM_1, SPRITE_STAGE_NUM_WH.x, SPRITE_STAGE_NUM_WH.y);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->SetScale(SPRITE_STAGE_NUM_SCALE);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->Deactivate();		//非表示

	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->SetPosition(Vector3::Zero);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->Init(SPRITE_NAME_STAGE_MODEL_1, SPRITE_STAGE_MODEL_WH.x, SPRITE_STAGE_MODEL_WH.y);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->SetScale(SPRITE_STAGE_MODEL_SCALE);
	m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->Deactivate();		//非表示
	//Stage2
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->SetPosition(SPRITE_STAGE_NUM_POS);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Init(SPRITE_NAME_STAGE_NUM_2, SPRITE_STAGE_NUM_WH.x, SPRITE_STAGE_NUM_WH.y);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->SetScale(SPRITE_STAGE_NUM_SCALE);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Deactivate();		//非表示

	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->SetPosition(Vector3::Zero);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Init(SPRITE_NAME_STAGE_MODEL_2, SPRITE_STAGE_MODEL_WH.x, SPRITE_STAGE_MODEL_WH.y);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->SetScale(SPRITE_STAGE_MODEL_SCALE);
	m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Deactivate();		//非表示
	//Stage3
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->SetPosition(SPRITE_STAGE_NUM_POS);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Init(SPRITE_NAME_STAGE_NUM_3, SPRITE_STAGE_NUM_WH.x, SPRITE_STAGE_NUM_WH.y);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->SetScale(SPRITE_STAGE_NUM_SCALE);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Deactivate();		//非表示

	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->SetPosition(Vector3::Zero);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Init(SPRITE_NAME_STAGE_MODEL_3, SPRITE_STAGE_MODEL_WH.x, SPRITE_STAGE_MODEL_WH.y);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->SetScale(SPRITE_STAGE_MODEL_SCALE);
	m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Deactivate();		//非表示

	//Stage4
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->SetPosition(SPRITE_STAGE_NUM_POS);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->Init(SPRITE_NAME_STAGE_NUM_4, SPRITE_STAGE_NUM_WH.x, SPRITE_STAGE_NUM_WH.y);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->SetScale(SPRITE_STAGE_NUM_SCALE);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->Deactivate();		//非表示

	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel] = NewGO<SpriteRender>(enPriority_First);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->SetPosition(Vector3::Zero);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->Init(SPRITE_NAME_STAGE_MODEL_4, SPRITE_STAGE_MODEL_WH.x, SPRITE_STAGE_MODEL_WH.y);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->SetScale(SPRITE_STAGE_MODEL_SCALE);
	m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->Deactivate();		//非表示

	return true;
}

StageSelect::~StageSelect()
{
	DeleteGO(m_sprite);	//レベル削除
	SoundManager::GetInstance()->Release(enBGM_Title);	//BGM削除
	for (int i = 0; i < Stage_Num; i++)
	{
		DeleteGO(m_stageSpriteRender[i][enStageSelectSprite_StageNum]);
		DeleteGO(m_stageSpriteRender[i][enStageSelectSprite_StageModel]);
	}
}

void StageSelect::Update()
{
	//右入力or左入力されたら、
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonRight) || g_pad[enData_Zeroth]->IsTrigger(enButtonLeft)) {
		//現在セレクトされているボタンが「もどる」(0番)だったら、
		if (NowSelect == BackButton) {
			//選択を右に1つずらす。
			NowSelect = KetteiButton;
		}
		//現在セレクトされているボタンが「けってい」(1番)だったら、
		else {
			//選択を左に1つずらす。
			NowSelect = BackButton;
		}
		//移動効果音鳴らす。
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}

	//ボタンを全て半透明にする。
	HUD::GetHUD()->SetMulColor(enSprite_Back, TRANSLUCENT_VALUE_HALF);
	HUD::GetHUD()->SetMulColor(enSprite_Decision, TRANSLUCENT_VALUE_HALF);

	m_standardScale[BackButton] = HUD::GetHUD()->GetScale(enSprite_Back);
	m_standardScale[KetteiButton] = HUD::GetHUD()->GetScale(enSprite_Decision);

	//現在選択しているボタンの強調表示
	switch (NowSelect) {

		//「もどる」ボタンが選ばれているとき、
	 case BackButton:
		//ボタンを不透明度100％にする。
		 HUD::GetHUD()->SetMulColor(enSprite_Back, TRANSLUCENT_VALUE_MAX);

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (Fscale < BUTTON_SIZE_MIN) {
			ScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (Fscale > BUTTON_SIZE_MAX) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//拡大
			Fscale += BUTTON_SCALE_ADD;
		}
		if (ScaleUpFlag == false) {
			//縮小
			Fscale -= BUTTON_SCALE_ADD;
		}
		//スプライトに反映。
		Vscale = { Fscale,Fscale,Fscale };
		HUD::GetHUD()->SetScale(enSprite_Back, Vscale);

		//選択されていないボタンの拡大率を元に戻す。
		HUD::GetHUD()->SetScale(enSprite_Decision, m_standardScale[KetteiButton]);

		break;

		//「けってい」ボタンが選ばれているとき、
	 case KetteiButton:
		//ボタンを不透明度100％にする。
		 HUD::GetHUD()->SetMulColor(enSprite_Decision, TRANSLUCENT_VALUE_MAX);

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (Fscale1 < BUTTON_SIZE_MIN) {
			ScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (Fscale1 > BUTTON_SIZE_MAX) {
			ScaleUpFlag = false;
		}

		if (ScaleUpFlag == true) {
			//拡大
			Fscale1 += BUTTON_SCALE_ADD;
		}
		if (ScaleUpFlag == false) {
			//縮小
			Fscale1 -= BUTTON_SCALE_ADD;
		}
		//スプライトに反映。
		Vscale = { Fscale1,Fscale1,Fscale1 };
		HUD::GetHUD()->SetScale(enSprite_Decision, Vscale);

		//選択されていないボタンの拡大率を元に戻す。
		HUD::GetHUD()->SetScale(enSprite_Back, m_standardScale[BackButton]);

		break;
	};

	//ステージ選択

	//現在選択されているステージが1のとき、
	if (NowSelectStage == Stage_One)
	{
		//左矢印を非表示する
		HUD::GetHUD()->Deactivate(enSprite_LeftSelect);
		//LBを非表示する
		HUD::GetHUD()->Deactivate(enSprite_LB);
	}
	//ステージ１以外の時、
	else
	{
		//左矢印を表示する
		HUD::GetHUD()->Activate(enSprite_LeftSelect);
		//LBを表示する
		HUD::GetHUD()->Activate(enSprite_LB);
	}
	//現在選択されているステージが最後のステージのとき、
	if (NowSelectStage == Stage_Four)
	{
		//右矢印を非表示する
		HUD::GetHUD()->Deactivate(enSprite_RightSelect);
		//RBを非表示する
		HUD::GetHUD()->Deactivate(enSprite_RB);
	}
	//最後のステージ以外の時、
	else
	{
		//右矢印を表示する
		HUD::GetHUD()->Activate(enSprite_RightSelect);
		//RBを表示する
		HUD::GetHUD()->Activate(enSprite_RB);
	}

	//LBボタンが押されたら、(キーボードB)
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonLB1))
	{
		//ステージ1が選ばれていないときだけ1つ下にずらす
		if (NowSelectStage != Stage_One)
		{
			//移動効果音鳴らす。
			SoundManager::GetInstance()->Play(enSE_CursolMove);
			//ステージ番号を１つ下にずらす
			NowSelectStage--;
		}
	}
	//RBボタンが押されたら、(キーボードの7)
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonRB1))
	{
		if (NowSelectStage != Stage_Four) {
			//移動効果音鳴らす。
			SoundManager::GetInstance()->Play(enSE_CursolMove);
			//ステージ番号を１つ上にずらす
			NowSelectStage++;
		}
	}
	//ステージ1,ステージ2などの文字画像表示
	switch (NowSelectStage)
	{
	case Stage_One:
		m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->Activate();			//表示
		m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->Activate();			//表示
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Deactivate();		//非表示
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Deactivate();		//非表示
		break;
	case Stage_Two:
		m_stageSpriteRender[Stage_One][enStageSelectSprite_StageNum]->Deactivate();		//非表示
		m_stageSpriteRender[Stage_One][enStageSelectSprite_StageModel]->Deactivate();		//非表示
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Activate();			//表示
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Activate();			//表示
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Deactivate();		//非表示
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Deactivate();		//非表示
		break;
	case Stage_Three:
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageNum]->Deactivate();		//非表示
		m_stageSpriteRender[Stage_Two][enStageSelectSprite_StageModel]->Deactivate();		//非表示
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Activate();			//表示
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Activate();			//表示
		m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->Deactivate();		//非表示
		m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->Deactivate();		//非表示
		break;
	case Stage_Four:
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageNum]->Deactivate();		//非表示
		m_stageSpriteRender[Stage_Three][enStageSelectSprite_StageModel]->Deactivate();		//非表示
		m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageNum]->Activate();			//表示
		m_stageSpriteRender[Stage_Four][enStageSelectSprite_StageModel]->Activate();			//表示
		break;
	}

	//Aボタン(キーボードのJ)が押されたら
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonA)) {
		//決定ボタン音再生。
		SoundManager::GetInstance()->Play(enSE_DecisionButton);

		switch (NowSelect) {

			//「もどる」ボタンが選ばれているとき、
		 case BackButton:
			//タイトル画面に遷移。
			NewGO<TitleScene>(enPriority_Zeroth);

			break;

			//「決定」ボタンが選ばれているとき、
		 case KetteiButton:
			 m_game = NewGO<Game>(enPriority_Zeroth, "game");
			 //ゲーム画面に遷移
			 m_game->SetStageNum(NowSelectStage);
			break;
		};
		//クラスを削除。
		DeleteGO(this);
	}
}