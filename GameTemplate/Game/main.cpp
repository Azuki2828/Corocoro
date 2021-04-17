#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Background2.h"
#include "PhysicsBall.h"
#include "Seesaw.h"
#include "PostEffect.h"

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
	Camera::CreateLightCamera();

	//NewGO<Background2>(0);
	//NewGO<PhysicsBall>(0);
	//NewGO<Seesaw>(0);
	NewGO<Game>(0,"game");

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

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();
		

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////

		//////////////////////////////////////
		// ここから絵を描くコードを記述する
		//////////////////////////////////////

		////シャドウマップにレンダリング。
		////レンダリングターゲットをシャドウマップに変更する。
		//renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetShadowMap());
		//renderContext.SetRenderTargetAndViewport(*RenderTarget::GetShadowMap());
		//renderContext.ClearRenderTargetView(*RenderTarget::GetShadowMap());
		//
		////書き込み完了待ち。
		//renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetShadowMap());

		////通常レンダリング。
		////レンダリングターゲットをフレームバッファに戻す。
		//renderContext.SetRenderTarget(
		//	g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		//	g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		//);
		//renderContext.SetViewport(g_graphicsEngine->GetFrameBufferViewport());

		//// レンダリングターゲットをmainRenderTargetに変更する
		//// レンダリングターゲットとして利用できるまで待つ
		//renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		//// レンダリングターゲットを設定
		//renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		//// レンダリングターゲットをクリア
		//renderContext.ClearRenderTargetView(mainRenderTarget);

		//// mainRenderTargetに各種モデルを描画する
		//plModel.Draw(renderContext);
		
		GameObjectManager::GetInstance()->ExecuteUpdate();
		//物理ワールドの更新。
		PhysicsWorld::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		//LightManagerの更新。
		LightManager::GetInstance()->Update();

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