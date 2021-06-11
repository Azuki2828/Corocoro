#pragma once
#include "stdafx.h"

class FontRender : public IGameObject
{
public:
	struct FontValue {
		wchar_t text[256];	//テキスト
		Vector2 position;	//座標
		Vector4 color;		//色
		float rotation;		//回転
		float scale;		//拡大率
		Vector2 pivot;		//ピボット
	};

	/**
	 * @brief テキストを設定する関数
	 * @param text テキスト
	*/
	void SetText(const wchar_t* text)
	{
		swprintf_s(m_fontValue.text, text);
	}

	/**
	 * @brief 座標を設定する関数
	 * @param pos 座標
	*/
	void SetPosition(const Vector2& pos) {
		m_fontValue.position = pos;
	}

	/**
	 * @brief 拡大率を設定する関数
	 * @param sca 拡大率
	*/
	void SetScale(float sca) {
		m_fontValue.scale = sca;
	}

	/**
	 * @brief フォントの色を設定する関数
	 * @param col 色
	*/
	void SetColor(const Vector4& col) {
		m_fontValue.color = col;
	}

	/**
	 * @brief ピボットを設定する関数
	 * @param piv ピボット
	*/
	void SetPivot(const Vector2& piv) {
		m_fontValue.pivot = piv;
	}

	/**
	 * @brief 初期化関数
	 * @param text テキスト
	 * @param position 座標
	 * @param color 色
	 * @param rotation 回転 
	 * @param scale 拡大率
	 * @param pivot ピボット
	*/
	void Init(
		const wchar_t* text,
		const Vector2 position = Vector2::Zero,
		Vector4 color = Vector4::Black,
		float rotation = 0.0f,
		float scale = 1.0f,
		Vector2 pivot = { 0.5f,0.5f }
	);

	/**
	 * @brief 枠の影を付ける関数
	 * @param isDrawShadow 枠の影を付けるかどうかのフラグ
	 * @param shadowOffset 枠の影の太さ
	 * @param shadowColor 枠の影の色
	*/
	void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
	{
		m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
	}

	/**
	 * @brief 描画関数
	 * @param rc レンダーコンテキスト
	*/
	void Render(RenderContext& rc)override final;

private:
	Font m_font;			//フォント
	FontValue m_fontValue;	//フォントの要素
};

