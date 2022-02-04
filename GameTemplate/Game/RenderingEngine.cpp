#include "stdafx.h"
#include "RenderingEngine.h"

RenderingEngine* RenderingEngine::m_renderingEngine = nullptr;

void RenderingEngine::Init() {

	//レンダリングターゲットの生成。
	CreateRenderingTarget();
	g_blur.Init(&RenderTarget::GetZPrepassRenderTarget()->GetRenderTargetTexture());

	InitPostEffect();

	// mainRenderTargetのテクスチャをフレームバッファーに貼り付けるためのスプライトを初期化する
	InitDifferdRenderingSprite();

	InitCopyToMainRenderTargetSprite();

	InitFinalSprite();
}

void RenderingEngine::CreateRenderingTarget() {

	RenderTarget::CreateMainRenderTarget();
	RenderTarget::CreateAlbedoRenderTarget();
	RenderTarget::CreateNormalAndDepthRenderTarget();
	RenderTarget::CreateWorldPosAndLigIDRenderTarget();
	RenderTarget::CreateShadowMap();
	RenderTarget::CreateZPrepassRenderTarget();
	RenderTarget::CreateSnapShotRenderTarget();
	RenderTarget::CreateLuminanceRenderTarget();
	RenderTarget::CreateFinalRenderTarget();
}

void RenderingEngine::InitPostEffect() {

	m_postEffect = NewGO<PostEffect>(enPriority_Zeroth);

	m_postEffect->InitLuminance(*RenderTarget::GetMainRenderTarget());
	m_postEffect->InitGaussianBlur(*RenderTarget::GetLuminanceRenderTarget());
}

void RenderingEngine::InitDifferdRenderingSprite() {

	SpriteInitData spriteInitData;

	// テクスチャはmainRenderTargetのカラーバッファー
	spriteInitData.m_textures[enAlbedoAndShadowReceiverFlgMap] = &RenderTarget::GetRenderTarget(enAlbedoAndShadowReceiverFlgMap)->GetRenderTargetTexture();
	spriteInitData.m_textures[enNormalAndDepthMap] = &RenderTarget::GetRenderTarget(enNormalAndDepthMap)->GetRenderTargetTexture();
	spriteInitData.m_textures[enWorldPosAndLigIDMap] = &RenderTarget::GetRenderTarget(enWorldPosAndLigIDMap)->GetRenderTargetTexture();
	//spriteInitData.m_textures[enShadowMap] = &RenderTarget::GetRenderTarget(enShadowMap)->GetRenderTargetTexture();
	spriteInitData.m_width = RENDER_TARGET_W1280H720.x;
	spriteInitData.m_height = RENDER_TARGET_W1280H720.y;

	// モノクロ用のシェーダーを指定する
	spriteInitData.m_fxFilePath = SPRITE_SHADER_FILE_PATH;
	spriteInitData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
	spriteInitData.m_expandShaderResoruceView = &RenderTarget::GetShadowMap()->GetRenderTargetTexture();
	spriteInitData.m_expandShaderResoruceView_2 = &g_blur.GetBokeTexture();
	spriteInitData.m_expandConstantBufferSize = sizeof(*LightManager::GetInstance()->GetLigData());

	// 初期化オブジェクトを使って、スプライトを初期化する
	m_differdRenderingSprite.Init(spriteInitData);
}

void RenderingEngine::InitCopyToMainRenderTargetSprite() {

	SpriteInitData copyToMainRenderTargetSpriteInitData;
	copyToMainRenderTargetSpriteInitData.m_textures[0] = &RenderTarget::GetMainRenderTarget()->GetRenderTargetTexture();
	copyToMainRenderTargetSpriteInitData.m_width = RENDER_TARGET_W1280H720.x;
	copyToMainRenderTargetSpriteInitData.m_height = RENDER_TARGET_W1280H720.y;
	copyToMainRenderTargetSpriteInitData.m_fxFilePath = SPRITE_SHADER_MONOCHROME_FILE_PATH;
	copyToMainRenderTargetSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	m_copyToMainRenderTargetSprite.Init(copyToMainRenderTargetSpriteInitData);
}

void RenderingEngine::InitFinalSprite() {

	SpriteInitData copyToMainRenderTargetSpriteInitData;
	copyToMainRenderTargetSpriteInitData.m_textures[0] = &RenderTarget::GetFinalRenderTarget()->GetRenderTargetTexture();
	copyToMainRenderTargetSpriteInitData.m_width = RENDER_TARGET_W1280H720.x;
	copyToMainRenderTargetSpriteInitData.m_height = RENDER_TARGET_W1280H720.y;
	copyToMainRenderTargetSpriteInitData.m_fxFilePath = SPRITE_SHADER_MONOCHROME_FILE_PATH;
	copyToMainRenderTargetSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	m_finalSprite.Init(copyToMainRenderTargetSpriteInitData);
}

void RenderingEngine::UpdateInstance() {

	GameObjectManager::GetInstance()->ExecuteUpdate();
	PhysicsWorld::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
	EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
	SoundManager::GetInstance()->Update();
	HUD::GetHUD()->Update();
	LightManager::GetInstance()->Update();
}

void RenderingEngine::DefferdRenderingExecute(RenderContext& renderContext) {

	RenderTarget* rts[] = {
			RenderTarget::GetRenderTarget(enAlbedoAndShadowReceiverFlgMap),   // 0番目のレンダリングターゲット
			RenderTarget::GetRenderTarget(enNormalAndDepthMap),  // 1番目のレンダリングターゲット
			RenderTarget::GetRenderTarget(enWorldPosAndLigIDMap) // 2番目のレンダリングターゲット
	};

	// まず、レンダリングターゲットとして設定できるようになるまで待つ
	renderContext.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts), rts);

	// レンダリングターゲットを設定
	renderContext.SetRenderTargets(ARRAYSIZE(rts), rts);
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(rts[0]->GetWidth());
	viewport.Height = static_cast<float>(rts[0]->GetHeight());
	viewport.MinDepth = D3D12_MIN_DEPTH;
	viewport.MaxDepth = D3D12_MAX_DEPTH;
	renderContext.SetViewport(viewport);

	// レンダリングターゲットをクリア
	renderContext.ClearRenderTargetViews(ARRAYSIZE(rts), rts);

	LightManager::GetInstance()->GetLigData();
	//モデルの描画
	GameObjectManager::GetInstance()->ExecuteBackSpriteRender(renderContext);
	GameObjectManager::GetInstance()->ExecuteRender(renderContext);

	// レンダリングターゲットへの書き込み待ち
	renderContext.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts), rts);
}

void RenderingEngine::DefferdLightingExecute(RenderContext& renderContext) {

	renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetMainRenderTarget());

	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetMainRenderTarget());

	m_differdRenderingSprite.Draw(renderContext);

	renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetMainRenderTarget());
}

void RenderingEngine::CopyToRenderTarget(RenderContext& renderContext) {

	renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetSnapShotRenderTarget());

	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetSnapShotRenderTarget());

	m_copyToMainRenderTargetSprite.Draw(renderContext);

	renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetSnapShotRenderTarget());

}

void RenderingEngine::ExecuteDrawLuminance(RenderContext& renderContext) {

	auto& luminanceRenderTarget = *RenderTarget::GetLuminanceRenderTarget();
	// 輝度抽出用のレンダリングターゲットに変更
	renderContext.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);

	// レンダリングターゲットを設定
	renderContext.SetRenderTargetAndViewport(luminanceRenderTarget);

	// レンダリングターゲットをクリア
	renderContext.ClearRenderTargetView(luminanceRenderTarget);

	// 輝度抽出を行う
	m_postEffect->GetLuminanceSprite().Draw(renderContext);

	// レンダリングターゲットへの書き込み終了待ち
	renderContext.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
}

void RenderingEngine::ExecuteGaussianBlur(RenderContext& renderContext) {

	//ガウシアンブラーを4回実行する
	for (int i = 0; i < GAUSSIAN_BLUR_NUM; i++) {

		m_postEffect->GetGaussianBlurSprite(i).ExecuteOnGPU(renderContext, BLUR_POWER);
	}

	//4枚のボケ画像を合成してメインレンダリングターゲットに加算合成
	renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetMainRenderTarget());

	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetMainRenderTarget());

	m_postEffect->GetFinalSprite().Draw(renderContext);

	renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetMainRenderTarget());
}

void RenderingEngine::DrawPostEffect(RenderContext& renderContext) {

	renderContext.SetRenderTarget(
		RenderTarget::GetFinalRenderTarget()->GetRTVCpuDescriptorHandle(),
		RenderTarget::GetRenderTarget(enAlbedoAndShadowReceiverFlgMap)->GetDSVCpuDescriptorHandle()
	);

	EffectEngine::GetInstance()->Draw();									//エフェクト
	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetFinalRenderTarget());
	HUD::GetHUD()->Draw(renderContext);										//HUD
	GameObjectManager::GetInstance()->ExecuteFontRender(renderContext);		//フォント
	PhysicsWorld::GetInstance()->DebubDrawWorld(renderContext);
}

void RenderingEngine::DrawFinalSprite(RenderContext& renderContext) {

	renderContext.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetFinalRenderTarget());

	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetFinalRenderTarget());

	m_copyToMainRenderTargetSprite.Draw(renderContext);
	DrawPostEffect(renderContext);
	GameObjectManager::GetInstance()->Execute2DRender(renderContext);

	renderContext.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetFinalRenderTarget());
}

void RenderingEngine::Render() {

	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//シャドウマップの作成
	GameObjectManager::GetInstance()->DrawShadowMap(renderContext);

	//深度値テクスチャの作成（このゲームでは法線テクスチャと化している）
	GameObjectManager::GetInstance()->DrawZPrepassMap(renderContext);

	//ディファードレンダリング(G-Bufferの作成)
	DefferdRenderingExecute(renderContext);

	//ディファードライティング(G-Bufferとモデルの構造体を元にライト計算)
	DefferdLightingExecute(renderContext);


	//輝度抽出
	ExecuteDrawLuminance(renderContext);

	//ガウシアンブラーを４回かける。
	ExecuteGaussianBlur(renderContext);


	//最終的にできるスプライト
	DrawFinalSprite(renderContext);

	//メインレンダリングターゲットの内容をスナップショット。
	CopyToRenderTarget(renderContext);

	// メインレンダリングターゲットの絵をフレームバッファーにコピー
	renderContext.SetRenderTarget(
		g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		g_graphicsEngine->GetCurrentFrameBuffuerDSV()
	);

	m_finalSprite.Draw(renderContext);
}
