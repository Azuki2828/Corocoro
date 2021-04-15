#pragma once

#include "stdafx.h"
#include "DirectionLight.h"
#include "LightBase.h"

static const int MAX_DIRECTION_LIGHT = 8;

//struct SDirectionLigData {
//	Vector3 Dir;
//	float pad;
//	Vector3 Col;
//};

struct LigData {
	DirectionLigData m_directionLigData[MAX_DIRECTION_LIGHT];
	Vector3 eyePos;
	//Matrix viewProj;
};

class LightManager
{
public:

	static void CreateInstance() {

		m_lightManager = new LightManager;
	}

	static LightManager* GetInstance() {

		return m_lightManager;
	}

	void Update();

	void AddLight(LightBase* light);
	void RemoveLight(LightBase* light);

	LigData* GetLigData() { return &m_ligData; }

	//bool Start()override final;
	//void Update()override final;
private:
	static LightManager* m_lightManager;
	LigData m_ligData;
	std::list<DirectionLigData*> m_directionLights;
};

