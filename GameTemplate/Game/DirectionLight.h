#pragma once
#include "LightBase.h"

struct DirectionLigData {
	Vector3 Dir;
	float pad;
	Vector4 Col;
};

class DirectionLight : public LightBase
{
	bool StartSub();
	~DirectionLight();
public:
	void Init();
	void SetLigDirection(float _x = 0.0f, float _y = -1.0f, float _z = 1.0f) {
		m_dirLigData.Dir.x = _x;
		m_dirLigData.Dir.y = _y;
		m_dirLigData.Dir.z = _z;
		m_dirLigData.Dir.Normalize();
	}

	void SetLigDirection(const Vector3& dir) {
		m_dirLigData.Dir = dir;
		m_dirLigData.Dir.Normalize();
	}

	Vector3* GetLigDirection() { 
		return &m_dirLigData.Dir;
	}

	void SetLigColor(float _x = 50.0f, float _y = 50.0f, float _z = 50.0f) {
		m_dirLigData.Col.x = _x;
		m_dirLigData.Col.y = _y;
		m_dirLigData.Col.z = _z;
	}


	void SetLigColor(const Vector3& col) {
		m_dirLigData.Col = col;
	}

	void* GetLigData() { return &m_dirLigData; }

	ConstantBuffer cb;
	DescriptorHeap ds;
	DirectionLigData m_dirLigData;
};