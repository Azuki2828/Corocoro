#include "stdafx.h"
#include "StageSelect.h"
#include "StageSelectLevel2D.h"
#include "Game.h"
#include "TitleScene.h"

bool StageSelect::Start()
{
	//ステージ選択画面表示
	m_stageSelectLevel2D = NewGO<StageSelectLevel2D>(enPriority_Zeroth, NAME_STAGE_SELECT_LEVEL2D);

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

	//m_standardScale[BackButton] = m_stageSelectLevel2D->GetScale(enStageSelectSprite_BackButton);
	//m_standardScale[KetteiButton] = m_stageSelectLevel2D->GetScale(enStageSelectSprite_DecisionButton);

	return true;
}

StageSelect::~StageSelect()
{
	DeleteGO(m_stageSelectLevel2D);	//レベル削除
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
		if (m_nowSelect == BackButton) {
			//選択を右に1つずらす。
			m_nowSelect = KetteiButton;
		}
		//現在セレクトされているボタンが「けってい」(1番)だったら、
		else {
			//選択を左に1つずらす。
			m_nowSelect = BackButton;
		}
		//移動効果音鳴らす。
		SoundManager::GetInstance()->Play(enSE_CursolMove);
	}

	//ボタンを全て半透明にする。
	m_stageSelectLevel2D->GetSprite(enStageSelectSprite_BackButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);
	m_stageSelectLevel2D->GetSprite(enStageSelectSprite_DecisionButton)->SetMulColor(TRANSLUCENT_VALUE_HALF);

	//現在選択しているボタンの強調表示
	switch (m_nowSelect) {

		//「もどる」ボタンが選ばれているとき、
	 case BackButton:
		//ボタンを不透明度100％にする。
		 m_stageSelectLevel2D->GetSprite(enStageSelectSprite_BackButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (m_spriteBackScale < BACK_BUTTON_SIZE_MIN) {
			m_spriteScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (m_spriteBackScale > BACK_BUTTON_SIZE_MAX) {
			m_spriteScaleUpFlag = false;
		}

		if (m_spriteScaleUpFlag == true) {
			//拡大
			m_spriteBackScale += BUTTON_SCALE_ADD;
		}
		if (m_spriteScaleUpFlag == false) {
			//縮小
			m_spriteBackScale -= BUTTON_SCALE_ADD;
		}
		//スプライトに反映。
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_BackButton)->SetScale({ m_spriteBackScale, m_spriteBackScale, m_spriteBackScale });

		//選択されていないボタンの拡大率を元に戻す。
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_DecisionButton)->SetScale({ DECISION_BUTTON_SIZE_MIN ,DECISION_BUTTON_SIZE_MIN ,DECISION_BUTTON_SIZE_MIN });

		break;

		//「けってい」ボタンが選ばれているとき、
	 case KetteiButton:
		//ボタンを不透明度100％にする。
		 m_stageSelectLevel2D->GetSprite(enStageSelectSprite_DecisionButton)->SetMulColor(TRANSLUCENT_VALUE_MAX);

		//単振動の公式を使ってボタンを拡大縮小する。

		 //大きさが最小になったとき、
		if (m_spriteDecisionScale < DECISION_BUTTON_SIZE_MIN) {
			m_spriteScaleUpFlag = true;
		}
		//大きさが最大になったとき、
		if (m_spriteDecisionScale > DECISION_BUTTON_SIZE_MAX) {
			m_spriteScaleUpFlag = false;
		}

		if (m_spriteScaleUpFlag == true) {
			//拡大
			m_spriteDecisionScale += BUTTON_SCALE_ADD;
		}
		if (m_spriteScaleUpFlag == false) {
			//縮小
			m_spriteDecisionScale -= BUTTON_SCALE_ADD;
		}
		//スプライトに反映。
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_DecisionButton)->SetScale({ m_spriteDecisionScale,m_spriteDecisionScale,m_spriteDecisionScale });

		//選択されていないボタンの拡大率を元に戻す。
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_BackButton)->SetScale({ BACK_BUTTON_SIZE_MIN ,BACK_BUTTON_SIZE_MIN ,BACK_BUTTON_SIZE_MIN });

		break;
	};

	//ステージ選択

	//現在選択されているステージが1のとき、
	if (m_nowSelectStage == Stage_One)
	{
		//左矢印を非表示する
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_Select_Left)->Deactivate();
		//LBを非表示する
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_LB)->Deactivate();
	}
	//ステージ１以外の時、
	else
	{
		//左矢印を表示する
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_Select_Left)->Activate();
		//LBを表示する
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_LB)->Activate();
	}
	//現在選択されているステージが最後のステージのとき、
	if (m_nowSelectStage == Stage_Four)
	{
		//右矢印を非表示する
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_Select_Right)->Deactivate();
		//RBを非表示する
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_RB)->Deactivate();
	}
	//最後のステージ以外の時、
	else
	{
		//右矢印を表示する
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_Select_Right)->Activate();
		//RBを表示する
		m_stageSelectLevel2D->GetSprite(enStageSelectSprite_RB)->Activate();
	}

	//LBボタンが押されたら、(キーボードB)
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonLB1))
	{
		//ステージ1が選ばれていないときだけ1つ下にずらす
		if (m_nowSelectStage != Stage_One)
		{
			//移動効果音鳴らす。
			SoundManager::GetInstance()->Play(enSE_CursolMove);
			//ステージ番号を１つ下にずらす
			m_nowSelectStage--;
		}
	}
	//RBボタンが押されたら、(キーボードの7)
	if (g_pad[enData_Zeroth]->IsTrigger(enButtonRB1))
	{
		if (m_nowSelectStage != Stage_Four) {
			//移動効果音鳴らす。
			SoundManager::GetInstance()->Play(enSE_CursolMove);
			//ステージ番号を１つ上にずらす
			m_nowSelectStage++;
		}
	}
	//ステージ1,ステージ2などの文字画像表示
	switch (m_nowSelectStage)
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

		switch (m_nowSelect) {

			//「もどる」ボタンが選ばれているとき、
		 case BackButton:
			//タイトル画面に遷移。
			NewGO<TitleScene>(enPriority_Zeroth);

			break;

			//「決定」ボタンが選ばれているとき、
		 case KetteiButton:
			 m_game = NewGO<Game>(enPriority_Zeroth, "game");
			 //ゲーム画面に遷移
			 m_game->SetStageNum(m_nowSelectStage);
			break;
		};
		//クラスを削除。
		DeleteGO(this);
	}
}