#pragma once

class Seesaw : public IGameObject
{
public:
	~Seesaw();
	bool Start() override;
	void Update() override;
	void Init(const char* name) {
		char filePathtkm[256];
		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->SetShadowReceiverFlag(true);

		//À•W‚ð“o˜^B
		m_ligData.m_directionLigData[0].Dir.Set(-1, -1, -1);
		m_ligData.m_directionLigData[0].Dir.Normalize();
		//m_ligData.m_directionLigData[0].Col.Set(10.0f, 10.0f, 0.0f, 1.0f);

		m_ligData.ambient.Set(0.8f, 0.8f, 0.8f);
		m_ligData.metaric = 0.5f;
		m_ligData.smooth = 0.1f;
		//m_ligData.edge = Edge_1;
		m_ligData.powValue = 10.0f;
		m_ligData.uvNoiseMul = 1.0f;
		m_skinModelRender->SetUserLigData(&m_ligData);
		//m_skinModelRender->SetExpandShaderResourceView_2(&RenderTarget::GetZPrepassRenderTarget()->GetRenderTargetTexture());
		m_skinModelRender->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

		m_skinModelRender->SetPosition(m_pos);
		m_skinModelRender->SetRotation(m_rot);
		m_skinModelRender->Init(true, false);

		m_skinModelRender->UpdateWorldMatrix();

		//m_physicsStaticObject.CreateFromModel(
		//	*m_skinModelRender->GetModel(),
		//	m_skinModelRender->GetModel()->GetWorldMatrix()
		//);
		//m_physicsStaticObject.SetFriction(10.0f);
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
	Quaternion m_startRot;
	Vector3 m_pos;
	Quaternion m_rot;
	Vector3 m_sca;
	BoxCollider m_boxCollider;
	RigidBody m_rigidBody;
	SkinModelRender* m_skinModelRender = nullptr;
	//PhysicsStaticObject m_physicsStaticObject;
	LigData m_ligData;
};


