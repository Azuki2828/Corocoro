#pragma once

class Player;
class Key;

class Magnet : public IGameObject
{
private:
	int m_timer = 0;			//<�ύX>�������΂̈ꎞ��~�̂���m_timer��ǉ�
public:
	bool Start() override final;
	void Update() override final;
	
	//���͂�N�ɂ���֐��B
	void SetState_N(bool plusflg = false) {
		mState = State_N;
		if (plusflg) {
			plusFlg = true;
		}
	}
	//����S�ɂ���֐��B
	void SetState_S(bool plusflg = false) {
		mState = State_S; 
		if (plusflg) {
			plusFlg = true;
		}
	}

	//�ړ��͈͂�ݒ肷��֐��B
	//front:�O�̍��W�B	back:��̍��W�B
	//x�̒l������������front�ɐݒ肷��悤�ɂ��Ă��������B
	void SetMove(Vector3 front, Vector3 back) { moveRange_front = front, moveRange_back = back, moveFlg = true; }

	//���W��o�^����֐��B
	void SetPosition(Vector3 pos) { m_pos = pos; }

	//�������֐��B
	void Init(const char* magnetName)
	{
		char filePathtkm[256];

		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", magnetName);
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->SetShadowReceiverFlag(true);
		m_skinModelRender->Init(true, false);
	}
private:

	//�v���C���[�ɗ͂�^����֐��B
	void SetMagnetPower()const;

	bool plusFlg = false;		//�������΃t���O�B
	bool moveFlg = false;		//�����t���O�B
	mutable Vector3 m_length;	//�v���C���[�Ƃ̋����B
	Vector3 m_pos;				//���W�B
	Vector3 moveRange_front;	//�ړ��͈͂̍��[�B
	Vector3 moveRange_back;		//�ړ��͈͂̉E�[�B
	Vector3 moveSpeed;			//���������B

	/// <summary>
	/// ���ɂ̃X�e�[�g�B
	/// </summary>
	typedef enum {
		State_N,
		State_S,
		State_Nplus,
		State_Splus,
	}Magnet_State;

	Magnet_State mState;	//���ɂ̃X�e�[�g�B

	Player* m_player = nullptr;
	Key* m_key = nullptr;

	SkinModelRender* m_skinModelRender = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
};

