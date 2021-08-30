#pragma once

//////////////////////////////////////////////////
///�@�Q�ȏ�̃N���X�Ŏg���萔���܂Ƃ߂Ă���@///
//////////////////////////////////////////////////



/**
 * @brief �D��x�BenPriority_Zeroth���ł���ɕ`�悳���B
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
 * @brief �v�f�ɃA�N�Z�X����Ƃ��Ɏg���ԍ�
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
 * @brief �X�e�[�W�ԍ�
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
 * @brief �X�v���C�g�ԍ�
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
 * @brief �T�E���h���X�g
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
 * @brief HUD�ɓo�^����Ă���X�v���C�g
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
 * @brief ���Δԍ�
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
	const int NAME_SIZE = 256;										//���O�̍ő�̃T�C�Y
	const int TEXT_SIZE = 64;										//�e�L�X�g�̕W���T�C�Y
	const float TEXT_BIT_SIZE = 32.0f;								//�e�L�X�g�̃r�b�g�T�C�Y
	const float CAMERA_ROT_VALUE = -2.0f;							//�J�����̂P�t���[��������̉�]��

	const float REVERSE_VECTOR = -1.0f;								//�x�N�g�����]�̒萔

	const Vector3 GRAVITY_VALUE = { 0.0f,-300.0f,0.0f };			//�W���̏d��
	const Vector3 GRAVITY_REVERSE_VALUE = { 0.0f,300.0f,0.0f };		//�X�e�[�W���]�����Ƃ��̏d��

	const Vector3 CAMERA_UP = { 0.0f,1.0f,0.0f };					//�J�����̕W���̏����

	const char* NAME_PLAYER = "player";								//�v���C���[�N���X�̖��O
	const char* NAME_GAME = "game";									//�Q�[���N���X�̖��O
	const char* NAME_BACK_GROUND = "backGround";					//�w�i���f���N���X�̖��O
	const char* NAME_MAIN_CAMERA = "mainCamera";					//���C���J�����N���X�̖��O
	const char* NAME_GAME_LEVEL2D = "gameLevel2D";					//�Q�[�����x��2D�N���X�̖��O
	const char* NAME_TITLE_LEVEL2D = "titleLevel2D";				//�^�C�g�����x��2D�N���X�̖��O
	const char* NAME_KEY = "key";									//���N���X�̖��O
	const char* NAME_STAGE_SELECT = "stageSelect";					//�X�e�[�W�Z���N�g�N���X�̖��O
	const char* NAME_RULE_SCENE = "ruleScene";						//���[�������N���X�̖��O
	const char* NAME_TREASURE_BOX = "treasureBox";					//�󔠃N���X�̖��O
	const char* NAME_SAVE_DATA = "saveData";						//�Z�[�u�N���X�̖��O
	const char* NAME_RESULT_SCENE = "resultScene";					//���U���g�N���X�̖��O
	const char* NAME_DIRECTION_LIGHT = "mainLight";					//���C���ƂȂ�f�B���N�V�������C�g�N���X�̖��O
	const char* NAME_RESULT_LEVEL2D = "resultLevel2D";				//���U���g���x��2D�N���X�̖��O
	const char* NAME_STAGE_SELECT_LEVEL2D = "StageSelectLevel2D";	//�X�e�[�W�Z���N�g���x��2D�N���X�̖��O
	const char* NAME_RULE_LEVEL2D = "ruleLevel2D";

	const wchar_t* SOUND_FILEPATH_TITLE_BGM = L"Assets/sound/TitleBGM.wav";					//�^�C�g��BGM
	const wchar_t* SOUND_FILEPATH_GAME_BGM = L"Assets/sound/GameBGM.wav";					//�Q�[������BGM
	const wchar_t* SOUND_FILEPATH_UP_TEMPO = L"Assets/sound/GameBGM_UpTempo.wav";			//�X�e�[�W���]�������BGM
	const wchar_t* SOUND_FILEPATH_GAME_CLEAR = L"Assets/sound/GameClear.wav";				//�Q�[���N���A����BGM
	const wchar_t* SOUND_FILEPATH_CURSOR_MOVE = L"Assets/sound/CursorMove.wav";				//�I�����ς��������SE
	const wchar_t* SOUND_FILEPATH_DECISION_BUTTON = L"Assets/sound/DecisionButton.wav";		//����{�^�����������Ƃ���SE
	const wchar_t* SOUND_FILEPATH_COUNT_DOWN = L"Assets/sound/CountDown.wav";				//�J�E���g�_�E����SE
	const wchar_t* SOUND_FILEPATH_MAGNET_POWER_CHANGE = L"Assets/sound/NSChange.wav";		//���ɕϊ������Ƃ���SE
	const wchar_t* SOUND_FILEPATH_GET_KEY = L"Assets/sound/KeyGet.wav";						//���擾����SE
	const wchar_t* SOUND_FILEPATH_BOX_OPEN = L"Assets/sound/BoxOpen.wav";					//�󔠂��J�����Ƃ���SE
	const wchar_t* SOUND_FILEPATH_DEATH = L"Assets/sound/death.wav";						//���񂾂Ƃ���SE
	const wchar_t* SOUND_FILEPATH_RESTART = L"Assets/sound/restart.wav";					//���X�|�[�������Ƃ���SE

	const char16_t* DEATH_EFFECT_FILE_PATH = u"Assets/effect/death.efk";	//���S�G�t�F�N�g�̃t�@�C���p�X
	const Vector3 EFFECT_SCALE = { 100.0f,100.0f,100.0f };					//���S�G�t�F�N�g�̊g�嗦

	const Vector2 RENDER_TARGET_W1280H720 = { 1280.0f,720.0f };						//�����_�����O�^�[�Q�b�g�Ŏg�p���镝�ƍ���
	const int MIP_LEVEL1 = 1;														//�����_�����O�^�[�Q�b�g�Ŏg�p����~�b�v�}�b�v���x��
	const int RENDER_ARRAY_SIZE1 = 1;												//�����_�����O�^�[�Q�b�g�Ŏg�p����e�N�X�`���z��̃T�C�Y
	const int GAUSSIAN_BLUR_NUM = 4;												//�K�E�V�A���u���[���������
	const int BLUR_POWER = 10;														//�u���[�̋���
	const char* SPRITE_SHADER_FILE_PATH = "Assets/shader/defferdLighting.fx";		//�X�v���C�g�V�F�[�_�[�̃t�@�C���p�X
	const char* SPRITE_SHADER_MONOCHROME_FILE_PATH = "Assets/shader/sample2D.fx";	//���m�N���\���p�̃V�F�[�_�[�̃t�@�C���p�X
	const char* HUD_FILE_PATH = "Assets/shader/sprite.fx";

	const int INITIALIZE_TIME = 0;
	const int REST_INITIAL_TIME = 0;		//�X�s�����b�N���̑҂��^�C���̏�������
	const int SPIN_LOCK_CRITERIA = 16;		//�X�s�����b�N���̊�ƂȂ鎞��

	const float BACK_BUTTON_SIZE_MIN = 0.225f;				//�u�߂�v�{�^���̍ŏ��g�嗦
	const float BACK_BUTTON_SIZE_MAX = 0.25f;				//�u�߂�v�{�^���̍ő�g�嗦
	const float DECISION_BUTTON_SIZE_MIN = 0.175f;			//�u����v�{�^���̍ŏ��g�嗦
	const float DECISION_BUTTON_SIZE_MAX = 0.2f;			//�u����v�{�^���̍ő�g�嗦
	const float TITLE_SELECT_BUTTON_SCALE_MIN = 0.2f;		//�^�C�g����ʂ̃{�^���̍ŏ��g�嗦
	const float TITLE_SELECT_BUTTON_SCALE_MAX = 0.225f;		//�^�C�g����ʂ̃{�^���̍ő�g�嗦
	const float BUTTON_SCALE_ADD = 0.0005f;					//�P�t���[��������̃{�^���g��k����

	const Vector4 TRANSLUCENT_VALUE_HALF = { 1.0f,1.0f,1.0f,0.5f };			//������50%
	const Vector4 TRANSLUCENT_VALUE_ONE_THIRD = { 1.0f,1.0f,1.0f,0.3f };	//������70%
	const Vector4 TRANSLUCENT_VALUE_MAX = { 1.0f,1.0f,1.0f,1.0f };			//������0%

	const float TEXT_SHADOW_THICKNESS = 1.0f;					//�e�L�X�g�̉e�i�g���j�̌���

	const Vector3 SCALE_VALUE_HALF = { 0.5f,0.5f,0.5f };		//�g�嗦50%
	const Vector3 SCALE_VALUE_A_TENTH = { 0.1f,0.1f,0.1f };		//�g�嗦10%
	const Vector3 SCALE_VALUE_A_FIFTH = { 0.2f,0.2f,0.2f };		//�g�嗦20%
}

/**
 * @brief �����̌������擾����֐�
 * @tparam Num �e���v���[�g
 * @param num �������m���߂�������
 * @return ����
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