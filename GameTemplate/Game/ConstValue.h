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

//ステージ番号
enum StageNum {
	Stage_One,
	Stage_Two,
	Stage_Three,
	Stage_Four
};

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

enum SoundList {
	BGM_Title,
	BGM_Game,
	BGM_GameUpTempo,
	SE_GameClear,
	SE_CursolMove,
	SE_DecisionButton,
	SE_CountDown,
	SE_NSChange,
	SE_KeyGet,
	SE_BoxOpen,
	SE_Death,
	SE_ReStart,

	Sound_Num
};

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

	enSprite_HUDNum

};

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
}