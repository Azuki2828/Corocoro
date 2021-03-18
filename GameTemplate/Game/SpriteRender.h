#pragma once
class SpriteRender : public IGameObject
{
public:
	//スプライト初期化関数。
	void Init(const char* filepath, float width, float height);
	void Render(RenderContext& rc) override;
	void SetPosition(Vector3 pos) { m_pos = pos; }
	void Update()override final;
private:
	Sprite m_sprite;
	SpriteInitData m_initData;
	Vector3 m_pos;
};

