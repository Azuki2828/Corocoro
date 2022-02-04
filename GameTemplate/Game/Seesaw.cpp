#include "stdafx.h"
#include "Seesaw.h"

bool Seesaw::Start()
{

	m_boxCollider.Create(SEESAW_COLLIDER_SIZE);

	//剛体を初期化。
	RigidBodyInitData rbInitData;
	//質量を設定する。
	rbInitData.mass = SEESAW_MASS;
	rbInitData.collider = &m_boxCollider;
	rbInitData.pos = m_pos;
	rbInitData.rot = m_rot;

	//回転のしやすさを設定する。
	//物理エンジン任せの回転はしないので、全部の軸0にする。
	rbInitData.localInteria.Set(SEESAW_LOCAL_INTERIA);
	m_rigidBody.Init(rbInitData);

	//摩擦力を設定する。
	m_rigidBody.SetFriction(SEESAW_FRICTION);
	//線形移動する要素を設定する。
	//シーソーは動かないので全部の軸を0にする。
	m_rigidBody.SetLinearFactor(SEESAW_LINIOR_FACTOR);
	//エンジン任せの
	m_rigidBody.SetAngularFactor(SEESAW_ANGULAR_FACTOR);
	return true;
}

Seesaw::~Seesaw() {
	DeleteGO(m_skinModelRender);
}

void Seesaw::Update()
{
	////剛体の座標と回転を取得。
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
	//徐々に減衰
	//angularVel *= 0.98f;
	//
	m_rigidBody.SetAngularVelocity(SEESAW_ANGULAR_VELOCITY);
	//剛体の座標と回転をモデルに反映。
	m_skinModelRender->SetPosition(pos);
	m_skinModelRender->SetRotation(rot);
	m_skinModelRender->UpdateWorldMatrix(pos, rot, g_vec3One);

}
