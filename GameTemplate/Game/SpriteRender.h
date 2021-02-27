#pragma once
class SpriteRender : public IGameObject
{
public:
	void Init(const char* filepath, float width, float height);
	void Render(RenderContext& rc) override;
private:
	Sprite m_sprite;
	SpriteInitData m_initData;
};

