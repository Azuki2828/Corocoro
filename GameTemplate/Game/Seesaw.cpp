#include "stdafx.h"
#include "Seesaw.h"

bool Seesaw::Start()
{

	//コライダーを初期化。
	Vector3 size;
	size.x = 400.0f;
	size.y = 25.0f;
	size.z = 400.0f;

	m_boxCollider.Create(size);

	//剛体を初期化。
	RigidBodyInitData rbInitData;
	//質量を設定する。
	rbInitData.mass = 1.0f;
	rbInitData.collider = &m_boxCollider;
	rbInitData.pos = m_pos;
	rbInitData.rot = m_rot;

	//回転のしやすさを設定する。
	//物理エンジン任せの回転はしないので、全部の軸0にする。
	rbInitData.localInteria.Set(0.0f, 0.0f, 3000.0f);
	m_rigidBody.Init(rbInitData);

	//摩擦力を設定する。
	m_rigidBody.SetFriction(10.0f);
	//線形移動する要素を設定する。
	//シーソーは動かないので全部の軸を0にする。
	m_rigidBody.SetLinearFactor(0.0f, 0.0f, 0.0f);
	//エンジン任せの
	m_rigidBody.SetAngularFactor(0.0f, 0.0f, 1.0f);
	return true;
}

Seesaw::~Seesaw() {
	DeleteGO(m_skinModelRender);
}

void Seesaw::Update()
{
	////剛体の座標と回転を取得。
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
	//徐々に減衰
	angularVel *= 0.98f;
	//
	m_rigidBody.SetAngularVelocity(angularVel);
	//剛体の座標と回転をモデルに反映。
	m_skinModelRender->SetPosition(pos);
	m_skinModelRender->SetRotation(rot);
	m_skinModelRender->UpdateWorldMatrix(pos, rot, g_vec3One);

}
