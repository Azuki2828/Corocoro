#pragma once
class Player;
class Game;

class TreasureBox : public IGameObject
{
	//宝箱のアニメーションリスト
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
	 * @brief 座標を設定する関数。
	 * @param pos 座標
	*/
	void SetPosition(const Vector3& pos) {
		m_pos = pos;
	}

	/**
	 * @brief 座標を取得する関数。
	 * @return 座標
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

