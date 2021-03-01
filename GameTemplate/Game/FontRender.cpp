#include "stdafx.h"
#include "FontRender.h"

void FontRender::Init(
	const wchar_t* text,
	const Vector2 position = { 0.0f,0.0f },
	Vector4 color = { 0.0f,0.0f,0.0f,1.0f },
	float rotation = 0.0f,
	float scale = 1.0f,
	Vector2 pivot = { 0.5f,0.5f }
) {
	m_fontValue.text = text;
	m_fontValue.position = position;
	m_fontValue.color = color;
	m_fontValue.rotation = rotation;
	m_fontValue.scale = scale;
	m_fontValue.pivot = pivot;
}

void FontRender::Render(RenderContext& rc) {

	m_font.Begin(rc);

	m_font.Draw(
		m_fontValue.text,
		m_fontValue.position,
		m_fontValue.color,
		m_fontValue.rotation,
		m_fontValue.scale,
		m_fontValue.pivot
	);

	m_font.End(rc);
}