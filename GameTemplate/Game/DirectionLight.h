#pragma once

class DirectionLight : public IGameObject
{
	struct LigData {
		Vector3 Dir;
		float pad;
		Vector3 Col;
		float pad2;
		Vector3 eyePos;
	};
	//DirectionLight(float _x = 1.0f, float _y = -1.0f, float _z = -1.0f);
	bool Start() override final;
	~DirectionLight();
	void Update() override final;
public:
	void Init();
	void SetLigDirection(float _x, float _y, float _z) {
		m_ligData.Dir.x = _x;
		m_ligData.Dir.y = _y;
		m_ligData.Dir.z = _z;
	}

	void SetLigColor(float _x, float _y, float _z) {
		m_ligData.Col.x = _x;
		m_ligData.Col.y = _y;
		m_ligData.Col.z = _z;
	}

	void SetEyePos() { m_ligData.eyePos = g_camera3D->GetPosition(); }

	ConstantBuffer cb;
	DescriptorHeap ds;

	LigData m_ligData;
	LigData* GetLigData() { return &m_ligData; }
};