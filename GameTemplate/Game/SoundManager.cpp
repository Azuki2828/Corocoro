#include "stdafx.h"
#include "SoundManager.h"

SoundManager* SoundManager::m_soundManager = nullptr;

void SoundManager::Init(const wchar_t* filePath, int num, bool flg, SoundType sType, float vol) {

	for (int i = 0; i < m_soundData.size(); i++) {
		if (m_soundData[i].soundNum == num) {

			MessageBoxA(nullptr, "���ɓo�^���ꂽ�T�E���h�̓o�^�ԍ��ł��B", "�G���[", MB_OK);
			return;
		}
	}

	SoundData soundData;
	soundData.soundName = filePath;
	soundData.soundVolume = vol;
	soundData.soundNum = num;
	soundData.roopFlg = flg;

	m_soundData.push_back(soundData);
}

void SoundManager::Play(int num) {
	bool Flg = false;
	for (int i = 0; i < m_soundData.size(); i++) {
		//�o�^�ԍ���������������Đ��B
		if (m_soundData[i].soundNum == num) {
			m_soundData[i].sound = NewGO<CSoundSource>(0);
			m_soundData[i].sound->Init(m_soundData[i].soundName);
			switch (m_soundData[i].soundType) {
			case SoundType::Type_BGM:
				m_soundData[i].sound->SetVolume(m_soundData[i].soundVolume * m_bgmVolume);
				break;
			case SoundType::Type_SE:
				m_soundData[i].sound->SetVolume(m_soundData[i].soundVolume * m_seVolume);
				break;
			case SoundType::Type_Effect:
				m_soundData[i].sound->SetVolume(m_soundData[i].soundVolume * m_effectVolume);
				break;
			}
			m_soundData[i].sound->Play(m_soundData[i].roopFlg);
			Flg = true;
		}
	}

	if (!Flg) {
		MessageBoxA(nullptr, "�܂����݂��Ȃ��T�E���h�ł��B���Init()�֐����Ă�ł��������B", "�G���[", MB_OK);
		return;
	}
}

void SoundManager::SetRoopFlg(int num, bool flg) {

	bool Flg = false;
	for (int i = 0; i < m_soundData.size(); i++) {
		//�o�^�ԍ��������������烋�[�v�t���O��ݒ�B
		if (m_soundData[i].soundNum == num) {

			m_soundData[i].roopFlg = flg;
			Flg = true;
		}
	}

	if (!Flg) {
		MessageBoxA(nullptr, "�܂����݂��Ȃ��T�E���h�ł��B���Init()�֐����Ă�ł��������B", "�G���[", MB_OK);
		return;
	}
}

void SoundManager::Release(int num) {

	for (int i = 0; i < m_soundData.size(); i++) {
		//�o�^�ԍ���������������폜�B
		if (m_soundData[i].soundNum == num) {
			DeleteGO(m_soundData[i].sound);
		}
	}
}

void SoundManager::SetSoundSourceVolume(int num, float vol) {

	bool Flg = false;
	for (int i = 0; i < m_soundData.size(); i++) {
		//�o�^�ԍ���������������{�����[����ݒ�B
		if (m_soundData[i].soundNum == num) {

			m_soundData[i].soundVolume = vol;
			Flg = true;
		}
	}

	if (!Flg) {
		MessageBoxA(nullptr, "�܂����݂��Ȃ��T�E���h�ł��B��ɐ�����Init()�֐����Ă�ł��������B", "�G���[", MB_OK);
		return;
	}
}

void SoundManager::Update() {

	
}