#include "stdafx.h"
#include "HUD.h"

HUD* HUD::m_hud = nullptr;


void HUD::Init(int num, const char* filepath, float width, float height, AlphaBlendMode mode, int prio) {


	for (int i = 0; i < m_spriteData.size(); i++) {
		if (m_spriteData[i]->spriteNum == num) {
			m_spriteData[i]->activate = true;
			return;
		}
	}

	if (m_spriteData.size() == 0) {
		m_spriteData.push_back(new SpriteData);
		m_spriteData[0]->spriteNum = num;
		m_spriteData[0]->initData.m_ddsFilePath[enData_Zeroth] = filepath;
		m_spriteData[0]->initData.m_width = width;
		m_spriteData[0]->initData.m_height = height;
		m_spriteData[0]->initData.m_fxFilePath = SPRITE_SHADER_FILE_PATH;
		m_spriteData[0]->initData.m_alphaBlendMode = mode;
		m_spriteData[0]->prio = prio;

		m_spriteData[0]->sprite.Init(m_spriteData[0]->initData);
	}
	else {
		auto it = m_spriteData.begin();
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->prio >= prio) {
				it = m_spriteData.insert(it, new SpriteData);
				m_spriteData[i]->spriteNum = num;
				m_spriteData[i]->initData.m_ddsFilePath[enData_Zeroth] = filepath;
				m_spriteData[i]->initData.m_width = width;
				m_spriteData[i]->initData.m_height = height;
				m_spriteData[i]->initData.m_fxFilePath = SPRITE_SHADER_FILE_PATH;
				m_spriteData[i]->initData.m_alphaBlendMode = mode;
				m_spriteData[i]->prio = prio;

				m_spriteData[i]->sprite.Init(m_spriteData[i]->initData);
				break;
			}
			else {
				it++;
			}
		}
	}
}

void HUD::Release() {

	m_spriteData.clear();
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