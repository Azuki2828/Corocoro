#pragma once
#include "Level.h"
/// <summary>
/// 背景クラス。
/// </summary>

class Level;

class Background : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc)override;
private:
	Model m_model;								//モデル
	PhysicsStaticObject m_physicsStaticObject;	//静的物理オブジェクト・
	Level m_level;
	SpriteRender* m_spriteRender = nullptr;
};

