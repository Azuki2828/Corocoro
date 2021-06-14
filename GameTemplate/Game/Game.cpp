#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "GameTime.h"
#include "MainCamera.h"
#include "Key.h"
#include "GameTime.h"
#include "SaveData.h"
#include "ResultScene.h"
#include "TreasureBox.h"
#include "DeathBlock.h"

namespace {
	constexpr int TIMER_VALUE[] = { 0,1,2,3,4 };
	const int SPRITE_NUM = 4;

	const wchar_t* FONT_TEXT = L"Time";
	const Vector2 FONT_POS = { -500.0f,310.0f };
	const float FONT_FLAME = 1.0f;

	const Vector2 SPRITE_WH = { 1000.0f, 1000.0f };
	const char* SPRITE_THREE_FILE_PATH = "Assets/image/3.dds";
	const char* SPRITE_TWO_FILE_PATH = "Assets/image/2.dds";
	const char* SPRITE_ONE_FILE_PATH = "Assets/image/1.dds";
	const char* SPRITE_GO_FILE_PATH = "Assets/image/GO.dds";

	const Vector2 SPRITE_TIME_10_POS = { -520.0f,310.0f };
	const Vector2 SPRITE_TIME_100_POS = { -552.0f,310.0f };

	const int TIME_DIGIT_10 = 10;
	const int TIME_DIGIT_100 = 100;
	const wchar_t* TIME_FORMAT = L"%2.1f";
	const float RESULT_SCENE_TIME = 3.0f;
	const char16_t* RESPAWN_EFFECT_FILE_PATH = u"Assets/effect/respawn.efk";

	const float HIT_TIMER_VALUE[] = { 2.5f,3.0f };					//タイマーの途中経過の定数
}

bool Game::Start() {


	//デバッグ用。ワイヤーフレーム表示をする

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	PhysicsWorld::GetInstance()->SetGravity(GRAVITY_VALUE);
	g_camera3D->SetUp(CAMERA_UP);

	//セーブを追加
	m_saveData = NewGO<SaveData>(enPriority_Zeroth, NAME_SAVE_DATA);
	m_saveData->Load();

	//カメラを生成。
	m_camera = NewGO<MainCamera>(enPriority_Zeroth, NAME_MAIN_CAMERA);

	//プレイヤーを生成。
	m_player = NewGO<Player>(enPriority_Zeroth, NAME_PLAYER);

	//地形を生成。
	m_backGround = NewGO<BackGround>(enPriority_Zeroth, NAME_BACK_GROUND);

	//フォントレンダーを生成
	m_fontRender = NewGO<FontRender>(enPriority_Second);

	//時間経過を表示
	m_fontRender->Init(FONT_TEXT, FONT_POS);	//場所
	m_fontRender->SetColor(Vector4::White);		//白色
	m_fontRender->SetShadowParam(true, FONT_FLAME, Vector4::Black);

	HUD::GetHUD()->Init(enSprite_3,SPRITE_THREE_FILE_PATH, SPRITE_WH.x, SPRITE_WH.y);
	HUD::GetHUD()->Deactivate(enSprite_3);
	HUD::GetHUD()->Init(enSprite_2,SPRITE_TWO_FILE_PATH, SPRITE_WH.x, SPRITE_WH.y);
	HUD::GetHUD()->Deactivate(enSprite_2);
	HUD::GetHUD()->Init(enSprite_1,SPRITE_ONE_FILE_PATH, SPRITE_WH.x, SPRITE_WH.y);
	HUD::GetHUD()->Deactivate(enSprite_1);
	HUD::GetHUD()->Init(enSprite_GO,SPRITE_GO_FILE_PATH, SPRITE_WH.x, SPRITE_WH.y);
	HUD::GetHUD()->Deactivate(enSprite_GO);

	return true;
}

Game::~Game()
{
	//セーブデータクラスを削除
	DeleteGO(m_saveData);
	m_saveData = nullptr;

	DeleteGO(m_player);
	m_player = nullptr;

	DeleteGO(m_backGround);
	m_backGround = nullptr;
	
	DeleteGO(m_camera);
	m_camera = nullptr;

	DeleteGO(m_fontRender);
	m_fontRender = nullptr;
}

void Game::Update() {

	//カメラのスクロールが終わってプレイヤーの視点になる。且つ、ワンショット再生させるためのフラグ。
	if (m_startSoundflg) {

		SoundManager::GetInstance()->Play(SE_CountDown);

		m_countDownSprite = true;
		m_startSoundflg = false;
	}

	//カウントダウンが鳴りだしたら、
	if (m_countDownSprite) {
		m_countDownTimer += GameTime().GameTimeFunc().GetFrameDeltaTime();
		//カウントダウンスプライトを表示。
		switch (static_cast<int>(m_countDownTimer)) {
		 case TIMER_VALUE[enData_Zeroth]:
			 //「3」表示
			 HUD::GetHUD()->Activate(enSprite_3);

			break;

		 case TIMER_VALUE[enData_First]:
			//「3」削除。
			 HUD::GetHUD()->Deactivate(enSprite_3);
			//「2」表示
			 HUD::GetHUD()->Activate(enSprite_2);
			

			break;

		 case TIMER_VALUE[enData_Second]:
			//「2」削除。
			 HUD::GetHUD()->Deactivate(enSprite_2);
			//「1」表示
			 HUD::GetHUD()->Activate(enSprite_1);

			

			break;

		 case TIMER_VALUE[enData_Third]:
			//「1」削除。
			 HUD::GetHUD()->Deactivate(enSprite_1);
			//「GO!!」表示
			 HUD::GetHUD()->Activate(enSprite_GO);
			 m_gameStartFlg = true;
			
			break;

		 case TIMER_VALUE[enData_Fourth]:
			 HUD::GetHUD()->Deactivate(enSprite_GO);

			 m_countDownSprite = false;

			break;
		}
	}

	wchar_t time[NAME_SIZE];
	if (m_gameStartFlg && !m_player->GetTreasureFlg()) {
		m_time += GameTime::GameTimeFunc().GetFrameDeltaTime();
	}


		//スイッチ文で使いたいのでキャスト。
		switch (static_cast<int>(m_time)) {
		
		case TIME_DIGIT_10:

			m_fontRender->SetPosition(SPRITE_TIME_10_POS);	//場所
			m_fontRender->SetColor(Vector4::White);	//白色

			break;

		//100秒経過したら、
		case TIME_DIGIT_100:

			m_fontRender->SetPosition(SPRITE_TIME_100_POS);	//場所
			m_fontRender->SetColor(Vector4::White);	//白色

			break;
		}
		//タイム文字表示
		swprintf_s(time, TIME_FORMAT, m_time);
		m_fontRender->SetText(time);


	if (m_player->GetTreasureFlg()) {			//ゴールしたら計測終了

		m_resultSceneTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

		if (m_resultScene == nullptr && m_resultSceneTime >= RESULT_SCENE_TIME) {
			//BGMを削除。
			SoundManager::GetInstance()->Release(BGM_GameUpTempo);

			//ゲームクリアのサウンドを再生。
			SoundManager::GetInstance()->Play(SE_GameClear);
			m_resultScene = NewGO<ResultScene>(enPriority_Zeroth, NAME_RESULT_SCENE);
			m_resultScene->SetStageNum(m_stageNum);
		}
	}

	if (m_hitPlayer)
	{
		//死ぬエフェクト再生と効果音
		if (!m_player->Getrespawn()) {
			m_playerPos = m_player->GetPosition();
			Effect* m_death = NewGO<Effect>(enPriority_Zeroth);
			m_death->Init(DEATH_EFFECT_FILE_PATH);
			m_death->SetScale(EFFECT_SCALE);
			m_player->Setrespawn(true);
			m_death->SetPosition(m_playerPos);
			m_deathActiveState = m_player->DeactivatePlayerModel();
			m_death->Play();
			m_deathFlg = true;

			SoundManager::GetInstance()->Play(SE_Death);
		}
		m_hitTimer += GameTime().GameTimeFunc().GetFrameDeltaTime();
		if (m_hitTimer >= HIT_TIMER_VALUE[enData_First])
		{
			SoundManager::GetInstance()->Play(SE_ReStart);
			m_player->Setrespawn(false);
			m_hitTimer = 0;
			m_backGround->SetStart(true);
			m_hitPlayer = false;
			m_respawnEfk = false;

		}
		else if (m_hitTimer >= HIT_TIMER_VALUE[enData_Zeroth]) {

			if (m_player->GetKeyFlg()) {
				m_key = FindGO<Key>(NAME_KEY);
				m_player->SetPosition(m_key->GetKeyPos());
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
			}
			else {
				m_player->SetPosition(m_player->GetStartPos());
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
			}
			if (!m_respawnEfk) {
				m_efkRespawn = NewGO<Effect>(enPriority_Zeroth);
				m_efkRespawn->Init(RESPAWN_EFFECT_FILE_PATH);
				m_efkRespawn->SetScale(EFFECT_SCALE);
				Vector3 effPos = m_player->GetPosition();
				m_efkRespawn->SetPosition(effPos);
				m_efkRespawn->Play();
				m_respawnEfk = true;
			}
		}
		else {
			m_player->SetPosition(m_playerPos);
		}
		m_player->ClearPower();

		if (m_efkRespawn != nullptr) {
			m_efkRespawn->SetPosition(m_player->GetPosition());
		}
	}
}