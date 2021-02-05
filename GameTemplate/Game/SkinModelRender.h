#pragma once

class DirectionLight;

class SkinModelRender : public IGameObject
{
public:
	SkinModelRender() {}
	void Init(const char* ModelFileName);

	void InitSkeleton();
	void InitModel(void* data);
	void InitAnimation();

	Model m_model;			//���f���\�������B
	ModelInitData initData;
	Animation m_animation;	//�A�j���V�����Đ������B
	Skeleton m_skeleton;	//�X�P���g���B

	DirectionLight* m_directionLight = nullptr;

private:
	const char* m_modelFileName;
};

