#include "stdafx.h"
#include "Seesaw.h"

bool Seesaw::Start()
{

	//�R���C�_�[���������B
	Vector3 size;
	size.x = 400.0f;
	size.y = 25.0f;
	size.z = 400.0f;

	m_boxCollider.Create(size);

	//���̂��������B
	RigidBodyInitData rbInitData;
	//���ʂ�ݒ肷��B
	rbInitData.mass = 1.0f;
	rbInitData.collider = &m_boxCollider;
	rbInitData.pos = m_pos;
	rbInitData.rot = m_rot;

	//��]�̂��₷����ݒ肷��B
	//�����G���W���C���̉�]�͂��Ȃ��̂ŁA�S���̎�0�ɂ���B
	rbInitData.localInteria.Set(0.0f, 0.0f, 3000.0f);
	m_rigidBody.Init(rbInitData);

	//���C�͂�ݒ肷��B
	m_rigidBody.SetFriction(10.0f);
	//���`�ړ�����v�f��ݒ肷��B
	//�V�[�\�[�͓����Ȃ��̂őS���̎���0�ɂ���B
	m_rigidBody.SetLinearFactor(0.0f, 0.0f, 0.0f);
	//�G���W���C����
	m_rigidBody.SetAngularFactor(0.0f, 0.0f, 1.0f);
	return true;
}

Seesaw::~Seesaw() {
	DeleteGO(m_skinModelRender);
}

void Seesaw::Update()
{
	////���̂̍��W�Ɖ�]���擾�B
	static Vector3 angularVel = { 0.0f, 0.0f, 0.0f };

	Vector3 pos;
	Quaternion rot;
	static Quaternion oldRot;
	//oldRot.SetRotationZ(0.26f);
	m_rigidBody.GetPositionAndRotation(pos, rot);

	//Vector3 v1 = Vector3::Right;
	//Quaternion r1 = Quaternion::Identity;
	//rot.Apply(v1);
	//float rad = Dot(v1, Vector3::Up);

	//if (rad > 0.26f) {
	//	rot = oldRot;
	//	m_rigidBody.SetPositionAndRotation(pos, rot);
	//	m_rigidBody.ClearPower();
	//}
	//else if (rad < -0.26f) {
	//	oldRot.SetRotationZ(-0.26f);
	//	rot = oldRot;
	//	m_rigidBody.SetPositionAndRotation(pos, rot);
	//	m_rigidBody.ClearPower();
	//}

	auto rb = m_rigidBody.GetBody();
	if (fabsf(g_pad[0]->GetRStickXF()) > 0.0f) {
		angularVel.Set(0.0f, 0.0f, g_pad[0]->GetRStickXF() * -2.0f);
	
	}
	//���X�Ɍ���
	angularVel *= 0.98f;
	//
	m_rigidBody.SetAngularVelocity(angularVel);
	//���̂̍��W�Ɖ�]�����f���ɔ��f�B
	m_skinModelRender->SetPosition(pos);
	m_skinModelRender->SetRotation(rot);
	m_skinModelRender->UpdateWorldMatrix(pos, rot, g_vec3One);

}
