#pragma once

class DirectionLight;

class Player : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	const Vector3 GetPosition()const { return m_charaCon.GetPosition(); }
private:
	/// <summary>
	/// スケルトンを初期化。
	/// </summary>
	void InitSkeleton();
	/// <summary>
	/// モデルを初期化。
	/// </summary>
	void InitModel(void* data = nullptr);
	/// <summary>
	/// アニメーションを初期化。
	/// </summary>
	void InitAnimation();
private:
	/// <summary>
	/// アニメーションクリップ。
	/// </summary>
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};
	
	Model m_model;			//モデル表示処理。
	ModelInitData initData;
	Animation m_animation;	//アニメション再生処理。
	AnimationClip m_animationClips[enAnimClip_Num];	//アニメーションクリップ。
	Skeleton m_skeleton;	//スケルトン。
	CharacterController m_charaCon;

	DirectionLight* m_dirLight = nullptr;
	Vector3 m_pos;
};

