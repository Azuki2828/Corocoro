#pragma once

namespace {
	const Vector3 SEESAW_LIG_DIRECTION = { 0.0f,1.0f,1.0f };
	const Vector4 SEESAW_LIG_COLOR = { 10.0f, 10.0f, 10.0f, 1.0f };
	const Vector3 SEESAW_AMBIENT = { 0.8f, 0.8f, 0.8f };
	const float SEESAW_METARIC = 1.0f;
	const float SEESAW_SMOOTH = 0.35f;
	const float SEESAW_POW_VALUE = 0.7f;

	const Vector3 SEESAW_COLLIDER_SIZE = { 400.0f,25.0f,400.0f };
	const float SEESAW_MASS = 1.0f;
	const Vector3 SEESAW_LOCAL_INTERIA = { 0.0f,0.0f,3000.0f };
	const float SEESAW_FRICTION = 10.0f;
	const Vector3 SEESAW_LINIOR_FACTOR = { 0.0f,0.0f,0.0f };
	const Vector3 SEESAW_ANGULAR_FACTOR = { 0.0f,0.0f,1.0f };
	const Vector3 SEESAW_ANGULAR_VELOCITY = { 0.0f,0.0f,0.0f };
}

class Seesaw : public IGameObject
{
private:
	~Seesaw();
	bool Start() override;
	void Update() override;

public:
	void Init(const char* name) {
		char filePathtkm[NAME_SIZE];
		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
		m_skinModelRender = NewGO<SkinModelRender>(enPriority_Zeroth);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->SetShadowReceiverFlag(true);
		m_skinModelRender->SetZprepassFlag(true);

		m_ligData.m_directionLigData[enData_Zeroth].Dir.Set(SEESAW_LIG_DIRECTION);
		m_ligData.m_directionLigData[enData_Zeroth].Dir.Normalize();
		m_ligData.m_directionLigData[enData_Zeroth].Col.Set(SEESAW_LIG_COLOR);
		m_ligData.ambient.Set(SEESAW_AMBIENT);
		m_ligData.metaric = SEESAW_METARIC;
		m_ligData.smooth = SEESAW_SMOOTH;
		m_ligData.edge = Edge_1;
		m_ligData.powValue = SEESAW_POW_VALUE;

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


