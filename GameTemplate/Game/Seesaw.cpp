#include "stdafx.h"
#include "Seesaw.h"

bool Seesaw::Start()
{

	m_boxCollider.Create(SEESAW_COLLIDER_SIZE);

	//���̂��������B
	RigidBodyInitData rbInitData;
	//���ʂ�ݒ肷��B
	rbInitData.mass = SEESAW_MASS;
	rbInitData.collider = &m_boxCollider;
	rbInitData.pos = m_pos;
	rbInitData.rot = m_rot;

	//��]�̂��₷����ݒ肷��B
	//�����G���W���C���̉�]�͂��Ȃ��̂ŁA�S���̎�0�ɂ���B
	rbInitData.localInteria.Set(SEESAW_LOCAL_INTERIA);
	m_rigidBody.Init(rbInitData);

	//���C�͂�ݒ肷��B
	m_rigidBody.SetFriction(SEESAW_FRICTION);
	//���`�ړ�����v�f��ݒ肷��B
	//�V�[�\�[�͓����Ȃ��̂őS���̎���0�ɂ���B
	m_rigidBody.SetLinearFactor(SEESAW_LINIOR_FACTOR);
	//�G���W���C����
	m_rigidBody.SetAngularFactor(SEESAW_ANGULAR_FACTOR);
	return true;
}

Seesaw::~Seesaw() {
	DeleteGO(m_skinModelRender);
}

void Seesaw::Update()
{
	////���̂̍��W�Ɖ�]���擾�B
	//static Vector3 angularVel = { 0.0f, 0.0f, 0.0f };

	Vector3 pos;
	Quaternion rot;
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

	//auto rb = m_rigidBody.GetBody();
	/*if (fabsf(g_pad[0]->GetRStickXF()) > 0.0f) {
		angularVel.Set(0.0f, 0.0f, g_pad[0]->GetRStickXF() * -2.0f);
	
	}*/
	//���X�Ɍ���
	//angularVel *= 0.98f;
	//
	m_rigidBody.SetAngularVelocity(SEESAW_ANGULAR_VELOCITY);
	//���̂̍��W�Ɖ�]�����f���ɔ��f�B
	m_skinModelRender->SetPosition(pos);
	m_skinModelRender->SetRotation(rot);
	m_skinModelRender->UpdateWorldMatrix(pos, rot, g_vec3One);

}
