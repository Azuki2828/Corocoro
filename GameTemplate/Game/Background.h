#pragma once
#include "Level.h"
/// <summary>
/// 背景クラス。
/// </summary>

class Level;
class Magnet;
class Key;

class Background : public IGameObject
{
public:
	bool Start() override;
	~Background();
	void Update() override;
	void Render(RenderContext& rc)override;
	float GetDeathPosY() { return deathPosY; }

	//Keyクラスでいじるためにpublicにしています。
	CSoundSource* GameBGMSound = nullptr;		//BGM用サウンドソース

private:
	float deathPosY;							//死ぬY座標。ステージによってポジションは異なる。
	Model m_model;								//モデル
	PhysicsStaticObject m_physicsStaticObject;	//静的物理オブジェクト・
	Level m_level;								//レベル
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
	FontRender* m_fontRender = nullptr;

	std::vector<Magnet*> m_magnet;
	Key* m_key = nullptr;

};

