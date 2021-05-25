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
	Camera::CreateLightCamera();



	//タイトル画面からスタート
	NewGO<TitleScene>(0);

	DirectionLight* m_dirLight = NewGO<DirectionLight>(0, "mainLight");
	m_dirLight->SetLigDirection();
	m_dirLight->SetLigColor();

	//BGMの設定。
	SoundManager::GetInstance()->Init(L"Assets/sound/TitleBGM.wav", BGM_Title, true, SoundType::Type_BGM);
	SoundManager::GetInstance()->Init(L"Assets/sound/GameBGM.wav", BGM_Game, true, SoundType::Type_BGM);
	SoundManager::GetInstance()->Init(L"Assets/sound/GameBGM_UpTempo.wav", BGM_GameUpTempo, true, SoundType::Type_BGM);

	//SEの設定。
	SoundManager::GetInstance()->Init(L"Assets/sound/GameClear.wav", SE_GameClear, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(L"Assets/sound/CursorMove.wav", SE_CursolMove, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(L"Assets/sound/DecisionButton.wav", SE_DecisionButton, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(L"Assets/sound/CountDown.wav", SE_CountDown, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(L"Assets/sound/NSChange.wav", SE_NSChange, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(L"Assets/sound/KeyGet.wav", SE_KeyGet, false, SoundType::Type_SE);
	SoundManager::GetInstance()->Init(L"Assets/sound/BoxOpen.wav", SE_BoxOpen, false, SoundType::Type_SE);

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////

	RenderTarget::CreateMainRenderTarget();
	RenderTarget::GetMainRenderTarget()->Create(
		1280,
		720,
		1,
		1,
		// 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);


	//// 32ビットの浮動小数点のカラーバッファーを保持したメインレンダリングターゲットを作成する
	//RenderTarget mainRenderTarget;
	//mainRenderTarget.Create(
	//	1280,
	//	720,
	//	1,
	//	1,
	//	// 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
	//	DXGI_FORMAT_R32G32B32A32_FLOAT,
	//	DXGI_FORMAT_D32_FLOAT
	//);

	// 輝度抽出用のレンダリングターゲットを作成
	RenderTarget luminnceRenderTarget;

	// 解像度、ミップマップレベル
	luminnceRenderTarget.Create(
		1280,       // 解像度はメインレンダリングターゲットと同じ
		720,        // 解像度はメインレンダリングターゲットと同じ
		1,
		1,
		// 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	);


	PostEffect* m_postEffect = NewGO<PostEffect>(0);
	m_postEffect->InitLuminance(*RenderTarget::GetMainRenderTarget());
	m_postEffect->InitGaussianBlur(luminnceRenderTarget);

	// mainRenderTargetのテクスチャをフレームバッファーに貼り付けるためのスプライトを初期化する
	// スプライトの初期化オブジェクトを作成する
	SpriteInitData spriteInitData;

	// テクスチャはmainRenderTargetのカラーバッファー
	spriteInitData.m_textures[0] = &RenderTarget::GetMainRenderTarget()->GetRenderTargetTexture();
	spriteInitData.m_width = 1280;
	spriteInitData.m_height = 720;

	// モノクロ用のシェーダーを指定する
	spriteInitData.m_fxFilePath = "Assets/shader/sample2D.fx";

	// 初期化オブジェクトを使って、スプライトを初期化する
	Sprite copyToFrameBufferSprite;
	copyToFrameBufferSprite.Init(spriteInitData);

	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//step-1 シャドウマップ描画用のレンダリングターゲットを作成する。

	RenderTarget::CreateShadowMap();
	RenderTarget::CreateZPrepassRenderTarget();

	
	g_blur.Init(&RenderTarget::GetZPrepassRenderTarget()->GetRenderTargetTexture());
	////影描画用のライトカメラを作成する。
	//Camera lightCamera;
	////カメラの位置を設定。これはライトの位置。
	//lightCamera.SetPosition(0, 500, 0);
	////カメラの注視点を設定。これがライトが照らしている場所。
	//lightCamera.SetTarget(0, 0, 0);
	////上方向を設定。今回はライトが真下を向いているので、X方向を上にしている。
	//lightCamera.SetUp(1, 0, 0);
	////ライトビュープロジェクション行列を計算している。
	//lightCamera.Update();
/*	Effect* laserEffect = nullptr;
	laserEffect = NewGO<Effect>(0);
	laserEffect->Init(u"Assets/effect/laser.efk");
	laserEffect->SetScale({ 15.0f,15.0f,15.0f });*/
	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//if (g_pad[0]->IsTrigger(enButtonA)) {
		//	//再生開始。
		//	laserEffect->Play();

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
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		EffectEngine::GetInstance()->Draw();

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

		for (int i = 0; i < 4; i++) {

			m_postEffect->GetGaussianBlurSprite(i).ExecuteOnGPU(renderContext, 10);
		}

		//gaussianBlur[0].ExecuteOnGPU(renderContext, 10);
		//gaussianBlur[1].ExecuteOnGPU(renderContext, 10);
		//gaussianBlur[2].ExecuteOnGPU(renderContext, 10);
		//gaussianBlur[3].ExecuteOnGPU(renderContext, 10);

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

		//// ライトの強さを変更する
		//light.directionalLight[0].color.x += g_pad[0]->GetLStickXF() * 0.5f;
		//light.directionalLight[0].color.y += g_pad[0]->GetLStickXF() * 0.5f;
		//light.directionalLight[0].color.z += g_pad[0]->GetLStickXF() * 0.5f;
		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}