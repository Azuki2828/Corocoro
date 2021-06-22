#pragma once

//////////////////////////////////////////////////
///　２つ以上のクラスで使う定数をまとめている　///
//////////////////////////////////////////////////



/**
 * @brief 優先度。enPriority_Zerothが最も先に描画される。
*/
enum PriorityNum{
	enPriority_Zeroth,
	enPriority_First,
	enPriority_Second,
	enPriority_Third,
	enPriority_Fourth,
	enPriority_Fifth
};

/**
 * @brief 要素にアクセスするときに使う番号
*/
enum DataNum{
	enData_Zeroth,
	enData_First,
	enData_Second,
	enData_Third,
	enData_Fourth,
	enData_Fifth
};

/**
 * @brief ステージ番号
*/
enum StageNum {
	Stage_One,
	Stage_Two,
	Stage_Three,
	Stage_Four,

	Stage_Num
};

/**
 * @brief スプライト番号
*/
enum SpriteNum{
	enSprite_Zeroth,
	enSprite_First,
	enSprite_Second,
	enSprite_Third,
	enSprite_Fourth,
	enSprite_Fifth,
	enSprite_Sixth,
	enSprite_Seventh,
	enSprite_Eighth,
	enSprite_Nineth,

	enSprite_Num
};

/**
 * @brief サウンドリスト
*/
enum SoundList {
	enBGM_Title,
	enBGM_Game,
	enBGM_GameUpTempo,
	enSE_GameClear,
	enSE_CursolMove,
	enSE_DecisionButton,
	enSE_CountDown,
	enSE_NSChange,
	enSE_KeyGet,
	enSE_BoxOpen,
	enSE_Death,
	enSE_ReStart,

	enSound_Num
};

/**
 * @brief HUDに登録されているスプライト
*/
enum HUDList {
	enSprite_3,
	enSprite_2,
	enSprite_1,
	enSprite_GO,
	enSprite_Result,
	enSprite_GrayBack,
	enSprite_Time,
	enSprite_Ten1,
	enSprite_Second1,
	enSprite_Top,
	enSprite_Ten2,
	enSprite_Second2,
	enSprite_TitleButton,
	enSprite_EndButton,
	enSprite_EheheNS03,
	enSprite_StageSelect,
	enSprite_LeftSelect,
	enSprite_RightSelect,
	enSprite_Back,
	enSprite_Decision,
	enSprite_LB,
	enSprite_RB,
	enSprite_EheheNS,
	enSprite_TitleLogo,
	enSprite_StartButton,
	enSprite_RuleButton,




	enSprite_HUDNum

};

/**
 * @brief 磁石番号
*/
enum MagnetNum {
	enMagnet_Zero,
	enMagnet_First,
	enMagnet_Second,
	enMagnet_Third,
	enMagnet_Fourth,
	enMagnet_Fifth,
	enMagnet_Sixth,
	enMagnet_Seventh,
	enMagnet_Eighth,
	enMagnet_Nineth,
	enMagnet_Tenth,
	enMagnet_Eleventh,
	enMagnet_Twelfth,
	enMagnet_Thirteenth,
	enMagnet_Fourteenth,
	enMagnet_Fifteenth,
	enMagnet_Sixteenth,
	enMagnet_Seventeenth,
	enMagnet_Eighteenth,
	enMagnet_Nineteenth,
	enMagnet_Twentieth,
	enMagnet_TwentyFirst,
	enMagnet_TwentySecond,
	enMagnet_TwentyThird,
	enMagnet_TwentyFourth,
	enMagnet_TwentyFifth,
	enMagnet_TwentySixth,
	enMagnet_TwentySeventh,
	enMagnet_TwentyEighth,
	enMagnet_TwentyNineth,
	enMagnet_Thirtieth,
	enMagnet_ThirtyFirst,
	enMagnet_ThirtySecond,
	enMagnet_ThirtyThird,
	enMagnet_ThirtyFourth,
	enMagnet_ThirtyFifth,
	enMagnet_ThirtySixth,
	enMagnet_ThirtySeventh,
	enMagnet_ThirtyEighth,
	enMagnet_ThirtyNineth,
	enMagnet_Fourtieth,
	enMagnet_FourtyFirst,
	enMagnet_FourtySecond,
	enMagnet_FourtyThird,
	enMagnet_FourtyFourth,
	enMagnet_FourtyFifth,
	enMagnet_FourtySixth,
	enMagnet_FourtySeventh,
	enMagnet_FourtyEighth,
	enMagnet_FourtyNineth,
};

namespace {

	const int NAME_SIZE = 256;										//名前の最大のサイズ
	const int TEXT_SIZE = 64;
	const float CAMERA_ROT_VALUE = -2.0f;

	const float REVERSE_VECTOR = -1.0f;

	const Vector3 GRAVITY_VALUE = { 0.0f,-300.0f,0.0f };
	const Vector3 GRAVITY_REVERSE_VALUE = { 0.0f,300.0f,0.0f };

	const Vector3 CAMERA_UP = { 0.0f,1.0f,0.0f };

	const char* NAME_PLAYER = "player";
	const char* NAME_GAME = "game";
	const char* NAME_BACK_GROUND = "backGround";
	const char* NAME_MAIN_CAMERA = "mainCamera";
	const char* NAME_GAME_LEVEL2D = "gameLevel2D";
	const char* NAME_KEY = "key";
	const char* NAME_TREASURE_BOX = "treasureBox";
	const char* NAME_SAVE_DATA = "saveData";
	const char* NAME_RESULT_SCENE = "resultScene";
	const char* NAME_DIRECTION_LIGHT = "mainLight";
	const char* NAME_RESULT_LEVEL2D = "resultLevel2D";
	const char* NAME_STAGE_SELECT_LEVEL2D = "StageSelectLevel2D";

	const wchar_t* SOUND_FILEPATH_TITLE_BGM = L"Assets/sound/TitleBGM.wav";
	const wchar_t* SOUND_FILEPATH_GAME_BGM = L"Assets/sound/GameBGM.wav";
	const wchar_t* SOUND_FILEPATH_UP_TEMPO = L"Assets/sound/GameBGM_UpTempo.wav";
	const wchar_t* SOUND_FILEPATH_GAME_CLEAR = L"Assets/sound/GameClear.wav";
	const wchar_t* SOUND_FILEPATH_CURSOR_MOVE = L"Assets/sound/CursorMove.wav";
	const wchar_t* SOUND_FILEPATH_DECISION_BUTTON = L"Assets/sound/DecisionButton.wav";
	const wchar_t* SOUND_FILEPATH_COUNT_DOWN = L"Assets/sound/CountDown.wav";
	const wchar_t* SOUND_FILEPATH_MAGNET_POWER_CHANGE = L"Assets/sound/NSChange.wav";
	const wchar_t* SOUND_FILEPATH_GET_KEY = L"Assets/sound/KeyGet.wav";
	const wchar_t* SOUND_FILEPATH_BOX_OPEN = L"Assets/sound/BoxOpen.wav";
	const wchar_t* SOUND_FILEPATH_DEATH = L"Assets/sound/death.wav";
	const wchar_t* SOUND_FILEPATH_RESTART = L"Assets/sound/restart.wav";

	const char16_t* DEATH_EFFECT_FILE_PATH = u"Assets/effect/death.efk";	//死亡エフェクトのファイルパス
	const Vector3 EFFECT_SCALE = { 100.0f,100.0f,100.0f };			//死亡エフェクトの拡大率

	const Vector2 RENDER_TARGET_W1280H720 = { 1280.0f,720.0f };
	const int MIP_LEVEL1 = 1;
	const int RENDER_ARRAY_SIZE1 = 1;
	const int GAUSSIAN_BLUR_NUM = 4;
	const int BLUR_POWER = 10;
	const char* SPRITE_SHADER_FILE_PATH = "Assets/shader/sprite.fx";
	const char* SPRITE_SHADER_MONOCHROME_FILE_PATH = "Assets/shader/sample2D.fx";

	const int REST_INITIAL_TIME = 0;
	const int SPIN_LOCK_CRITERIA = 16;

	const float BUTTON_SIZE_MIN = 0.25f;
	const float BUTTON_SIZE_MAX = 0.275f;
	const float BUTTON_SCALE_ADD = 0.0005f;

	const Vector4 TRANSLUCENT_VALUE_HALF = { 1.0f,1.0f,1.0f,0.5f };
	const Vector4 TRANSLUCENT_VALUE_ONE_THIRD = { 1.0f,1.0f,1.0f,0.3f };
	const Vector4 TRANSLUCENT_VALUE_MAX = { 1.0f,1.0f,1.0f,1.0f };

	const float TEXT_SHADOW_THICKNESS = 1.0f;
}

template<typename Num>
int GetDigit(Num num) {

	int digit = 0;
	while (num >= 1) {
		num /= 10;
		digit++;
	}

	return digit;
}