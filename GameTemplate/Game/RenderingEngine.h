#pragma once
#include "stdafx.h"
extern GaussianBlur g_blur;
class RenderingEngine
{
private:
	void CreateRenderingTarget();
	void InitPostEffect();
	void InitDifferdRenderingSprite();
	void InitCopyToMainRenderTargetSprite();
	void InitFinalSprite();
	void DefferdRenderingExecute(RenderContext& renderContext);
	void DefferdLightingExecute(RenderContext& renderContext);
	void CopyToRenderTarget(RenderContext& renderContext);
	void ExecuteDrawLuminance(RenderContext& renderContext);
	void ExecuteGaussianBlur(RenderContext& renderContext);
	void DrawPostEffect(RenderContext& renderContext);
	void DrawFinalSprite(RenderContext& renderContext);
public:
	static void CreateRenderingEngine() {
		m_renderingEngine = new RenderingEngine;
	}

	static RenderingEngine* GetRenderingEngine() {

		return m_renderingEngine;
	}

	void Init();

	void UpdateInstance();

	void Render();

private:
	static RenderingEngine* m_renderingEngine;
	PostEffect* m_postEffect = nullptr;
	Sprite m_differdRenderingSprite;
	Sprite m_copyToMainRenderTargetSprite;
	Sprite m_finalSprite;
};

