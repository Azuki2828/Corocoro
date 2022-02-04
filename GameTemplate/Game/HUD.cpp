#include "stdafx.h"
#include "HUD.h"

HUD* HUD::m_hud = nullptr;


void HUD::Init(int num, const char* filepath, float width, float height, AlphaBlendMode mode, int prio) {


	for (int i = 0; i < m_spriteData.size(); i++) {

		//スプライトが存在しているなら有効にする。
		if (m_spriteData[i]->spriteNum == num) {
			m_spriteData[i]->activate = true;
			return;
		}
	}

	//最初はそのまま作成する。
	if (m_spriteData.size() == 0) {
		m_spriteData.push_back(new SpriteData);
		m_spriteData[enData_Zeroth]->spriteNum = num;
		m_spriteData[enData_Zeroth]->initData.m_ddsFilePath[enData_Zeroth] = filepath;
		m_spriteData[enData_Zeroth]->initData.m_width = width;
		m_spriteData[enData_Zeroth]->initData.m_height = height;
		m_spriteData[enData_Zeroth]->initData.m_fxFilePath = HUD_FILE_PATH;
		m_spriteData[enData_Zeroth]->initData.m_alphaBlendMode = mode;
		m_spriteData[enData_Zeroth]->prio = prio;

		m_spriteData[enData_Zeroth]->sprite.Init(m_spriteData[enData_Zeroth]->initData);
	}
	//２回目以降はテンプレで作成する。
	else {
		auto it = m_spriteData.begin();
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->prio <= prio) {
				it = m_spriteData.insert(it, new SpriteData);
				m_spriteData[i]->spriteNum = num;
				m_spriteData[i]->initData.m_ddsFilePath[enData_Zeroth] = filepath;
				m_spriteData[i]->initData.m_width = width;
				m_spriteData[i]->initData.m_height = height;
				m_spriteData[i]->initData.m_fxFilePath = HUD_FILE_PATH;
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

	//全て解放する。
	m_spriteData.clear();
}

void HUD::Update() {
	for (int i = 0; i < m_spriteData.size(); i++) {
		//乗算カラーをスプライトに設定する。
		m_spriteData[i]->sprite.SetMulColor(m_spriteData[i]->mulColor);
		//スプライトを更新する。(この中で乗算カラーの更新も行っている)
		m_spriteData[i]->sprite.Update(m_spriteData[i]->pos, m_spriteData[i]->rot, m_spriteData[i]->sca);
	}
}

void HUD::Draw(RenderContext& rc) {

	for (int i = 0; i < m_spriteData.size(); i++) {

		//有効なら描画する。
		if (m_spriteData[i]->activate) {
			m_spriteData[i]->sprite.Draw(rc);
		}
	}
}