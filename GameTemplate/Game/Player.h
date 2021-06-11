#pragma once
#include "Key.h"
#include "TreasureBox.h"

class Key;
class BackGround;
class Game;
class TreasureBox;

class Player : public IGameObject
{
private:
	bool Start() override;
	~Player();
	void Update() override;
	void FreeUpdate()override;

public:

	//現在のステートを取得する関数。
	const int GetPlayerState()const { return pState; }

	//現在の座標を取得する関数。
	const Vector3 GetPosition()const { return m_pos; }

	RigidBody* GetRigidBody() { return &m_rigidBody; }

	//外部から力を受け取る関数。
	//pow：力の大きさ
	void ReceivePower(Vector3 pow) { m_movePower += pow; }

	void ClearPower() { m_rigidBody.ClearPower(); }

	//プレイヤーの磁極を変換する関数。
	void ChangeState();

	void SetPosition(const Vector3& pos) {
		m_pos = pos;
		m_rigidBody.SetPositionAndRotation(m_pos, m_rot);
	}

	void SetStartPos(const Vector3& pos) {
		m_startPos = pos;
		m_rigidBody.SetPositionAndRotation(m_startPos, m_rot);
		for (int i = 0; i < enPlayer_Num; i++) {
			m_skinModelRender[i]->SetPosition(m_startPos);
			m_skinModelRender[i]->SetRotation(m_rot);
			m_skinModelRender[i]->UpdateWorldMatrix();
		}
	}

	Vector3 GetStartPos() {
		return m_startPos;
	}
	void SetKeyFlg(bool flg) { m_getKeyFlg = flg; }
	bool GetKeyFlg() { return m_getKeyFlg; }

	bool GetTreasureFlg() {
		if (m_treasureBox == nullptr) {
			return false;
		}
		else{
			return m_treasureBox->GetTreasureFlg();
		}
	};

	
	/**
	 * @brief スポーンフラグを取得。
	 * @return すポーンフラグ
	*/
	const bool Getrespawn()const
	{
		return m_respawnFlg;
	}

	/**
	 * @brief スポーンフラグを設定する。
	 * @param b フラグ。
	*/
	void Setrespawn(const bool b) 
	{
		m_respawnFlg = b;
	}
	/// <summary>
	/// プレイヤーモデルの表示
	/// </summary>
	void ActivatePlayerModel(int i)
	{
		m_deathFlag = false;

		if (i == enPlayer_0) {
			m_skinModelRender[enPlayer_0]->Activate();
		}
		else if (i == enPlayer_1) {
			m_skinModelRender[enPlayer_1]->Activate();
		}
	}

	/// <summary>
	/// プレイヤーモデルの削除
	/// </summary>
	int DeactivatePlayerModel()
	{
		m_deathFlag = true;

		if (m_skinModelRender[enPlayer_0]->IsActive()) {
			m_skinModelRender[enPlayer_0]->Deactivate();
			return enPlayer_0;
		}
		else if (m_skinModelRender[enPlayer_1]->IsActive()) {
			m_skinModelRender[enPlayer_1]->Deactivate();
			return enPlayer_1;
		}
	}
private:
	/// <summary>
	/// 磁極。
	/// </summary>
	typedef enum {
		State_N,
		State_S,
	}Player_State;

	/// <summary>
	/// アニメーションクリップ。
	/// </summary>
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};
	/// <summary>
	/// プレイヤーの登録番号。
	/// </summary>
	enum EnPlayer {
		enPlayer_0,
		enPlayer_1,
		enPlayer_Num
	};
	bool m_getKeyFlg = false;		//鍵取得フラグ。
	bool m_keySoundFlg = false;
	bool m_startFlg = false;
	bool m_resetPosFlg = false;
	bool m_deathFlag = false; //プレイヤーが死亡しているかのフラグ
	bool m_respawnFlg = false;
	float m_deathPosY = 0.0f;

	Vector3 m_pos = { 300.0f,1300.0f,-300.0f };		//初期座標。ステージ３
	Vector3 m_startPos;
	Vector3 m_movePower;						//動く力。
	Quaternion m_rot = Quaternion::Identity;
	Font m_font;
	Model m_model;										//モデル表示処理。
	ModelInitData initData;								//モデルのデータ。
	Skeleton m_skeleton;								//スケルトン。
	SphereCollider m_sphereCollider;
	RigidBody m_rigidBody;
	Animation m_animation;								//アニメション再生処理。
	AnimationClip m_animationClips[enAnimClip_Num];		//アニメーションクリップ。

	Player_State pState = State_N;
	LigData m_ligData[enPlayer_Num];


	//それぞれのクラスのポインタ

	SkinModelRender* m_skinModelRender[enPlayer_Num] = { nullptr };
	Key* m_key = nullptr;
	TreasureBox* m_treasureBox = nullptr;
	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	DirectionLight* m_dirLight = nullptr;				//ディレクションライト。
	Effect* m_NCahgeState;
	Effect* m_SCahgeState;
};