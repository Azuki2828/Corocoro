#pragma once
class Player;
class Game;

class TreasureBox : public IGameObject
{
private:
	bool Start()override;
	~TreasureBox();
	void Update()override;

public:

	void SetPosition(const Vector3& pos) {
		m_pos = pos;
	}

	Vector3 GetPosition() {
		return m_pos;
	}

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

	LigData m_ligData;
	Animation m_animation;
	AnimationClip m_animClip;
	PhysicsStaticObject m_physicsStaticObject;	//当たり判定
	CPhysicsGhostObject m_ghostBox;

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	Effect* m_effect = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
};

