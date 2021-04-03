#pragma once
#include "LightBase.h"

struct DirectionLigData {
	Vector3 Dir;
	float pad;
	Vector4 Col;
};

class DirectionLight : public LightBase
{
	//DirectionLight(float _x = 1.0f, float _y = -1.0f, float _z = -1.0f);
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

	void SetLigColor(float _x = 20.0f, float _y = 20.0f, float _z = 20.0f) {
		m_dirLigData.Col.x = _x;
		m_dirLigData.Col.y = _y;
		m_dirLigData.Col.z = _z;
	}


	void SetLigColor(const Vector3& col) {
		m_dirLigData.Col = col;
	}


	//void SetEyePos() { m_dirLigData.eyePos = g_camera3D->GetPosition(); }

	ConstantBuffer cb;
	DescriptorHeap ds;

	DirectionLigData m_dirLigData;
	void* GetLigData() { return &m_dirLigData; }
};