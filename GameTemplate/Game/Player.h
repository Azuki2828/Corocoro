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

private:
	/// <summary>
	/// �A�j���[�V�����N���b�v�B
	/// </summary>
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};

	typedef enum {
		State_N,
		State_S,
	}Player_State;
	
	//�v���C���[�̃X�e�[�g�B
	Player_State pState = State_N;

	Model m_model;			//���f���\�������B
	ModelInitData initData;
	Animation m_animation;	//�A�j���V�����Đ������B
	AnimationClip m_animationClips[enAnimClip_Num];	//�A�j���[�V�����N���b�v�B
	Skeleton m_skeleton;	//�X�P���g���B
	CharacterController m_charaCon;

	DirectionLight* m_dirLight = nullptr;
	Vector3 m_pos;
	mutable Vector3 m_movePower;

	SkinModelRender* m_skinModelRender = nullptr;

};

