#pragma once
#include "level2D/Level2D.h"

namespace {
	const char* SPRITE_NAME_RESULT = "Result";
	const char* SPRITE_NAME_GRAY_BACK = "GrayBack";
	const char* SPRITE_NAME_TIME = "time";
	const char* SPRITE_NAME_TEN1 = "ten1";
	const char* SPRITE_NAME_SECOND1 = "second1";
	const char* SPRITE_NAME_TOP = "top";
	const char* SPRITE_NAME_TEN2 = "ten2";
	const char* SPRITE_NAME_SECOND2 = "second2";
	const char* SPRITE_NAME_TITLE_BUTTON = "titlebutton";
	const char* SPRITE_NAME_END_BUTTON = "End";

}

class ResultLevel2D : public IGameObject
{
private:
	bool Start();
	~ResultLevel2D();
	void Update();

public:
	SpriteRender* GetSprite(int num) {
		return m_sprite[num];
	}
	void Render(RenderContext& rc) override;

private:
	Level2D m_level2D;		//���x��2D�B
	SpriteRender* m_sprite[10] = { nullptr };		//�X�v���C�g�����_�[
};