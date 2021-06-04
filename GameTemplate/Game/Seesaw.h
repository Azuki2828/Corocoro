#pragma once

class Seesaw : public IGameObject
{
private:
	~Seesaw();
	bool Start() override;
	void Update() override;

public:
	void Init(const char* name) {
		char filePathtkm[256];
		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->SetShadowReceiverFlag(true);
		m_skinModelRender->SetZprepassFlag(true);

		m_ligData.m_directionLigData[0].Dir.Set(0, 1, 1);
		m_ligData.m_directionLigData[0].Dir.Normalize();
		m_ligData.m_directionLigData[0].Col.Set(10.0f, 10.0f, 10.0f, 1.0f);
		m_ligData.ambient.Set(0.8f, 0.8f, 0.8f);
		m_ligData.metaric = 1.0f;
		m_ligData.smooth = 0.35f;
		m_ligData.edge = Edge_1;
		m_ligData.powValue = 0.7f;

		m_skinModelRender->SetUserLigData(&m_ligData);
		m_skinModelRender->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);
		m_skinModelRender->Init();

		m_skinModelRender->UpdateWorldMatrix();
	}

	void SetPosition(const Vector3& pos) {
		m_pos = pos;
	}
	Vector3 GetPosition() {
		return m_pos;
	}
	void SetRotation(const Quaternion& rot) {
		m_rot = rot;
	}
	void StartRot(const Quaternion& rot) {
		m_startRot = rot;
	}
	void SetStart() {
		m_rigidBody.SetPositionAndRotation(m_pos, m_startRot);
		m_skinModelRender->SetPosition(m_pos);
		m_skinModelRender->SetRotation(m_startRot);
		m_skinModelRender->UpdateWorldMatrix(m_pos, m_startRot, g_vec3One);
	}
private:
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_sca = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;
	Quaternion m_startRot = Quaternion::Identity;
	BoxCollider m_boxCollider;
	RigidBody m_rigidBody;
	LigData m_ligData;

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	SkinModelRender* m_skinModelRender = nullptr;
};


