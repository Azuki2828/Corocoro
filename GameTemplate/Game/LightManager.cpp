#include "stdafx.h"
#include "LightManager.h"


LightManager* LightManager::m_lightManager = nullptr;

void LightManager::AddLight(LightBase* light) {

	//�����K�肳��Ă��鐔�ɒB���Ă�����u���Ȃ�
	if (m_directionLights.size() >= MAX_DIRECTION_LIGHT) {
		MessageBoxA(nullptr, "����ȏ�f�B���N�V�������C�g�͒u���܂���", "�G���[", MB_OK);
		return;
	}

	//�N���X�̖��O�𒲂ׂ�
	const std::type_info& typeInfo = typeid(*light);

	//�f�B���N�V�������C�g��������
	if (typeInfo == typeid(DirectionLight)) {

		//�o�^�ς݂����ׂ�B
		auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), light->GetLigData());
		if (findIt == m_directionLights.end()) {
			//�V�K�o�^�B
			m_directionLights.push_back(reinterpret_cast<DirectionLigData*>(light->GetLigData()));

			int a = 0;
			std::list<DirectionLigData*>::iterator itr;
			itr = m_directionLights.begin();

			//for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
			//	m_ligData.m_directionLigData[i] = nullptr;
			//}
			for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

				m_ligData.directionLigData[a] = *(*itr);
				a++;
			}
		}
		else {
			//���ɓo�^����Ă��B
			MessageBoxA(nullptr, "���ɓo�^����Ă��܂�", "�G���[", MB_OK);
			return;
		}
	}

}

void LightManager::RemoveLight(LightBase* light)
{
	//�N���X�̖��O�𒲂ׂ�
	const std::type_info& typeInfo = typeid(*light);
	
	//�f�B���N�V�������C�g��������
	if (typeInfo == typeid(DirectionLight)) {

		//���C�g���폜
		m_directionLights.erase(
			std::remove(m_directionLights.begin(), m_directionLights.end(), light->GetLigData()),
			m_directionLights.end()
		);

		int a = 0;

		//for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
		//	m_ligData.m_directionLigData[i] = nullptr;
		//}

		for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

			m_ligData.directionLigData[a] = *(*itr);
			a++;
		}
	}
}
void LightManager::RemoveLightAll()
{
	m_directionLights.clear();
}
void LightManager::Update() {

	//�J�����̍��W���X�V
	m_lightManager->m_ligData.eyePos = g_camera3D->GetPosition();
	//���C�g�J��������v���W�F�N�V�����s����擾�B
	m_lightManager->m_ligData.m_viewProj = Camera::GetLightCamera()->GetViewProjectionMatrix();

	////���C�g�̊�����0.3f�ɐݒ�
	//m_ligData.ambient.Set(0.3f, 0.3f, 0.3f);


	for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

		int a = 0;
		m_ligData.directionLigData[a] = *(*itr);
		a++;
	}

}