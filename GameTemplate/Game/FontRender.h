#pragma once
#include "stdafx.h"

class FontRender : public IGameObject
{
public:
	struct FontValue {
		const wchar_t* text;
		Vector2 position;
		Vector4 color;
		float rotation;
		float scale;
		Vector2 pivot;
	};

	void Init(
		const wchar_t* text,
		const Vector2 position = { 0.0f,0.0f },
		Vector4 color = { 0.0f,0.0f,0.0f,1.0f },
		float rotation = 0.0f,
		float scale = 1.0f,
		Vector2 pivot = { 0.5f,0.5f }
	);

	void SetText(const wchar_t* text) { m_fontValue.text = text; }

	void SetPosition(const Vector2& position) { m_fontValue.position = position; }

	void SetColor(const Vector4& color) { m_fontValue.color = color; }

	void SetRotation(float rotation) { m_fontValue.rotation = rotation; }

	void SetScale(float scale) { m_fontValue.scale = scale; }

	void SetPiVot(const Vector2& pivot) { m_fontValue.pivot = pivot; }

	void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
	{
		m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
	}

	//void Draw(FontValue& fontValue);
	void Render(RenderContext& rc)override final;
private:
	Font m_font;
	FontValue m_fontValue;
};

