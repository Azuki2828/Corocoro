#pragma once
#include "SpriteRender.h"
#include <vector>

struct SpriteData {
	Sprite m_sprite;
	SpriteInitData m_initData;
	Vector3 m_pos = Vector3::Zero;
	Quaternion m_rot = Quaternion::Identity;
	Vector3 m_sca = Vector3::One;
	Vector4 m_mulColor = Vector4::White;	//æŽZƒJƒ‰[B
	bool activate = true;
};
class HUD
{
public:
	static void CreateHUD() {
		m_hud = new HUD;
	}
	static HUD* GetHUD() {
		return m_hud;
	}
	void Init(const char* filepath, float width, float height, AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans);
	void Release();
	void Draw(RenderContext& rc);
	void SetPosition(int num,const Vector3& pos) { m_spriteData[num]->m_pos = pos; }
	void SetRotation(int num, const Quaternion& rot) { m_spriteData[num]->m_rot = rot; }
	void SetScale(int num, const Vector3& sca) { m_spriteData[num]->m_sca = sca; }
	void SetMulColor(int num, const Vector4& mulCol) {

		m_spriteData[num]->m_mulColor = mulCol;
	}
	void Deactivate(int num) {
		m_spriteData[num]->activate = false;
	}

	void Activate(int num) {
		m_spriteData[num]->activate = true;
	}

	void Update();
private:
	int m_spriteNum = 0;
	static HUD* m_hud;
	std::vector<SpriteData*> m_spriteData;
};

