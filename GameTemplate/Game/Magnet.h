#pragma once

class Player;
class Key;
class Game;

namespace {
	const float MAGNET_POWER = 100000.0f;		//��Ղ̎���
	const float MAGNET_FRICTION = 10.0f;		//���΂̖��C

	const Vector3 MAGNET_TRIGGER_BOX_ADD_POS_BASE = { 0.0f,0.0f,-200.0f };	//���͂̔����ʒu�̒���

	const float MAGNET_Z_POWER = 0.0f;								//Z�����ɂ͎��͂𔭐������Ȃ�
	const Vector4 MAGNET_N_LIG_COLOR = { 10.0f,10.0f,10.0f,1.0f };	//N���΂̐F
	const Vector4 MAGNET_S_LIG_COLOR = { 10.0f,10.0f,30.0f,1.0f };	//S���΂̐F
	const Vector3 MAGNET_LIG_DIR = { -1.0f,-1.0f,-1.0f };			//���΂̃��C�g�̕���
	const Vector3 MAGNET_LIG_AMBIENT = { 0.8f,0.8f,0.8f };			//���΂̃��C�g�̊����̋���
	const float MAGNET_METARIC = 1.0f;								//���΂̋����x
	const float MAGNET_SMOOTH = 0.35f;								//���΂̂Ȃ߂炩��
	const float MAGNET_POW_VALUE = 10.0f;							//�i�藦
}

class Magnet : public IGameObject
{
private:
	~Magnet();
	bool Start() override final;
	void Update() override final;

public:

	/**
	 * @brief ���ɂ�N�ɂ���֐��B
	 * @param plusflg �������΂��ǂ����̃t���O
	*/
	void SetState_N(bool plusflg = false) {
		m_magState = State_N;
		m_ligData.m_directionLigData[enData_Zeroth].Col.Set(MAGNET_N_LIG_COLOR);
		if (plusflg) {
			m_plusFlg = true;
		}
	}
	/**
	 * @brief ���ɂ�S�ɂ���֐��B
	 * @param plusflg �������΂��ǂ����̃t���O
	*/
	void SetState_S(bool plusflg = false) {
		m_magState = State_S;
		m_ligData.m_directionLigData[enData_Zeroth].Col.Set(MAGNET_S_LIG_COLOR);
		if (plusflg) {
			m_plusFlg = true;
		}
	}

	/**
	 * @brief �P/���{�̌v�Z������֐��B
	 * @param n ����
	 * @return 1/n�{�������ʂ̒l
	*/
	float ReturnReciprocal(float n) {

		float value = n;
		//n = 0�Ȃ疳����ɔ��U����̂�n = 0.0001f�Ƃ���B
		if (value == 0) {
			value = 0.0001f;
		}

		//�v�Z���ʂ�Ԃ��B
		return 1.0f / value;
	}

	/**
	 * @brief ���W��ݒ肷��֐��B
	 * @param pos ���W
	*/
	void SetPosition(Vector3 pos) { m_pos = pos; }

	/**
	 * @brief ��]����ݒ肷��֐��B
	 * @param rot ��]��
	*/
	void SetRotation(const Quaternion& rot) {
		m_rot = rot;
	}

	/**
	 * @brief �g�嗦��ݒ肷��֐��B
	 * @param sca �g�嗦
	*/
	void SetScale(const Vector3& sca) {
		m_sca = sca;
	}

	/**
	 * @brief ���W���擾����֐��B
	 * @return ���W
	*/
	Vector3 GetPosition() { return m_pos; }

	/**
	 * @brief �g���K�[�{�b�N�X���쐬����֐��B
	 * @param type �g���K�[�{�b�N�X�̃^�C�v
	*/
	void CreateTriggerBox(int type);

	/**
	 * @brief �v���C���[�ɗ͂�^����֐��B
	*/
	void SetMagnetPower();

	/**
	 * @brief ���΂̉e���͈͂����߂�֐��B
	 * @param stageNum �X�e�[�W�ԍ�
	*/
	void SetMagnetTriggerBox(int stageNum);

	/**
	 * @brief ���΂̔ԍ���ݒ肷��֐��B
	 * @param num �X�e�[�W�ԍ�
	*/
	void SetMagnetNum(int num) {
		m_magnetNum = num;
	}

	/**
	 * @brief ���΂̊�_��ݒ肷��֐��B
	 * @param pos ��_�ƂȂ���W
	*/
	void SetMagnetPosition(const Vector3& pos) {
		m_magnetPos = pos;
	}

	/**
	 * @brief �������֐��B
	 * @param magnetName ���΂̖��O
	*/
	void Init(const char* magnetName)
	{
		char filePathtkm[NAME_SIZE];

		//���O���烂�f�����쐬�B
		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", magnetName);
		m_skinModelRender = NewGO<SkinModelRender>(enPriority_Zeroth);
		m_skinModelRender->SetFileNametkm(filePathtkm);

		//�V���h�E���󂯂�t���O��ݒ�
		m_skinModelRender->SetShadowReceiverFlag(true);

		//�y�v���p�X�t���O��ݒ�
		m_skinModelRender->SetZprepassFlag(true);

		//���C�g�̕�����ݒ�
		m_ligData.m_directionLigData[enData_Zeroth].Dir.Set(MAGNET_LIG_DIR);
		m_ligData.m_directionLigData[enData_Zeroth].Dir.Normalize();
		
		//������ݒ�
		m_ligData.ambient.Set(MAGNET_LIG_AMBIENT);
		//�����x��ݒ�
		m_ligData.metaric = MAGNET_METARIC;
		//�Ȃ߂炩����ݒ�
		m_ligData.smooth = MAGNET_SMOOTH;
		//�֊s����ݒ�
		m_ligData.edge = Edge_1;
		//�i�藦��ݒ�
		m_ligData.powValue = MAGNET_POW_VALUE;
		//���C�g�f�[�^����Ǝ��̃��C�g��ݒ�
		m_skinModelRender->SetUserLigData(&m_ligData);
		//�J���[�o�b�t�@�̃t�H�[�}�b�g���w��
		m_skinModelRender->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);
		//������
		m_skinModelRender->Init();
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

	//���͂̉e���͈͂̃T���v��
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


	bool m_plusFlg = false;							//�������΃t���O
	bool m_moveFlg = false;							//�����t���O
	int m_magnetNum = 0;							//���Δԍ�
	int m_timer = 0;								//<�ύX>�������΂̈ꎞ��~�̂���m_timer��ǉ�
	Vector3 m_length = Vector3::Zero;				//�v���C���[�Ƃ̋���
	Vector3 m_pos = Vector3::Zero;					//���W
	Quaternion m_rot = Quaternion::Identity;		//��]��
	Vector3 m_sca = Vector3::One;					//�g�嗦
	Vector3 m_magnetPos = Vector3::Zero;			//���͂̔����ꏊ�B��_�͍����Ȃ��߁A���S�ɂ���
	Vector3 m_moveRange_front = Vector3::Zero;		//�ړ��͈͂̍��[
	Vector3 m_moveRange_back = Vector3::Zero;		//�ړ��͈͂̉E�[
	Vector3 m_moveSpeed = Vector3::Zero;			//��������

	Magnet_State m_magState = State_N;				//���ɂ̃X�e�[�g�B
	PhysicsStaticObject m_physicsStaticObject;		//�����蔻��
	CPhysicsGhostObject m_ghostBox;					//�g���K�[�{�b�N�X
	LigData m_ligData;								//���C�g�̃f�[�^

	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	SkinModelRender* m_skinModelRender = nullptr;
	Player* m_player = nullptr;
	Key* m_key = nullptr;
	Game* m_game = nullptr;
};

