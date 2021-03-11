#pragma once

class DirectionLight;

class Player : public IGameObject
{
public:
	bool Start() override;
	void Update() override;

	//現在のステートを取得する関数。
	const int GetPlayerState()const { return pState; }

	//現在の座標を取得する関数。
	const Vector3 GetPosition()const { return m_charaCon.GetPosition(); }

	//外部から力を受け取る関数。
	//pow：力の大きさ
	void ReceivePower(Vector3 pow)const { m_movePower += pow; }

	void ChangeState();

	void Render(RenderContext& rc)override;

private:
	/// <summary>
	/// アニメーションクリップ。
	/// </summary>
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};

	typedef enum {
		State_N,
		State_S,
	}Player_State;

	enum EnPlayer {
		enPlayer_0,
		enPlayer_1,
		enPlayer_Num
	};
	//プレイヤーのステート。
	Player_State pState = State_N;

	Model m_model;			//モデル表示処理。
	ModelInitData initData;
	Animation m_animation;	//アニメション再生処理。
	AnimationClip m_animationClips[enAnimClip_Num];	//アニメーションクリップ。
	Skeleton m_skeleton;	//スケルトン。
	CharacterController m_charaCon;

	DirectionLight* m_dirLight = nullptr;
	Vector3 m_pos = { 500.0f,300.0f,20.0f };
	mutable Vector3 m_movePower;

	SkinModelRender* m_skinModelRender[enPlayer_Num] = { nullptr };
	Font m_font;
};

