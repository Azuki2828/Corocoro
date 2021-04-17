#pragma once
class SpriteRender : public IGameObject
{
public:
	bool Start()override final;
	//スプライト初期化関数。
	void Init(const char* filepath, float width, float height , AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans);
	void Render(RenderContext& rc) override;
	void SetPosition(const Vector3& pos) { m_pos = pos; }
	void SetRotation(const Quaternion& rot) { m_rot = rot; }
	void SetScale(const Vector3& sca) { m_sca = sca; }
	void SetMulColor(const Vector4& mulCol) {
		m_mulColor = mulCol;
	}
	void Update()override final;
private:
	Sprite m_sprite;
	SpriteInitData m_initData;
	Vector3 m_pos;
	Quaternion m_rot = Quaternion::Identity;
	Vector3 m_sca = Vector3::One;
	Vector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };	//乗算カラー。
};

