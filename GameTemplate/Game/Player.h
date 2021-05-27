#pragma once

#include "Key.h"
#include "TreasureBox.h"
class Key;

class Background;
class Game;
class TreasureBox;

class Player : public IGameObject
{
private:
	bool getKeyFlg = false;		//鍵取得フラグ。
	bool m_keySoundFlg = false;
	bool m_startFlg = false;
	bool m_resetPosFlg = false;

public:
	bool Start() override;
	~Player();
	void Update() override;
	void FreeUpdate()override;

	//現在のステートを取得する関数。
	const int GetPlayerState()const { return pState; }

	//現在の座標を取得する関数。
	const Vector3 GetPosition()const { return m_pos; }

	RigidBody* GetRigidBody() { return &m_rigidBody; }

	//外部から力を受け取る関数。
	//pow：力の大きさ
	void ReceivePower(Vector3 pow)const { m_movePower += pow; }

	void ClearPower() { m_rigidBody.ClearPower(); }

	//プレイヤーの磁極を変換する関数。
	void ChangeState();

	void Render(RenderContext& rc)override;

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
	void SetKeyFlg(bool flg) { getKeyFlg = flg; }
	bool GetKeyFlg() { return getKeyFlg; }

	bool GetTreasureFlg() {
		if (m_treasureBox == nullptr) {
			return false;
		}
		else{
			return m_treasureBox->GetTreasureFlg();
		}
	};

	Effect * m_NCahgeState;
	Effect* m_SCahgeState;

	const bool Getrespawn()const
	{
		return m_respawn;
	}


	void Setrespawn(const bool b) 
	{
		m_respawn = b;
	}

private:
	/// <summary>
	/// アニメーションクリップ。
	/// </summary>
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};

	/// <summary>
	/// 磁極。
	/// </summary>
	typedef enum {
		State_N,
		State_S,
	}Player_State;

	/// <summary>
	/// プレイヤーの登録番号。
	/// </summary>
	enum EnPlayer {
		enPlayer_0,
		enPlayer_1,
		enPlayer_Num
	};
	//プレイヤーのステート。
	Player_State pState = State_N;
	LigData m_ligData[enPlayer_Num];
	Model m_model;										//モデル表示処理。
	ModelInitData initData;								//モデルのデータ。
	Animation m_animation;								//アニメション再生処理。
	AnimationClip m_animationClips[enAnimClip_Num];		//アニメーションクリップ。
	Skeleton m_skeleton;								//スケルトン。

	DirectionLight* m_dirLight = nullptr;				//ディレクションライト。
	//Vector3 m_pos = { 300.0f,1200.0f,-300.0f };		//初期座標。ステージ１
	//Vector3 m_pos = { 300.0f,300.0f,-300.0f };			//初期座標。ステージ２
	Vector3 m_pos = { 300.0f,1300.0f,-300.0f };		//初期座標。ステージ３
	Vector3 m_startPos;
	Quaternion m_rot = Quaternion::Identity;
	//Vector3 m_pos = { 1500.0f,2800.0f,0.0f };
	//Vector3 m_pos = { 1500.0f,2800.0f,20.0f };
	mutable Vector3 m_movePower;						//動く力。

	SkinModelRender* m_skinModelRender[enPlayer_Num] = { nullptr };
	Font m_font;
	

//////////////////////////////
// DeathBlockの処理で使用
//////////////////////////////
private:
	bool m_deathFlag = false; //プレイヤーが死亡しているかのフラグ


public:
	/// <summary>
	/// プレイヤーモデルの表示
	/// </summary>
	void ActivatePlayerModel(int i)
	{
		m_deathFlag = false;

		if (i == 0) {
			m_skinModelRender[enPlayer_0]->Activate();
		}
		else if (i == 1) {
			m_skinModelRender[enPlayer_1]->Activate();
		}
	}

	/// <summary>
	/// プレイヤーモデルの削除
	/// </summary>
	int DeactivatePlayerModel()
	{
		m_deathFlag = true;

		if (m_skinModelRender[enPlayer_0]->IsActive() == true) {
			m_skinModelRender[enPlayer_0]->Deactivate();
			return enPlayer_0;
		}
		else if (m_skinModelRender[enPlayer_1]->IsActive() == true) {
			m_skinModelRender[enPlayer_1]->Deactivate();
			return enPlayer_1;
		}
	}

	


private:
			

	SphereCollider m_sphereCollider;
	RigidBody m_rigidBody;
	Key* m_key = nullptr;
	TreasureBox* m_treasureBox = nullptr;
	Background* m_backGround = nullptr;
	Game* m_game = nullptr;
	CSoundSource* NSChangeSound = nullptr;		//NS反転サウンドソース
	

	bool m_respawn = false;


};