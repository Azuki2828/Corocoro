#pragma once

class DirectionLight;

class Player : public IGameObject
{
public:
	bool Start() override;
	void Update() override;

	//���݂̃X�e�[�g���擾����֐��B
	const int GetPlayerState()const { return pState; }

	//���݂̍��W���擾����֐��B
	const Vector3 GetPosition()const { return m_charaCon.GetPosition(); }

	//�O������͂��󂯎��֐��B
	//pow�F�͂̑傫��
	void ReceivePower(Vector3 pow)const { m_movePower += pow; }

	//�v���C���[�̎��ɂ�ϊ�����֐��B
	void ChangeState();

	void Render(RenderContext& rc)override;

private:
	/// <summary>
	/// �A�j���[�V�����N���b�v�B
	/// </summary>
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};

	/// <summary>
	/// ���ɁB
	/// </summary>
	typedef enum {
		State_N,
		State_S,
	}Player_State;

	/// <summary>
	/// �v���C���[�̓o�^�ԍ��B
	/// </summary>
	enum EnPlayer {
		enPlayer_0,
		enPlayer_1,
		enPlayer_Num
	};
	//�v���C���[�̃X�e�[�g�B
	Player_State pState = State_N;

	Model m_model;										//���f���\�������B
	ModelInitData initData;								//���f���̃f�[�^�B
	Animation m_animation;								//�A�j���V�����Đ������B
	AnimationClip m_animationClips[enAnimClip_Num];		//�A�j���[�V�����N���b�v�B
	Skeleton m_skeleton;								//�X�P���g���B
	CharacterController m_charaCon;						//�L�����R���B

	DirectionLight* m_dirLight = nullptr;				//�f�B���N�V�������C�g�B
	Vector3 m_pos = { 300.0f,300.0f,0.0f };				//�������W�B
	//Vector3 m_pos = { 1500.0f,2800.0f,0.0f };
	//Vector3 m_pos = { 1500.0f,2800.0f,20.0f };
	mutable Vector3 m_movePower;						//�����́B

	SkinModelRender* m_skinModelRender[enPlayer_Num] = { nullptr };
	Font m_font;
};

