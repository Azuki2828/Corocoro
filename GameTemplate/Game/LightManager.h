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

enum {
	Edge_NULL,
	Edge_1,
	Edge_2
};
struct LigData {
	DirectionLigData m_directionLigData[MAX_DIRECTION_LIGHT];
	Vector3 eyePos = Vector3::Zero;
	float pad;
	Vector3 ambient;
	float pad1;
	Matrix m_viewProj;
	float metaric = 0.0f;
	float smooth = 0.5f;
	int edge = Edge_NULL;
	float powValue = 0.0f;
	float uvNoiseMul = 0.0f;
	float uvNoiseOffset = 0.0f;
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
private:
	LigData m_ligData;
	static LightManager* m_lightManager;
	std::list<DirectionLigData*> m_directionLights;
};

