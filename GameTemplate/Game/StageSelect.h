#pragma once
class StageSelectLevel2D;
class Game;

namespace {
	const Vector3 SPRITE_STAGE_NUM_POS = { 0.0f,-270.0f,0.0f };
	const Vector2 SPRITE_STAGE_NUM_WH = { 350.0f,350.0f };
	const Vector3 SPRITE_STAGE_NUM_SCALE = { 1.3f,1.3f,1.3f };
	const Vector2 SPRITE_STAGE_MODEL_WH = { 1024.0f,768.0f };
	const Vector3 SPRITE_STAGE_MODEL_SCALE = { 0.5f,0.5f,0.5f };

	const char* SPRITE_NAME_STAGE_NUM_1 = "Assets/image/Stage1.dds";
	const char* SPRITE_NAME_STAGE_MODEL_1 = "Assets/image/Stage01.dds";
	const char* SPRITE_NAME_STAGE_NUM_2 = "Assets/image/Stage2.dds";
	const char* SPRITE_NAME_STAGE_MODEL_2 = "Assets/image/Stage02.dds";
	const char* SPRITE_NAME_STAGE_NUM_3 = "Assets/image/Stage3.dds";
	const char* SPRITE_NAME_STAGE_MODEL_3 = "Assets/image/Stage03.dds";
	const char* SPRITE_NAME_STAGE_NUM_4 = "Assets/image/Stage4.dds";
	const char* SPRITE_NAME_STAGE_MODEL_4 = "Assets/image/Stage04.dds";
}

class StageSelect : public IGameObject
{
private:
	bool Start();
	~StageSelect();
	void Update();
private:
		//ボタンを選択するための列挙型
	enum Select {
		BackButton,
		KetteiButton,

		enSelect_Num
	};
	enum StageSelectSprite{
		enStageSelectSprite_StageNum,
		enStageSelectSprite_StageModel,

		enStageSelectSprite_Num
	};
	bool ScaleUpFlag = true;
	int NowSelectStage = 0;
	int NowSelect = 1;	//列挙の値を格納する変数。はじめは「けってい」ボタンの1。
	float Fscale = 0.23f;
	float Fscale1 = 0.18f;
	Vector3 Vscale = { 0.0f,0.0f,0.0f };
	Vector3 m_standardScale[enSelect_Num] = { Vector3::One };
	Vector3 vscale = { 0.23f,0.23f,0.23f };
	Vector3 vscale1 = { 0.18f,0.18f,0.18f };


	/**
	 * @brief それぞれのクラスのポインタ
	*/

	StageSelectLevel2D* m_sprite = nullptr;
	SpriteRender* m_stageSpriteRender[Stage_Num][enStageSelectSprite_Num] = { nullptr };		//ステージ文字スプライトレンダー
	Game* m_game = nullptr;
};