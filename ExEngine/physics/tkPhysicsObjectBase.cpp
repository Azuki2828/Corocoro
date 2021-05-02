/*!
 * @brief	物理オブジェクトのベースクラス。
 */


#include "stdafx.h"
#include "physics/tkPhysicsObjectBase.h"
#include "physics/BoxCollider.h"
#include "physics/SphereCollider.h"

using namespace std;
	
	void CPhysicsObjectBase::CreateBox(Vector3 pos, Quaternion rot, Vector3 size)
	{
		Release();
		auto boxCollider = make_unique<BoxCollider>();
		boxCollider->Create(size);
		m_collider = move(boxCollider);
		CreateCommon(pos, rot);
	}
	void CPhysicsObjectBase::CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height )
	{
		Release();
		auto capusuleCollider = make_unique<CCapsuleCollider>();
		capusuleCollider->Init(radius, height);
		m_collider = move(capusuleCollider);
		CreateCommon(pos, rot);
	}
	
	void CPhysicsObjectBase::CreateSphere(Vector3 pos, Quaternion rot, float radius)
	{
		Release();
		auto sphereCollider = make_unique<SphereCollider>();
		sphereCollider->Create(radius);
		m_collider = move(sphereCollider);
		CreateCommon(pos, rot);
	}

	//void CPhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, const CSkinModelData& skinModelData)
	//{
	//	Release();
	//	auto meshCollider = make_unique<CMeshCollider>();
	//	meshCollider->CreateFromSkinModel(skinModelData, nullptr);
	//	m_collider = move(meshCollider);
	//	CreateCommon(pos, rot);
	//}
	//void CPhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, prefab::CSkinModelRender* skinModelRender)
	//{
	//	CreateMesh(pos, rot, scale, skinModelRender->GetSkinModel());
	//}
	//void CPhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, const CSkinModel& skinModel)
	//{
	//	Release();
	//	CMatrix mScale;
	//	mScale.MakeScaling(scale);
	//	auto meshCollider = make_unique<CMeshCollider>();
	//	meshCollider->CreateFromSkinModel(skinModel, &mScale);
	//	m_collider = move(meshCollider);
	//	CreateCommon(
	//		pos,
	//		rot
	//	);
	//	
	//}
