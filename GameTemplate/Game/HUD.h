#pragma once
#include "SpriteRender.h"
#include <vector>

namespace {

	const int RESET_SPRITE_NUM = 0;
}
struct SpriteData {
	int spriteNum = 0;
	Sprite sprite;
	SpriteInitData initData;
	Vector3 pos = Vector3::Zero;
	Quaternion rot = Quaternion::Identity;
	Vector3 sca = Vector3::One;
	Vector4 mulColor = Vector4::White;	//èÊéZÉJÉâÅ[ÅB
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
	void Init(int num, const char* filepath, float width, float height, AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans);
	void Release();
	void Draw(RenderContext& rc);
	void SetPosition(int num,const Vector3& pos) { 
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->pos = pos;
				break;
			}
		}
	}
	void SetRotation(int num, const Quaternion& rot) { 
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->rot = rot;
				break;
			}
		}
	}

	Vector3 GetScale(int num) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				return m_spriteData[i]->sca;
				break;
			}
		}
	}
	void SetScale(int num, const Vector3& sca) { 
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->sca = sca;
				break;
			}
		}
	}
	void SetMulColor(int num, const Vector4& mulCol) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->mulColor = mulCol;
				break;
			}
		}
	}
	void Deactivate(int num) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->activate = false;
				break;
			}
		}
	}

	void Activate(int num) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->activate = true;
				break;
			}
		}
	}

	void Update();
private:
	int m_spriteNum = 0;
	static HUD* m_hud;
	std::vector<SpriteData*> m_spriteData;
};

