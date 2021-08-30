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

enum GameObjectList {
	enGameObject_Player_N = 1,
	enGameObject_Player_S,
	enGameObject_Key,
	enGameObject_Door,
	enGameObject_TreasureBox,
	enGameObject_DeathBlock,
	enGameObject_Seesaw,
	enGameObject_Magnet,

	enGameObject_Num
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
	enSprite_TimeBack,
	enSprite_YesKey,
	enSprite_NoKey,

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

	const int PAD_0 = 0;
	const int NAME_SIZE = 256;										//名前の最大のサイズ
	const int TEXT_SIZE = 64;										//テキストの標準サイズ
	const float TEXT_BIT_SIZE = 32.0f;								//テキストのビットサイズ
	const float CAMERA_ROT_VALUE = -2.0f;							//カメラの１フレーム当たりの回転数

	const float REVERSE_VECTOR = -1.0f;								//ベクトル反転の定数

	const Vector3 GRAVITY_VALUE = { 0.0f,-300.0f,0.0f };			//標準の重力
	const Vector3 GRAVITY_REVERSE_VALUE = { 0.0f,300.0f,0.0f };		//ステージ反転したときの重力

	const Vector3 CAMERA_UP = { 0.0f,1.0f,0.0f };					//カメラの標準の上方向

	const char* NAME_PLAYER = "player";								//プレイヤークラスの名前
	const char* NAME_GAME = "game";									//ゲームクラスの名前
	const char* NAME_BACK_GROUND = "backGround";					//背景モデルクラスの名前
	const char* NAME_MAIN_CAMERA = "mainCamera";					//メインカメラクラスの名前
	const char* NAME_GAME_LEVEL2D = "gameLevel2D";					//ゲームレベル2Dクラスの名前
	const char* NAME_TITLE_LEVEL2D = "titleLevel2D";				//タイトルレベル2Dクラスの名前
	const char* NAME_KEY = "key";									//鍵クラスの名前
	const char* NAME_STAGE_SELECT = "stageSelect";					//ステージセレクトクラスの名前
	const char* NAME_RULE_SCENE = "ruleScene";						//ルール説明クラスの名前
	const char* NAME_TREASURE_BOX = "treasureBox";					//宝箱クラスの名前
	const char* NAME_SAVE_DATA = "saveData";						//セーブクラスの名前
	const char* NAME_RESULT_SCENE = "resultScene";					//リザルトクラスの名前
	const char* NAME_DIRECTION_LIGHT = "mainLight";					//メインとなるディレクションライトクラスの名前
	const char* NAME_RESULT_LEVEL2D = "resultLevel2D";				//リザルトレベル2Dクラスの名前
	const char* NAME_STAGE_SELECT_LEVEL2D = "StageSelectLevel2D";	//ステージセレクトレベル2Dクラスの名前
	const char* NAME_RULE_LEVEL2D = "ruleLevel2D";

	const wchar_t* SOUND_FILEPATH_TITLE_BGM = L"Assets/sound/TitleBGM.wav";					//タイトルBGM
	const wchar_t* SOUND_FILEPATH_GAME_BGM = L"Assets/sound/GameBGM.wav";					//ゲーム中のBGM
	const wchar_t* SOUND_FILEPATH_UP_TEMPO = L"Assets/sound/GameBGM_UpTempo.wav";			//ステージ反転した後のBGM
	const wchar_t* SOUND_FILEPATH_GAME_CLEAR = L"Assets/sound/GameClear.wav";				//ゲームクリア時のBGM
	const wchar_t* SOUND_FILEPATH_CURSOR_MOVE = L"Assets/sound/CursorMove.wav";				//選択が変わった時のSE
	const wchar_t* SOUND_FILEPATH_DECISION_BUTTON = L"Assets/sound/DecisionButton.wav";		//決定ボタンを押したときのSE
	const wchar_t* SOUND_FILEPATH_COUNT_DOWN = L"Assets/sound/CountDown.wav";				//カウントダウンのSE
	const wchar_t* SOUND_FILEPATH_MAGNET_POWER_CHANGE = L"Assets/sound/NSChange.wav";		//磁極変換したときのSE
	const wchar_t* SOUND_FILEPATH_GET_KEY = L"Assets/sound/KeyGet.wav";						//鍵取得時のSE
	const wchar_t* SOUND_FILEPATH_BOX_OPEN = L"Assets/sound/BoxOpen.wav";					//宝箱が開いたときのSE
	const wchar_t* SOUND_FILEPATH_DEATH = L"Assets/sound/death.wav";						//死んだときのSE
	const wchar_t* SOUND_FILEPATH_RESTART = L"Assets/sound/restart.wav";					//リスポーンしたときのSE

	const char16_t* DEATH_EFFECT_FILE_PATH = u"Assets/effect/death.efk";	//死亡エフェクトのファイルパス
	const Vector3 EFFECT_SCALE = { 100.0f,100.0f,100.0f };					//死亡エフェクトの拡大率

	const Vector2 RENDER_TARGET_W1280H720 = { 1280.0f,720.0f };						//レンダリングターゲットで使用する幅と高さ
	const int MIP_LEVEL1 = 1;														//レンダリングターゲットで使用するミップマップレベル
	const int RENDER_ARRAY_SIZE1 = 1;												//レンダリングターゲットで使用するテクスチャ配列のサイズ
	const int GAUSSIAN_BLUR_NUM = 4;												//ガウシアンブラーをかける回数
	const int BLUR_POWER = 10;														//ブラーの強さ
	const char* SPRITE_SHADER_FILE_PATH = "Assets/shader/defferdLighting.fx";		//スプライトシェーダーのファイルパス
	const char* SPRITE_SHADER_MONOCHROME_FILE_PATH = "Assets/shader/sample2D.fx";	//モノクロ表示用のシェーダーのファイルパス
	const char* HUD_FILE_PATH = "Assets/shader/sprite.fx";

	const int INITIALIZE_TIME = 0;
	const int REST_INITIAL_TIME = 0;		//スピンロック時の待ちタイムの初期時間
	const int SPIN_LOCK_CRITERIA = 16;		//スピンロック時の基準となる時間

	const float BACK_BUTTON_SIZE_MIN = 0.225f;				//「戻る」ボタンの最小拡大率
	const float BACK_BUTTON_SIZE_MAX = 0.25f;				//「戻る」ボタンの最大拡大率
	const float DECISION_BUTTON_SIZE_MIN = 0.175f;			//「決定」ボタンの最小拡大率
	const float DECISION_BUTTON_SIZE_MAX = 0.2f;			//「決定」ボタンの最大拡大率
	const float TITLE_SELECT_BUTTON_SCALE_MIN = 0.2f;		//タイトル画面のボタンの最小拡大率
	const float TITLE_SELECT_BUTTON_SCALE_MAX = 0.225f;		//タイトル画面のボタンの最大拡大率
	const float BUTTON_SCALE_ADD = 0.0005f;					//１フレームあたりのボタン拡大縮小率

	const Vector4 TRANSLUCENT_VALUE_HALF = { 1.0f,1.0f,1.0f,0.5f };			//透明率50%
	const Vector4 TRANSLUCENT_VALUE_ONE_THIRD = { 1.0f,1.0f,1.0f,0.3f };	//透明率70%
	const Vector4 TRANSLUCENT_VALUE_MAX = { 1.0f,1.0f,1.0f,1.0f };			//透明率0%

	const float TEXT_SHADOW_THICKNESS = 1.0f;					//テキストの影（枠線）の厚さ

	const Vector3 SCALE_VALUE_HALF = { 0.5f,0.5f,0.5f };		//拡大率50%
	const Vector3 SCALE_VALUE_A_TENTH = { 0.1f,0.1f,0.1f };		//拡大率10%
	const Vector3 SCALE_VALUE_A_FIFTH = { 0.2f,0.2f,0.2f };		//拡大率20%
}

/**
 * @brief 数字の桁数を取得する関数
 * @tparam Num テンプレート
 * @param num 桁数を確かめたい数字
 * @return 桁数
*/
template<typename Num>
int GetDigit(Num num) {

	int digit = 0;
	while (num >= 1) {
		num /= 10;
		digit++;
	}

	return digit;
}