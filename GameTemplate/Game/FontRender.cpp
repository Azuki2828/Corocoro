#include "stdafx.h"
#include "FontRender.h"

void FontRender::Init(
	const wchar_t* text,
	const Vector2 position,
	Vector4 color,
	float rotation,
	float scale,
	Vector2 pivot
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