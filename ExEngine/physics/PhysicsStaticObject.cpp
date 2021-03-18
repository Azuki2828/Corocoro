/*!
* @brief	静的オブジェクト。
*/


#include "stdafx.h"
#include "Physics.h"
#include "physics/PhysicsStaticObject.h"

PhysicsStaticObject::PhysicsStaticObject()
{
}
PhysicsStaticObject::~PhysicsStaticObject()
{
	
}
void PhysicsStaticObject::Release() {
	PhysicsWorld::GetInstance()->RemoveRigidBody(m_rigidBody);
}
void PhysicsStaticObject::CreateFromModel(Model& model, const Matrix& worldMatrix)
{
	m_meshCollider.CreateFromModel(model, worldMatrix);
	RigidBodyInitData rbInfo;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Init(rbInfo);
}
