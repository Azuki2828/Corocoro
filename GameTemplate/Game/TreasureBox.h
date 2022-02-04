#pragma once
class Player;
class Game;

class TreasureBox : public IGameObject
{
	//�󔠂̃A�j���[�V�������X�g
	enum TreasureBoxAnimation {
		enAnimation_Open,

		enAnimation_Num
	};
private:
	bool Start()override;
	~TreasureBox();
	void Update()override;

public:
	/**
	 * @brief ���W��ݒ肷��֐��B
	 * @param pos ���W
	*/
	void SetPosition(const Vector3& pos) {
		m_pos = pos;
	}

	/**
	 * @brief ���W���擾����֐��B
	 * @return ���W
	*/
	Vector3 GetPosition() {
		return m_pos;
	}

	/**
	 * @brief 
	 * @param rot 
	*/
	void SetRotation(const Quaternion& rot) {
		m_rot = rot;
	}

	void SetScale(const Vector3& sca) {
		m_sca = sca;
	}

	bool GetTreasureFlg() {

		return m_treasureFlg;
	}

private:
	bool m_soundFlg = false;
	bool m_treasureFlg = false;
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_sca = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;

	ModelOption m_modelOption;
	Animation m_animation;
	AnimationClip m_animClip;
	PhysicsStaticObject m_physicsStaticObject;	//�����蔻��
	CPhysicsGhostObject m_ghostBox;

	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	Effect* m_effect = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
};

