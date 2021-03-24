#pragma once

class DirectionLight;

class SkinModelRender : public IGameObject
{
public:
	//SkinModelRender();
	//�������B
	//directionFlg:�f�B���N�V�������C�g�̉e�����󂯂邩�B
	//pointLightFlg:�|�C���g���C�g�̉e�����󂯂邩�B
	void Init(bool directionFlg = false, bool pointLightFlg = false);

	//tkm�t�@�C���̃��[�h�B
	void SetFileNametkm(const char* name) { m_fileNametkm = name; }

	//tks�t�@�C���̃��[�h�B
	void SetFileNametks(const char* name) { m_fileNametks = name; }

	//�A�j���[�V�����������֐��B
	void InitAnimation(AnimationClip* animClip, int animNum) {
		m_animClip = animClip;
		m_animNum = animNum;
	}

	//���f�����擾�B
	Model* GetModel() { return &m_model; }

	//�X�P���g�����擾�B
	Skeleton* GetSkeleton() { return &m_skeleton; }
	
	void SetPosition(Vector3 pos) { m_pos = pos; }
	void SetRotation(Quaternion rot) { m_rot = rot; }
	void SetScale(Vector3 sca) { m_sca = sca; }
	void Render(RenderContext& rc) override;

	void Update()override final;
	//���[���h�s����X�V����B
	//���[���h�s��̍X�V�́A���t���[����x�s���Ă��܂����A
	//���̃N�X�̎g�p�҂̔C�ӂ̃^�C�~���O�ōX�V�������Ƃ��́A
	//���̊֐��𗘗p���Ă��������B
	void UpdateWorldMatrix()
	{
		m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
	}

	void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 sca)
	{
		m_model.UpdateWorldMatrix(pos, rot, sca);
	}

private:
	int m_animNum;
	const char* m_fileNametkm = nullptr;
	const char* m_fileNametks = nullptr;

	Model m_model;			//���f���\�������B
	ModelInitData initData;
	Animation m_animation;	//�A�j���V�����Đ������B
	AnimationClip* m_animClip;
	Skeleton m_skeleton;	//�X�P���g���B

	DirectionLight* m_directionLight = nullptr;

	Vector3 m_pos = Vector3::Zero;
	Vector3 m_sca = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;

	//struct DirectionLightData {
	//	Vector3 Direction;
	//	Vector3 Color;
	//};
	//DirectionLightData m_directionLightData;
};

