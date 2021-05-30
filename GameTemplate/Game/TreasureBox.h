#pragma once
class Player;
class Game;

class TreasureBox : public IGameObject
{
public:
	~TreasureBox();
	bool Start()override;
	void Update()override;

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
	bool soundFlg = false;
	bool m_treasureFlg = false;
	Effect* m_effect = nullptr;
	Vector3 m_pos;
	Quaternion m_rot;
	Vector3 m_sca;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	LigData m_ligData;
	Animation m_animation;
	AnimationClip m_animClip;
	AnimationPlayController animCon;
	PhysicsStaticObject m_physicsStaticObject;	//“–‚½‚è”»’è
	CPhysicsGhostObject m_ghostBox;
};

