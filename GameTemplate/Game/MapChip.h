#pragma once

#include "physics/PhysicsStaticObject.h"
struct LevelObjectData;

class Material;

class MapChip
{
public:
	MapChip(const LevelObjectData& objData);
	void Draw(RenderContext& rc);
	void Draw(RenderContext& rc,
		const Matrix& mWorld,
		const Matrix& mView,
		const Matrix& mProj);
	//{
	//	m_skinModelRender->Draw(
	//		rc,
	//		m_skinModelRender->GetModel()->GetWorldMatrix(),
	//		g_camera3D->GetViewMatrix(),
	//		g_camera3D->GetProjectionMatrix()
	//	);
	//}

private:

	struct MConstantBuffer{
		Matrix mWorld;		//ワールド行列。
		Matrix mView;		//ビュー行列。
		Matrix mProj;		//プロジェクション行列。
	};
	PhysicsStaticObject m_physicsStaticObject;

	ConstantBuffer m_constantBuffer;					//定数バッファ。
	std::vector< SMesh* > m_meshs;							//メッシュ。
	std::vector< DescriptorHeap > m_descriptorHeap;		//ディスクリプタヒープ。

	SkinModelRender* m_skinModelRender = nullptr;
};

