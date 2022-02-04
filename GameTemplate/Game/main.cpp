#include "stdafx.h"
#include "system/system.h"
#include "TitleScene.h"
#include "Game.h"

void CreateInstance();

void InitBGMAndSE();

void ExecuteGaussianBlur(RenderContext& renderContext, PostEffect* postEffect);

GaussianBlur g_blur;
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//クラスのインスタンスを作成。
	CreateInstance();
	//BGMとSEを初期化。
	InitBGMAndSE();

	//ストップウォッチを作成
	Stopwatch stopWatch;

	//タイトル画面からスタート
	NewGO<TitleScene>(enPriority_Zeroth);

	
	RenderingEngine::GetRenderingEngine()->Init();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{

		//ストップウォッチの計測開始
		stopWatch.Start();
		//レンダリング開始。
		g_engine->BeginFrame();

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////

		//インスタンスの更新。
		RenderingEngine::GetRenderingEngine()->UpdateInstance();

		RenderingEngine::GetRenderingEngine()->Render();
		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////

		g_engine->EndFrame();

		//スピンロックを行う。
		int restTime = REST_INITIAL_TIME;
		do {
			stopWatch.Stop();
			restTime = SPIN_LOCK_CRITERIA - (int)stopWatch.GetElapsedMillisecond();
		} while (restTime > REST_INITIAL_TIME);


		//ストップウォッチの計測終了
		stopWatch.Stop();
		//デルタタイムをストップウォッチの計測時間から、計算する
		GameTime().PushFrameDeltaTime((float)stopWatch.GetElapsed());
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();

	return 0;
}

void CreateInstance() {

	//クラスのインスタンスを作成する。
	RenderingEngine::CreateRenderingEngine();
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();
	CSoundEngine::CreateInstance();
	CSoundEngine::GetInstance()->Init();
	LightManager::CreateInstance();
	SoundManager::CreateInstance();
	EffectEngine::CreateInstance();
	HUD::CreateHUD();
	Camera::CreateLightCamera();
}

void InitBGMAndSE() {

	//BGMの設定。
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_TITLE_BGM, enBGM_Title, true, SoundType::Type_BGM);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_GAME_BGM, enBGM_Game, true, SoundType::Type_BGM);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_UP_TEMPO, enBGM_GameUpTempo, true, SoundType::Type_BGM);

	//SEの設定。
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_GAME_CLEAR, enSE_GameClear, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_CURSOR_MOVE, enSE_CursolMove, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_DECISION_BUTTON, enSE_DecisionButton, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_COUNT_DOWN, enSE_CountDown, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_MAGNET_POWER_CHANGE, enSE_NSChange, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_GET_KEY, enSE_KeyGet, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_BOX_OPEN, enSE_BoxOpen, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_DEATH, enSE_Death, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_RESTART, enSE_ReStart, false, SoundType::Type_SE);
}

void ExecuteGaussianBlur(RenderContext& renderContext, PostEffect* postEffect) {

	//ガウシアンブラーを4回実行する
	for (int i = 0; i < GAUSSIAN_BLUR_NUM; i++) {

		postEffect->GetGaussianBlurSprite(i).ExecuteOnGPU(renderContext, BLUR_POWER);
	}

	//4枚のボケ画像を合成してメインレンダリングターゲットに加算合成
	renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetMainRenderTarget());

	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetMainRenderTarget());

	postEffect->GetFinalSprite().Draw(renderContext);

	renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetMainRenderTarget());
}
