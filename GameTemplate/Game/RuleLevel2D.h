#pragma once
#include "level2D/Level2D.h"

//スプライトの番号
enum {
	enSprite_Rule,
	enSprite_Back,
	enSprite_Next,
	enSprite_BackGround,

	enRuleSprite_Num

};
class RuleLevel2D:public IGameObject
{
private:
	bool Start();
	~RuleLevel2D();
	void Update();
public:
	/**
	 * @brief スプライトを取得する関数。
	 * @param num スプライト番号
	 * @return スプライト
	*/
	SpriteRender* GetSprite(int num) {
		return m_sprite[num];
	}
	/**
	 * @brief 表示関数。
	 * @param rc レンダーコンテキスト
	*/
	void Render(RenderContext& rc) override;

private:
	Level2D m_level2D;		//レベル2D。

	//それぞれのクラスのポインタ

	SpriteRender* m_sprite[enRuleSprite_Num] = { nullptr };
};