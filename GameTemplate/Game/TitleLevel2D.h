#pragma once
#include "level2D/Level2D.h"


/// <summary>
/// レベル2D処理のサンプルクラス。
/// </summary>

class TitleLevel2D : public IGameObject
{
private:
	bool Start() override;
	~TitleLevel2D();
	void Update() override;

public:
	void Render(RenderContext& rc) override;

private:
	Level2D m_level2D;		//レベル2D。
};