#pragma once
class SpriteRender : public IGameObject
{
private:
	bool Start()override final;
	void Update()override final;

public:
	void Init(const char* filepath, float width, float height , AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans);
	void Render(RenderContext& rc) override;
	void RenderSprite(RenderContext& rc)override;
	void SetPosition(const Vector3& pos) { m_pos = pos; }
	void SetRotation(const Quaternion& rot) { m_rot = rot; }
	void SetScale(const Vector3& sca) { m_sca = sca; }
	Vector3 GetScale() { return m_sca; }
	void SetMulColor(const Vector4& mulCol) {
		m_mulColor = mulCol;
	}
private:
	Sprite m_sprite;
	SpriteInitData m_initData;
	Vector3 m_pos = Vector3::Zero;
	Quaternion m_rot = Quaternion::Identity;
	Vector3 m_sca = Vector3::One;
	Vector4 m_mulColor = Vector4::White;	//乗算カラー。
};

