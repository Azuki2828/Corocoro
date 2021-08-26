#pragma once

#include "physics/PhysicsStaticObject.h"
struct LevelObjectData;

class Material;

class MapChip
{
public:
	MapChip(const LevelObjectData& objData);
	~MapChip();
	ModelOption* GetModelOption() { return &m_modelOption; }
	void Draw(RenderContext& rc);
	void Draw(RenderContext& rc,
		const Matrix& mWorld,
		const Matrix& mView,
		const Matrix& mProj);

private:

	struct MConstantBuffer{
		Matrix mWorld;		//ワールド行列。
		Matrix mView;		//ビュー行列。
		Matrix mProj;		//プロジェクション行列。
	};
	ConstantBuffer m_constantBuffer;					//定数バッファ。
	PhysicsStaticObject m_physicsStaticObject;
	ModelOption m_modelOption;	//マップチップ専用のライト

	std::vector< SMesh* > m_meshs;							//メッシュ。
	std::vector< DescriptorHeap > m_descriptorHeap;		//ディスクリプタヒープ。

	SkinModelRender* m_skinModelRender = nullptr;
};

