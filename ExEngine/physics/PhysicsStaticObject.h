/*!
 * @brief	静的オブジェクト。
 */

#pragma once

#include "physics/MeshCollider.h"
#include "physics/RigidBody.h"


/// <summary>
/// 静的物理オブジェクト
/// </summary>
class PhysicsStaticObject{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PhysicsStaticObject();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~PhysicsStaticObject();

	virtual void Release();
	/// <summary>
	/// モデルからの静的オブジェクトの作成。
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="worldMatrix">ワールド行列</param>
	void CreateFromModel(Model& model, const Matrix& worldMatrix);

	virtual void CreateCommon(Vector3 pos, Quaternion rot) {

	}
	/// <summary>
	/// 摩擦力を設定する。
	/// </summary>
	/// <param name="friction">摩擦力。10が最大値。</param>
	void SetFriction(float friction)
	{
		m_rigidBody.SetFriction(friction);
	}

	MeshCollider* GetCollider() {
		return &m_meshCollider;
	}
private:
	MeshCollider m_meshCollider;		//メッシュコライダー。
	RigidBody m_rigidBody;				//剛体。
};
