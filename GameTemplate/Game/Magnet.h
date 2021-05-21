#pragma once

class Player;
class Key;
class Game;

class Magnet : public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;

	//���͂�N�ɂ���֐��B
	void SetState_N(bool plusflg = false) {
		mState = State_N;
		m_ligData.m_directionLigData[0].Col.Set(10.0f, 10.0f, 10.0f, 1.0f);
		if (plusflg) {
			plusFlg = true;
		}
	}
	//����S�ɂ���֐��B
	void SetState_S(bool plusflg = false) {
		mState = State_S;
		m_ligData.m_directionLigData[0].Col.Set(10.0f, 10.0f, 30.0f, 1.0f);
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
	Vector3 GetPosition() { return m_pos; }
	void CreateTriggerBox(int type);

	void SetMagnetNum(int num) {
		m_magnetNum = num;
	}

	void SetMagnetPosition(const Vector3& pos) {
		m_magnetPos = pos;
	}

	//�������֐��B
	void Init(const char* magnetName)
	{
		char filePathtkm[256];

		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", magnetName);
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->SetShadowReceiverFlag(true);

		m_skinModelRender->SetZprepassFlag(true);
		//���W��o�^�B
		m_ligData.m_directionLigData[0].Dir.Set(-1, -1, -1);
		m_ligData.m_directionLigData[0].Dir.Normalize();
		
		m_ligData.ambient.Set(0.8f, 0.8f, 0.8f);
		m_ligData.metaric = 1.0f;
		m_ligData.smooth = 0.35f;
		m_ligData.edge = Edge_1;
		m_ligData.powValue = 10.0f;
		m_skinModelRender->SetUserLigData(&m_ligData);
		//m_skinModelRender->SetExpandShaderResourceView_2(&RenderTarget::GetZPrepassRenderTarget()->GetRenderTargetTexture());
		m_skinModelRender->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

		m_skinModelRender->Init(true, false);
	}
private:
	int m_magnetNum = 0;
	int m_timer = 0;			//<�ύX>�������΂̈ꎞ��~�̂���m_timer��ǉ�

	//�v���C���[�ɗ͂�^����֐��B
	void SetMagnetPower();
	void SetMagnetTriggerBox(int stageNum);

	bool plusFlg = false;		//�������΃t���O�B
	bool moveFlg = false;		//�����t���O�B
	Vector3 m_length;			//�v���C���[�Ƃ̋����B
	Vector3 m_pos;				//���W�B
	Vector3 m_magnetPos;		//���͂̔����ꏊ�B��_�͍����Ȃ��߁A���S�ɂ���B
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

	typedef enum {
		Left3,
		Left4,
		Left5,
		Right3,
		Right4,
		Down2,
		Down3,
		Down4,
		Up2,
		Up3,
		Up4,
	}TriggerBoxType;

	Magnet_State mState;	//���ɂ̃X�e�[�g�B

	Player* m_player = nullptr;
	Key* m_key = nullptr;
	Game* m_game = nullptr;

	SkinModelRender* m_skinModelRender = nullptr;
	PhysicsStaticObject m_physicsStaticObject;	//�����蔻��
	CPhysicsGhostObject m_ghostBox;
	LigData m_ligData;
};

