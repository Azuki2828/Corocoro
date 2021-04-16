#pragma once

class Key;
class Background;

class Player : public IGameObject
{
private:
	bool getKeyFlg = false;		//鍵取得フラグ。

public:
	bool Start() override;
	~Player();
	void Update() override;

	//現在のステートを取得する関数。
	const int GetPlayerState()const { return pState; }

	//現在の座標を取得する関数。
	const Vector3 GetPosition()const { return m_pos; }

	//外部から力を受け取る関数。
	//pow：力の大きさ
	void ReceivePower(Vector3 pow)const { m_movePower += pow; }

	//プレイヤーの磁極を変換する関数。
	void ChangeState();

	void Render(RenderContext& rc)override;

	void SetKeyFlg(bool flg) { getKeyFlg = flg; }
	bool GetKeyFlg() { return getKeyFlg; }

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

	Model m_model;										//モデル表示処理。
	ModelInitData initData;								//モデルのデータ。
	Animation m_animation;								//アニメション再生処理。
	AnimationClip m_animationClips[enAnimClip_Num];		//アニメーションクリップ。
	Skeleton m_skeleton;								//スケルトン。
	CharacterController m_charaCon;						//キャラコン。

	DirectionLight* m_dirLight = nullptr;				//ディレクションライト。
	Vector3 m_pos = { 300.0f,300.0f,0.0f };				//初期座標。
	Quaternion m_rot = Quaternion::Identity;
	//Vector3 m_pos = { 1500.0f,2800.0f,0.0f };
	//Vector3 m_pos = { 1500.0f,2800.0f,20.0f };
	mutable Vector3 m_movePower;						//動く力。

	SkinModelRender* m_skinModelRender[enPlayer_Num] = { nullptr };
	Font m_font;


	SphereCollider m_sphereCollider;
	RigidBody m_rigidBody;

	Key* m_key = nullptr;
	Background* m_backGround = nullptr;

	CSoundSource* NSChangeSound = nullptr;		//NS反転サウンドソース
};