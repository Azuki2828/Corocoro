#include "stdafx.h"
#include "SpriteRender.h"


bool SpriteRender::Start() {

	return true;
}
void SpriteRender::Init(const char* filepath, float width, float height, AlphaBlendMode mode) {

	m_initData.m_ddsFilePath[enData_Zeroth] = filepath;
	m_initData.m_width = static_cast<UINT>(width);
	m_initData.m_height = static_cast<UINT>(height);
	m_initData.m_fxFilePath = "Assets/shader/sprite.fx";
	m_initData.m_alphaBlendMode = mode;

	m_sprite.Init(m_initData);
}

void SpriteRender::Update() {

	m_sprite.SetMulColor(m_mulColor);
	m_sprite.Update(m_pos, m_rot, m_sca);
}

void SpriteRender::Render(RenderContext& rc) {

	switch (rc.GetRenderMode()) {
	case RenderContext::Render_Mode::RenderMode_Shadow:
		break;
	case RenderContext::Render_Mode::RenderMode_Normal:
		m_sprite.Draw(rc);
		break;
	}
}

void SpriteRender::RenderSprite(RenderContext& rc) {

	switch (rc.GetRenderMode()) {
	case RenderContext::Render_Mode::RenderMode_Shadow:
		break;
	case RenderContext::Render_Mode::RenderMode_Normal:
		m_sprite.Draw(rc);
		break;
	}
}