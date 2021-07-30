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

	/**
	 * @brief 現在のステートを取得する関数。
	 * @return プレイヤーのステート
	*/
	int GetPlayerState()const { return pState; }

	/**
	 * @brief 座標を取得する関数。
	 * @return 座標
	*/
	const Vector3 GetPosition()const { return m_pos; }

	/**
	 * @brief 剛体を取得する関数。
	 * @return 剛体
	*/
	RigidBody* GetRigidBody() { return &m_rigidBody; }

	/**
	 * @brief 外部から力を受け取る関数。
	 * @param pow 力の大きさ
	*/
	void ReceivePower(Vector3 pow) { m_movePower += pow; }

	/**
	 * @brief 力を初期化する関数。
	*/
	void ClearPower() { m_rigidBody.ClearPower(); }

	/**
	 * @brief プレイヤーの磁極を変換する関数。
	*/
	void ChangeState();

	/**
	 * @brief 座標を設定する関数。
	 * @param pos 座標
	*/
	void SetPosition(const Vector3& pos) {
		m_pos = pos;
		m_rigidBody.SetPositionAndRotation(m_pos, m_rot);
	}

	/**
	 * @brief プレイヤーの開始地点を設定する関数。
	 * @param pos 開始地点の座標
	*/
	void SetStartPos(const Vector3& pos) {
		m_startPos = pos;
		m_rigidBody.SetPositionAndRotation(m_startPos, m_rot);
		for (int i = 0; i < enPlayer_Num; i++) {
			m_skinModelRender[i]->SetPosition(m_startPos);
			m_skinModelRender[i]->SetRotation(m_rot);
			m_skinModelRender[i]->UpdateWorldMatrix();
		}
	}

	/**
	 * @brief プレイヤーの開始地点を取得する関数。
	 * @return 開始地点の座標
	*/
	Vector3 GetStartPos() {
		return m_startPos;
	}

	/**
	 * @brief 鍵取得フラグを設定する関数。
	 * @param flg 鍵取得フラグ
	*/
	void SetKeyFlg(bool flg) { m_getKeyFlg = flg; }
	/**
	 * @brief 鍵取得フラグを取得する関数。
	 * @return 鍵取得フラグ
	*/
	bool GetKeyFlg() { return m_getKeyFlg; }

	/**
	 * @brief 宝箱を取得したかどうかを調べる関数。
	 * @return 宝箱を取得したかのフラグ
	*/
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
	const bool GetRespawn()const
	{
		return m_respawnFlg;
	}

	/**
	 * @brief スポーンフラグを設定する。
	 * @param b フラグ。
	*/
	void SetRespawn(const bool respawnFlg) 
	{
		m_respawnFlg = respawnFlg;
	}
	
	/**
	 * @brief プレイヤーモデルの更新をtrueにする関数。
	 * @param i プレイヤー番号
	*/
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

	/**
	 * @brief プレイヤーモデルの更新をfalseにする関数。
	 * @return プレイヤー番号
	*/
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
	/**
	 * @brief 磁極
	*/
	typedef enum {
		State_N,
		State_S,
	}Player_State;

	/**
	 * @brief アニメーションクリップ
	*/
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};
	/**
	 * @brief プレイヤー番号
	*/
	enum EnPlayer {
		enPlayer_0,
		enPlayer_1,
		enPlayer_Num
	};
	bool m_getKeyFlg = false;		//鍵取得フラグ。
	bool m_keySoundFlg = false;		//鍵取得SEの再生フラグ
	bool m_deathFlag = false;		//プレイヤーが死亡しているかのフラグ
	bool m_respawnFlg = false;		//リスポーンが完了しているかのフラグ
	float m_deathPosY = 0.0f;		//死亡する高さ

	Vector3 m_pos = Vector3::Zero;					//座標
	Vector3 m_startPos;								//開始地点の座標
	Vector3 m_movePower;							//動力。
	Quaternion m_rot = Quaternion::Identity;		//回転率
	Font m_font;									//フォント
	Model m_model;									//モデル
	ModelInitData initData;							//モデルのデータ。
	Skeleton m_skeleton;							//スケルトン
	SphereCollider m_sphereCollider;				//プレイヤーのコライダー
	RigidBody m_rigidBody;							//剛体
	Animation m_animation;							//アニメション
	AnimationClip m_animationClips[enAnimClip_Num];	//アニメーションクリップ

	Player_State pState = State_N;					//プレイヤーの磁力の状態
	LigData m_ligData[enPlayer_Num];				//プレイヤーのライトのデータ


	//それぞれのクラスのポインタ

	SkinModelRender* m_skinModelRender[enPlayer_Num] = { nullptr };
	Key* m_key = nullptr;
	TreasureBox* m_treasureBox = nullptr;
	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	DirectionLight* m_dirLight = nullptr;
	Effect* m_NCahgeState = nullptr;
	Effect* m_SCahgeState = nullptr;
};