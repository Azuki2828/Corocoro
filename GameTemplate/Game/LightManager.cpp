#include "stdafx.h"
#include "LightManager.h"


LightManager* LightManager::m_lightManager = nullptr;

void LightManager::AddLight(LightBase* light) {

	if (m_directionLights.size() >= MAX_DIRECTION_LIGHT) {
		MessageBoxA(nullptr, "Ç±ÇÍà»è„ÉfÉBÉåÉNÉVÉáÉìÉâÉCÉgÇíuÇØÇ»Ç¢ÇÊÅI", "ÇΩÇ¢Ç÷ÇÒÅI", MB_OK);
		return;
	}

	const std::type_info& typeInfo = typeid(*light);

	if (typeInfo == typeid(DirectionLight)) {

		//ìoò^çœÇ›Ç©í≤Ç◊ÇÈÅB
		auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), light->GetLigData());
		if (findIt == m_directionLights.end()) {
			//êVãKìoò^ÅB
			m_directionLights.push_back(reinterpret_cast<DirectionLigData*>(light->GetLigData()));

			int a = 0;
			std::list<DirectionLigData*>::iterator itr;
			itr = m_directionLights.begin();

			//for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
			//	m_ligData.m_directionLigData[i] = nullptr;
			//}
			for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

				m_ligData.m_directionLigData[a] = *(*itr);
				a++;
			}
		}
		else {
			//ä˘Ç…ìoò^Ç≥ÇÍÇƒÇÈÇÊÅB
			MessageBoxA(nullptr, "ä˘Ç…ìoò^Ç≥ÇÍÇƒÇÈÇÊÅIÅI", "ÇΩÇ¢Ç÷ÇÒÅI", MB_OK);
			return;
		}
	}

}

void LightManager::RemoveLight(LightBase* light)
{
	const std::type_info& typeInfo = typeid(*light);
	
	if (typeInfo == typeid(DirectionLight)) {
		m_directionLights.erase(
			std::remove(m_directionLights.begin(), m_directionLights.end(), light->GetLigData()),
			m_directionLights.end()
		);

		int a = 0;

		//for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
		//	m_ligData.m_directionLigData[i] = nullptr;
		//}
		for (auto itr = m_directionLights.begin(); itr != m_directionLights.end(); ++itr) {

			m_ligData.m_directionLigData[a] = *(*itr);
			a++;
		}
	}
}

void LightManager::Update() {
	m_lightManager->m_ligData.eyePos = g_camera3D->GetPosition();
	//m_lightManager->m_ligData.viewProj = Camera::GetLightCamera()->GetViewProjectionMatrix();
}