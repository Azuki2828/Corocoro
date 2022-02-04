#include "stdafx.h"
#include "RenderingEngine.h"

RenderingEngine* RenderingEngine::m_renderingEngine = nullptr;

void RenderingEngine::Init() {

	//�����_�����O�^�[�Q�b�g�̐����B
	CreateRenderingTarget();
	g_blur.Init(&RenderTarget::GetZPrepassRenderTarget()->GetRenderTargetTexture());

	InitPostEffect();

	// mainRenderTarget�̃e�N�X�`�����t���[���o�b�t�@�[�ɓ\��t���邽�߂̃X�v���C�g������������
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

	// �e�N�X�`����mainRenderTarget�̃J���[�o�b�t�@�[
	spriteInitData.m_textures[enAlbedoAndShadowReceiverFlgMap] = &RenderTarget::GetRenderTarget(enAlbedoAndShadowReceiverFlgMap)->GetRenderTargetTexture();
	spriteInitData.m_textures[enNormalAndDepthMap] = &RenderTarget::GetRenderTarget(enNormalAndDepthMap)->GetRenderTargetTexture();
	spriteInitData.m_textures[enWorldPosAndLigIDMap] = &RenderTarget::GetRenderTarget(enWorldPosAndLigIDMap)->GetRenderTargetTexture();
	//spriteInitData.m_textures[enShadowMap] = &RenderTarget::GetRenderTarget(enShadowMap)->GetRenderTargetTexture();
	spriteInitData.m_width = RENDER_TARGET_W1280H720.x;
	spriteInitData.m_height = RENDER_TARGET_W1280H720.y;

	// ���m�N���p�̃V�F�[�_�[���w�肷��
	spriteInitData.m_fxFilePath = SPRITE_SHADER_FILE_PATH;
	spriteInitData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
	spriteInitData.m_expandShaderResoruceView = &RenderTarget::GetShadowMap()->GetRenderTargetTexture();
	spriteInitData.m_expandShaderResoruceView_2 = &g_blur.GetBokeTexture();
	spriteInitData.m_expandConstantBufferSize = sizeof(*LightManager::GetInstance()->GetLigData());

	// �������I�u�W�F�N�g���g���āA�X�v���C�g������������
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
			RenderTarget::GetRenderTarget(enAlbedoAndShadowReceiverFlgMap),   // 0�Ԗڂ̃����_�����O�^�[�Q�b�g
			RenderTarget::GetRenderTarget(enNormalAndDepthMap),  // 1�Ԗڂ̃����_�����O�^�[�Q�b�g
			RenderTarget::GetRenderTarget(enWorldPosAndLigIDMap) // 2�Ԗڂ̃����_�����O�^�[�Q�b�g
	};

	// �܂��A�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂ő҂�
	renderContext.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts), rts);

	// �����_�����O�^�[�Q�b�g��ݒ�
	renderContext.SetRenderTargets(ARRAYSIZE(rts), rts);
	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(rts[0]->GetWidth());
	viewport.Height = static_cast<float>(rts[0]->GetHeight());
	viewport.MinDepth = D3D12_MIN_DEPTH;
	viewport.MaxDepth = D3D12_MAX_DEPTH;
	renderContext.SetViewport(viewport);

	// �����_�����O�^�[�Q�b�g���N���A
	renderContext.ClearRenderTargetViews(ARRAYSIZE(rts), rts);

	LightManager::GetInstance()->GetLigData();
	//���f���̕`��
	GameObjectManager::GetInstance()->ExecuteBackSpriteRender(renderContext);
	GameObjectManager::GetInstance()->ExecuteRender(renderContext);

	// �����_�����O�^�[�Q�b�g�ւ̏������ݑ҂�
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
	// �P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
	renderContext.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);

	// �����_�����O�^�[�Q�b�g��ݒ�
	renderContext.SetRenderTargetAndViewport(luminanceRenderTarget);

	// �����_�����O�^�[�Q�b�g���N���A
	renderContext.ClearRenderTargetView(luminanceRenderTarget);

	// �P�x���o���s��
	m_postEffect->GetLuminanceSprite().Draw(renderContext);

	// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
	renderContext.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
}

void RenderingEngine::ExecuteGaussianBlur(RenderContext& renderContext) {

	//�K�E�V�A���u���[��4����s����
	for (int i = 0; i < GAUSSIAN_BLUR_NUM; i++) {

		m_postEffect->GetGaussianBlurSprite(i).ExecuteOnGPU(renderContext, BLUR_POWER);
	}

	//4���̃{�P�摜���������ă��C�������_�����O�^�[�Q�b�g�ɉ��Z����
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

	EffectEngine::GetInstance()->Draw();									//�G�t�F�N�g
	renderContext.SetRenderTargetAndViewport(*RenderTarget::GetFinalRenderTarget());
	HUD::GetHUD()->Draw(renderContext);										//HUD
	GameObjectManager::GetInstance()->ExecuteFontRender(renderContext);		//�t�H���g
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

	//�V���h�E�}�b�v�̍쐬
	GameObjectManager::GetInstance()->DrawShadowMap(renderContext);

	//�[�x�l�e�N�X�`���̍쐬�i���̃Q�[���ł͖@���e�N�X�`���Ɖ����Ă���j
	GameObjectManager::GetInstance()->DrawZPrepassMap(renderContext);

	//�f�B�t�@�[�h�����_�����O(G-Buffer�̍쐬)
	DefferdRenderingExecute(renderContext);

	//�f�B�t�@�[�h���C�e�B���O(G-Buffer�ƃ��f���̍\���̂����Ƀ��C�g�v�Z)
	DefferdLightingExecute(renderContext);


	//�P�x���o
	ExecuteDrawLuminance(renderContext);

	//�K�E�V�A���u���[���S�񂩂���B
	ExecuteGaussianBlur(renderContext);


	//�ŏI�I�ɂł���X�v���C�g
	DrawFinalSprite(renderContext);

	//���C�������_�����O�^�[�Q�b�g�̓��e���X�i�b�v�V���b�g�B
	CopyToRenderTarget(renderContext);

	// ���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
	renderContext.SetRenderTarget(
		g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		g_graphicsEngine->GetCurrentFrameBuffuerDSV()
	);

	m_finalSprite.Draw(renderContext);
}
