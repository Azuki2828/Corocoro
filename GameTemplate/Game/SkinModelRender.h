#pragma once

class SkinModelRender : public IGameObject
{

	struct LightCameraData{
		Matrix m_viewProj;
		Vector3 eyePos;
	};
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

	//�J���[�o�b�t�@�[�t�H�[�}�b�g�̎w��B
	void SetColorBufferFormat(DXGI_FORMAT colorBufferFormat) {
		initData.m_colorBufferFormat = colorBufferFormat;
	}

	//�A�j���[�V�����������֐��B
	void InitAnimation(AnimationClip* animClip, int animNum) {
		m_animClip = animClip;
		m_animNum = animNum;
	}

	void SetAnimFlg(bool flg) {
		m_animFlg = flg;
	}

	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
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
		m_zprepassModel.UpdateWorldMatrix(m_pos, m_rot, m_sca);
		m_shadowModel.UpdateWorldMatrix(m_pos, m_rot, m_sca);
	}

	void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 sca)
	{
		m_model.UpdateWorldMatrix(pos, rot, sca);
		m_zprepassModel.UpdateWorldMatrix(pos, rot, sca);
		m_shadowModel.UpdateWorldMatrix(pos, rot, sca);
	}

	//�V���h�E�L���X�^�[�t���O��ݒ�B
	void SetShadowCasterFlag(bool flg) {

		m_shadowCasterFlag = flg;
	}

	void SetShadowReceiverFlag(bool flg) {

		m_shadowReceiverFlag = flg;
	}

	void SetZprepassFlag(bool flg) {
		m_zPrepassFlg = true;
	}

	void SetExpandShaderResourceView(IShaderResource* expandShaderResoruceView) {
		initData.m_expandShaderResoruceView = expandShaderResoruceView;
	}
	void SetExpandShaderResourceView_2(IShaderResource* expandShaderResoruceView_2) {
		initData.m_expandShaderResoruceView_2 = expandShaderResoruceView_2;
	}
	void SetUserLigData(LigData* lig) {
		m_userLigData = lig;
	}
private:
	int m_animNum;
	bool m_animFlg = false;
	const char* m_fileNametkm = nullptr;
	const char* m_fileNametks = nullptr;
	bool m_shadowCasterFlag = false;	//�V���h�E�L���X�^�[�t���O�B
	bool m_shadowReceiverFlag = false;	//�V���h�E���V�[�o�[�t���O�B
	bool m_zPrepassFlg = false;

	Model m_model;			//���f���\�������B
	Model m_shadowModel;	//�V���h�E�쐬�p�̃��f���B
	Model m_zprepassModel;   // ZPrepass�ŕ`�悳��郂�f��
	ModelInitData initData;
	Animation m_animation;	//�A�j���V�����Đ������B
	AnimationClip* m_animClip;
	Skeleton m_skeleton;	//�X�P���g���B

	DirectionLight* m_directionLight = nullptr;

	LightCameraData m_lightCameraData;
	LigData* m_userLigData = nullptr;	//���[�U�[���ݒ肷�郉�C�g�f�[�^
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_sca = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;

	//struct DirectionLightData {
	//	Vector3 Direction;
	//	Vector3 Color;
	//};
	//DirectionLightData m_directionLightData;
};

