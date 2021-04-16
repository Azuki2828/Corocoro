#pragma once
class SpriteRender : public IGameObject
{
public:
	//スプライト初期化関数。
	void Init(const char* filepath, float width, float height , AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans);
	void Render(RenderContext& rc) override;
	void SetPosition(Vector3 pos) { m_pos = pos; }
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
		m_scale.x *= -1.0f;

	}
	void Update()override final;
private:
	Sprite m_sprite;
	SpriteInitData m_initData;
	Vector3 m_pos;
	Vector3 m_scale = {-1.0f,1.0f,1.0f};
};

