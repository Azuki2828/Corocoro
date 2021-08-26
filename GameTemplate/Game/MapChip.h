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
		Matrix mWorld;		//���[���h�s��B
		Matrix mView;		//�r���[�s��B
		Matrix mProj;		//�v���W�F�N�V�����s��B
	};
	ConstantBuffer m_constantBuffer;					//�萔�o�b�t�@�B
	PhysicsStaticObject m_physicsStaticObject;
	ModelOption m_modelOption;	//�}�b�v�`�b�v��p�̃��C�g

	std::vector< SMesh* > m_meshs;							//���b�V���B
	std::vector< DescriptorHeap > m_descriptorHeap;		//�f�B�X�N���v�^�q�[�v�B

	SkinModelRender* m_skinModelRender = nullptr;
};

