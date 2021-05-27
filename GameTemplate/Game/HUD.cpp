#include "stdafx.h"
#include "HUD.h"

HUD* HUD::m_hud = nullptr;


void HUD::Init(const char* filepath, float width, float height, AlphaBlendMode mode) {

	m_spriteData.push_back(new SpriteData);
	m_spriteData[m_spriteNum]->m_initData.m_ddsFilePath[0] = filepath;
	m_spriteData[m_spriteNum]->m_initData.m_width = width;
	m_spriteData[m_spriteNum]->m_initData.m_height = height;
	m_spriteData[m_spriteNum]->m_initData.m_fxFilePath = "Assets/shader/sprite.fx";
	m_spriteData[m_spriteNum]->m_initData.m_alphaBlendMode = mode;

	m_spriteData[m_spriteNum]->m_sprite.Init(m_spriteData[m_spriteNum]->m_initData);
	m_spriteNum++;
}

void HUD::Release() {

	//for (auto it = m_spriteData.begin(); it != m_spriteData.end();it++) {
	//
	//	it = m_spriteData.erase(it);
	//}

	m_spriteData.clear();
	m_spriteNum = 0;
}

void HUD::Update() {
	for (int i = 0; i < m_spriteData.size(); i++) {
		m_spriteData[i]->m_sprite.SetMulColor(m_spriteData[i]->m_mulColor);
		m_spriteData[i]->m_sprite.Update(m_spriteData[i]->m_pos, m_spriteData[i]->m_rot, m_spriteData[i]->m_sca);
	}
}

void HUD::Draw(RenderContext& rc) {
	for (int i = 0; i < m_spriteData.size(); i++) {
		if (m_spriteData[i]->activate) {
			m_spriteData[i]->m_sprite.Draw(rc);
		}
	}
}