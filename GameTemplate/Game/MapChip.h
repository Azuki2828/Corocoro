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
		Matrix mWorld;		//���[���h�s��B
		Matrix mView;		//�r���[�s��B
		Matrix mProj;		//�v���W�F�N�V�����s��B
	};
	PhysicsStaticObject m_physicsStaticObject;

	ConstantBuffer m_constantBuffer;					//�萔�o�b�t�@�B
	std::vector< SMesh* > m_meshs;							//���b�V���B
	std::vector< DescriptorHeap > m_descriptorHeap;		//�f�B�X�N���v�^�q�[�v�B

	SkinModelRender* m_skinModelRender = nullptr;
};

