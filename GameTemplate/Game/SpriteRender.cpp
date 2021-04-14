#include "stdafx.h"
#include "SpriteRender.h"

void SpriteRender::Init(const char* filepath, float width, float height, AlphaBlendMode mode) {

	m_initData.m_ddsFilePath[0] = filepath;
	m_initData.m_width = width;
	m_initData.m_height = height;
	m_initData.m_fxFilePath = "Assets/shader/sprite.fx";
	m_initData.m_alphaBlendMode = mode;

	m_sprite.Init(m_initData);
}

void SpriteRender::Update() {
	m_sprite.Update(m_pos, Quaternion::Identity, Vector3::One);
}

void SpriteRender::Render(RenderContext& rc) {

	if (RenderContext::Render_Mode::RenderMode_Normal) {
		m_sprite.Draw(rc);
	}
}