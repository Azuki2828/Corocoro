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
	constexpr int TIMER_VALUE[] = { 0,1,2,3,4 };		//カウントダウン時に使用する値
	const int SPRITE_NUM = 4;							//スプライトの数

	const wchar_t* FONT_TEXT = L"Time";				//"Time"テキスト
	const Vector2 FONT_POS = { -500.0f,310.0f };	//"Time"の座標
	const float FONT_FLAME = 1.0f;					//"Time"の影の厚さ

	const Vector2 SPRITE_WH = { 1000.0f, 1000.0f };				//カウントダウンスプライトの幅と高さ
	const char* SPRITE_THREE_FILE_PATH = "Assets/image/3.dds";	//"3"スプライトのファイルパス
	const char* SPRITE_TWO_FILE_PATH = "Assets/image/2.dds";	//"2"スプライトのファイルパス
	const char* SPRITE_ONE_FILE_PATH = "Assets/image/1.dds";	//"1"スプライトのファイルパス
	const char* SPRITE_GO_FILE_PATH = "Assets/image/GO.dds";	//"GO"スプライトのファイルパス

	const Vector2 SPRITE_TIME_10_POS = { -488.0f,310.0f };		
	const Vector2 SPRITE_TIME_100_POS = { -552.0f,310.0f };

	const wchar_t* TIME_FORMAT = L"%2.1f";		//タイム表示のフォーマット
	const float RESULT_SCENE_TIME = 3.0f;		//クリアしてからリザルトシーンに移るまでの時間

	const char16_t* RESPAWN_EFFECT_FILE_PATH = u"Assets/effect/respawn.efk";	//リスポーンエフェクトのファイルパス

	const float HIT_TIMER_VALUE[] = { 2.5f,3.0f };		//タイマーの途中経過の定数
}

bool Game::Start() {


	//デバッグ用。ワイヤーフレーム表示をする

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//重力を通常のものに設定する。
	PhysicsWorld::GetInstance()->SetGravity(GRAVITY_VALUE);
	//カメラの上方向を通常のものにする。
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


	//カウントダウンスプライトを初期化して、非表示状態にしておく。
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
	//プレイヤークラスを削除
	DeleteGO(m_player);
	m_player = nullptr;
	//背景モデルクラスを削除
	DeleteGO(m_backGround);
	m_backGround = nullptr;
	//メインカメラクラスを削除
	DeleteGO(m_camera);
	m_camera = nullptr;
	//フォントレンダークラスを削除
	DeleteGO(m_fontRender);
	m_fontRender = nullptr;
}

void Game::Update() {

	if (m_startSoundflg) {
		//カウントダウンSEを一回だけ再生する
		SoundManager::GetInstance()->Play(enSE_CountDown);

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

	//ゲーム中の時間を加算。
	if (m_gameStartFlg && !m_player->GetTreasureFlg()) {
		m_time += GameTime::GameTimeFunc().GetFrameDeltaTime();
	}

	//時間のUIの座標と色を設定。
	m_fontRender->SetPosition({ SPRITE_TIME_10_POS.x - TEXT_BIT_SIZE * GetDigit(m_time),SPRITE_TIME_10_POS.y });
	m_fontRender->SetColor(Vector4::White);

		////スイッチ文で使いたいのでキャスト。
		//switch (static_cast<int>(m_time)) {
		//
		//case TIME_DIGIT_10:

		//	m_fontRender->SetPosition(SPRITE_TIME_10_POS);	//場所
		//	m_fontRender->SetColor(Vector4::White);	//白色

		//	break;

		////100秒経過したら、
		//case TIME_DIGIT_100:

		//	m_fontRender->SetPosition(SPRITE_TIME_100_POS);	//場所
		//	m_fontRender->SetColor(Vector4::White);	//白色

		//	break;
		//}

		//タイム文字表示
		swprintf_s(time, TIME_FORMAT, m_time);
		m_fontRender->SetText(time);

	//ゴールしたら計測終了
	if (m_player->GetTreasureFlg()) {

		//リザルトに移行するまでの時間を測る。
		m_resultSceneTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

		//リザルトに移行。
		if (m_resultScene == nullptr && m_resultSceneTime >= RESULT_SCENE_TIME) {
			//BGMを削除。
			SoundManager::GetInstance()->Release(enBGM_GameUpTempo);

			//ゲームクリアのサウンドを再生。
			SoundManager::GetInstance()->Play(enSE_GameClear);
			m_resultScene = NewGO<ResultScene>(enPriority_Zeroth, NAME_RESULT_SCENE);
			m_resultScene->SetStageNum(m_stageNum);
		}
	}

	if (m_hitPlayer)
	{
		static Vector3 playerPos = Vector3::Zero;
		//プレイヤーが死亡してからの時間を加算する。
		m_hitTimer += GameTime().GameTimeFunc().GetFrameDeltaTime();

		//死亡エフェクト再生と効果音
		if (!m_player->GetRespawn()) {
			//プレイヤーの座標を取得。
			playerPos = m_player->GetPosition();

			//死亡エフェクトを再生。
			Effect* m_death = NewGO<Effect>(enPriority_Zeroth);
			m_death->Init(DEATH_EFFECT_FILE_PATH);
			m_death->SetScale(EFFECT_SCALE);
			m_death->SetPosition(playerPos);
			m_death->Play();

			//プレイヤーをリスポーンさせる
			m_player->SetRespawn(true);
			m_deathActiveState = m_player->DeactivatePlayerModel();
			m_deathFlg = true;

			//死亡SEを再生。
			SoundManager::GetInstance()->Play(enSE_Death);
		}
		if (m_hitTimer >= HIT_TIMER_VALUE[enData_First])
		{
			//プレイヤー復帰SEを再生。
			SoundManager::GetInstance()->Play(enSE_ReStart);

			//プレイヤーをリスポーンさせる。
			m_player->SetRespawn(false);
			m_hitTimer = INITIALIZE_TIME;

			//シーソーを初期状態に戻す。
			m_backGround->SetStart(true);

			//ヒットフラグをfalseにする。
			m_hitPlayer = false;
			m_respawnEfk = false;


			//一時的な、プレイヤーから取得した座標を初期化する。
			playerPos = Vector3::Zero;
		}
		else if (m_hitTimer >= HIT_TIMER_VALUE[enData_Zeroth]) {

			//鍵を取得していたら
			if (m_player->GetKeyFlg()) {
				m_key = FindGO<Key>(NAME_KEY);
				//プレイヤーの復帰位置を鍵と場所と同じにする。
				m_player->SetPosition(m_key->GetKeyPos());
				//プレイヤーを有効にする。
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
			}
			else {
				//プレイヤーの復帰位置をスタート地点にする。
				m_player->SetPosition(m_player->GetStartPos());
				//プレイヤーを有効にする。
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
			}
			//復帰エフェクトが再生されていないなら
			if (!m_respawnEfk) {
				//復帰位置に復帰エフェクトを再生する。
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
			//剛体の影響を受けないようにするためにプレイヤーの座標を今の座標にする。
			m_player->SetPosition(playerPos);
		}
		//プレイヤーの現在の力を無効にする。
		m_player->ClearPower();

		//復帰エフェクトの再生場所をプレイヤーに座標で更新する。
		if (m_efkRespawn != nullptr) {
			m_efkRespawn->SetPosition(m_player->GetPosition());
		}
	}
}