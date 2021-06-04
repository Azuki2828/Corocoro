#pragma once

class Player;
class Key;
class Game;

class Magnet : public IGameObject
{
private:
	~Magnet();
	bool Start() override final;
	void Update() override final;

public:

	//���͂�N�ɂ���֐��B
	void SetState_N(bool plusflg = false) {
		m_MagState = State_N;
		m_ligData.m_directionLigData[0].Col.Set(10.0f, 10.0f, 10.0f, 1.0f);
		if (plusflg) {
			m_plusFlg = true;
		}
	}
	//����S�ɂ���֐��B
	void SetState_S(bool plusflg = false) {
		m_MagState = State_S;
		m_ligData.m_directionLigData[0].Col.Set(10.0f, 10.0f, 30.0f, 1.0f);
		if (plusflg) {
			m_plusFlg = true;
		}
	}

	//�ړ��͈͂�ݒ肷��֐��B
	//front:�O�̍��W�B	back:��̍��W�B
	//x�̒l������������front�ɐݒ肷��悤�ɂ��Ă��������B
	void SetMove(Vector3 front, Vector3 back) { m_moveRange_front = front, m_moveRange_back = back, m_moveFlg = true; }

	//���W��o�^����֐��B
	void SetPosition(Vector3 pos) { m_pos = pos; }
	void SetRotation(const Quaternion& rot) {
		m_rot = rot;
	}

	void SetScale(const Vector3& sca) {
		m_sca = sca;
	}
	Vector3 GetPosition() { return m_pos; }
	void CreateTriggerBox(int type);

	//�v���C���[�ɗ͂�^����֐��B
	void SetMagnetPower();
	void SetMagnetTriggerBox(int stageNum);

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


	bool m_plusFlg = false;		//�������΃t���O�B
	bool m_moveFlg = false;		//�����t���O�B
	int m_magnetNum = 0;
	int m_timer = 0;			//<�ύX>�������΂̈ꎞ��~�̂���m_timer��ǉ�
	Vector3 m_length = Vector3::Zero;			//�v���C���[�Ƃ̋����B
	Vector3 m_pos = Vector3::Zero;				//���W�B
	Vector3 m_sca = { 1.0f,1.0f,1.0f };
	Vector3 m_magnetPos = Vector3::Zero;		//���͂̔����ꏊ�B��_�͍����Ȃ��߁A���S�ɂ���B
	Vector3 m_moveRange_front = Vector3::Zero;	//�ړ��͈͂̍��[�B
	Vector3 m_moveRange_back = Vector3::Zero;	//�ړ��͈͂̉E�[�B
	Vector3 m_moveSpeed = Vector3::Zero;			//���������B
	Quaternion m_rot = Quaternion::Identity;

	Magnet_State m_MagState;	//���ɂ̃X�e�[�g�B
	PhysicsStaticObject m_physicsStaticObject;	//�����蔻��
	CPhysicsGhostObject m_ghostBox;
	LigData m_ligData;

	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	SkinModelRender* m_skinModelRender = nullptr;
	Player* m_player = nullptr;
	Key* m_key = nullptr;
	Game* m_game = nullptr;
};

