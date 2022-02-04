#include "stdafx.h"
#include "HUD.h"

HUD* HUD::m_hud = nullptr;


void HUD::Init(int num, const char* filepath, float width, float height, AlphaBlendMode mode, int prio) {


	for (int i = 0; i < m_spriteData.size(); i++) {

		//�X�v���C�g�����݂��Ă���Ȃ�L���ɂ���B
		if (m_spriteData[i]->spriteNum == num) {
			m_spriteData[i]->activate = true;
			return;
		}
	}

	//�ŏ��͂��̂܂܍쐬����B
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
	//�Q��ڈȍ~�̓e���v���ō쐬����B
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

	//�S�ĉ������B
	m_spriteData.clear();
}

void HUD::Update() {
	for (int i = 0; i < m_spriteData.size(); i++) {
		//��Z�J���[���X�v���C�g�ɐݒ肷��B
		m_spriteData[i]->sprite.SetMulColor(m_spriteData[i]->mulColor);
		//�X�v���C�g���X�V����B(���̒��ŏ�Z�J���[�̍X�V���s���Ă���)
		m_spriteData[i]->sprite.Update(m_spriteData[i]->pos, m_spriteData[i]->rot, m_spriteData[i]->sca);
	}
}

void HUD::Draw(RenderContext& rc) {

	for (int i = 0; i < m_spriteData.size(); i++) {

		//�L���Ȃ�`�悷��B
		if (m_spriteData[i]->activate) {
			m_spriteData[i]->sprite.Draw(rc);
		}
	}
}