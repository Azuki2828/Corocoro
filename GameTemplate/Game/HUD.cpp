#include "stdafx.h"
#include "HUD.h"

HUD* HUD::m_hud = nullptr;


void HUD::Init(int num, const char* filepath, float width, float height, AlphaBlendMode mode) {

	m_spriteData.push_back(new SpriteData);
	m_spriteData[m_spriteNum]->spriteNum = num;
	m_spriteData[m_spriteNum]->initData.m_ddsFilePath[enData_Zeroth] = filepath;
	m_spriteData[m_spriteNum]->initData.m_width = width;
	m_spriteData[m_spriteNum]->initData.m_height = height;
	m_spriteData[m_spriteNum]->initData.m_fxFilePath = SPRITE_SHADER_FILE_PATH;
	m_spriteData[m_spriteNum]->initData.m_alphaBlendMode = mode;

	m_spriteData[m_spriteNum]->sprite.Init(m_spriteData[m_spriteNum]->initData);
	m_spriteNum++;
}

void HUD::Release() {

	m_spriteData.clear();
	m_spriteNum = RESET_SPRITE_NUM;
}

void HUD::Update() {
	for (int i = 0; i < m_spriteData.size(); i++) {
		m_spriteData[i]->sprite.SetMulColor(m_spriteData[i]->mulColor);
		m_spriteData[i]->sprite.Update(m_spriteData[i]->pos, m_spriteData[i]->rot, m_spriteData[i]->sca);
	}
}

void HUD::Draw(RenderContext& rc) {
	for (int i = 0; i < m_spriteData.size(); i++) {
		if (m_spriteData[i]->activate) {
			m_spriteData[i]->sprite.Draw(rc);
		}
	}
}