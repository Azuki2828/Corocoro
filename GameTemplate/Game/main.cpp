#include "stdafx.h"
#include "system/system.h"
#include "TitleScene.h"
#include "PostEffect.h"
#include "Game.h"


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

	//ゲームオブジェクトマネージャーのインスタンスを作成する。
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();
	CSoundEngine::CreateInstance();
	CSoundEngine::GetInstance()->Init(); 
	LightManager::CreateInstance();
	SoundManager::CreateInstance();
	EffectEngine::CreateInstance();
	HUD::CreateHUD();

	Camera::CreateLightCamera();

	Stopwatch stopWatch;

	//タイトル画面からスタート
	NewGO<TitleScene>(enPriority_Zeroth);

	DirectionLight* m_dirLight = NewGO<DirectionLight>(enPriority_Zeroth, NAME_DIRECTION_LIGHT);
	m_dirLight->SetLigDirection();
	m_dirLight->SetLigColor();

	//BGMの設定。
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_TITLE_BGM, BGM_Title, true, SoundType::Type_BGM);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_GAME_BGM, BGM_Game, true, SoundType::Type_BGM);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_UP_TEMPO, BGM_GameUpTempo, true, SoundType::Type_BGM);

	//SEの設定。
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_GAME_CLEAR, SE_GameClear, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_CURSOR_MOVE, SE_CursolMove, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_DECISION_BUTTON, SE_DecisionButton, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_COUNT_DOWN, SE_CountDown, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_MAGNET_POWER_CHANGE, SE_NSChange, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_GET_KEY, SE_KeyGet, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_BOX_OPEN, SE_BoxOpen, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_DEATH, SE_Death, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(SOUND_FILEPATH_RESTART, SE_ReStart, false, SoundType::Type_SE);

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////

	RenderTarget::CreateMainRenderTarget();
	RenderTarget::GetMainRenderTarget()->Create(
		RENDER_TARGET_W1280H720.x,
		RENDER_TARGET_W1280H720.y,
		MIP_LEVEL1,
		RENDER_ARRAY_SIZE1,
		// 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);

	// 輝度抽出用のレンダリングターゲットを作成
	RenderTarget luminnceRenderTarget;

	// 解像度、ミップマップレベル
	luminnceRenderTarget.Create(
		RENDER_TARGET_W1280H720.x,       // 解像度はメインレンダリングターゲットと同じ
		RENDER_TARGET_W1280H720.y,        // 解像度はメインレンダリングターゲットと同じ
		MIP_LEVEL1,
		RENDER_ARRAY_SIZE1,
		// 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);


	PostEffect* m_postEffect = NewGO<PostEffect>(enPriority_Zeroth);
	m_postEffect->InitLuminance(*RenderTarget::GetMainRenderTarget());
	m_postEffect->InitGaussianBlur(luminnceRenderTarget);

	// mainRenderTargetのテクスチャをフレームバッファーに貼り付けるためのスプライトを初期化する
	// スプライトの初期化オブジェクトを作成する
	SpriteInitData spriteInitData;

	// テクスチャはmainRenderTargetのカラーバッファー
	spriteInitData.m_textures[enData_Zeroth] = &RenderTarget::GetMainRenderTarget()->GetRenderTargetTexture();
	spriteInitData.m_width = RENDER_TARGET_W1280H720.x;
	spriteInitData.m_height = RENDER_TARGET_W1280H720.y;

	// モノクロ用のシェーダーを指定する
	spriteInitData.m_fxFilePath = SPRITE_SHADER_MONOCHROME_FILE_PATH;

	// 初期化オブジェクトを使って、スプライトを初期化する
	Sprite copyToFrameBufferSprite;
	copyToFrameBufferSprite.Init(spriteInitData);

	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//step-1 シャドウマップ描画用のレンダリングターゲットを作成する。

	RenderTarget::CreateShadowMap();
	RenderTarget::CreateZPrepassRenderTarget();

	
	g_blur.Init(&RenderTarget::GetZPrepassRenderTarget()->GetRenderTargetTexture());

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

		GameObjectManager::GetInstance()->ExecuteUpdate();
		//物理ワールドの更新。
		PhysicsWorld::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
		EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
		SoundManager::GetInstance()->Update();
		HUD::GetHUD()->Update();


		GameObjectManager::GetInstance()->ExecuteRender(renderContext);


		EffectEngine::GetInstance()->Draw();
		HUD::GetHUD()->Draw(renderContext);
		GameObjectManager::GetInstance()->ExecuteFontRender(renderContext);



		//LightManagerの更新。
		LightManager::GetInstance()->Update();
		//laserEffect.Update();

		// レンダリングターゲットへの書き込み終了待ち
		renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetMainRenderTarget());

		// 輝度抽出
		// 輝度抽出用のレンダリングターゲットに変更
		renderContext.WaitUntilToPossibleSetRenderTarget(luminnceRenderTarget);

		// レンダリングターゲットを設定
		renderContext.SetRenderTargetAndViewport(luminnceRenderTarget);

		// レンダリングターゲットをクリア
		renderContext.ClearRenderTargetView(luminnceRenderTarget);

		// 輝度抽出を行う
		m_postEffect->GetLuminanceSprite().Draw(renderContext);

		// レンダリングターゲットへの書き込み終了待ち
		renderContext.WaitUntilFinishDrawingToRenderTarget(luminnceRenderTarget);

		// step-3 ガウシアンブラーを4回実行する

		for (int i = 0; i < GAUSSIAN_BLUR_NUM; i++) {

			m_postEffect->GetGaussianBlurSprite(i).ExecuteOnGPU(renderContext, BLUR_POWER);
		}

		// step-4 4枚のボケ画像を合成してメインレンダリングターゲットに加算合成

		renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetMainRenderTarget());

		renderContext.SetRenderTargetAndViewport(*RenderTarget::GetMainRenderTarget());

		m_postEffect->GetFinalSprite().Draw(renderContext);

		renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetMainRenderTarget());


		// メインレンダリングターゲットの絵をフレームバッファーにコピー
		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		copyToFrameBufferSprite.Draw(renderContext);

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////

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