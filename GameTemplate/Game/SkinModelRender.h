#pragma once

class DirectionLight;

class SkinModelRender : public IGameObject
{
public:
	//SkinModelRender();
	void Init(bool directionFlg = false, bool pointLightFlg = false);
	void SetFileNametkm(const char* name) { m_fileNametkm = name; }
	void SetFileNametks(const char* name) { m_fileNametks = name; }
	void InitAnimation(AnimationClip* animClip, int animNum) {
		m_animClip = animClip;
		m_animNum = animNum;
	}
	void SetPosition(Vector3 pos) { m_pos = pos; }
	void SetRotation(Quaternion rot) { m_rot = rot; }
	void SetScale(Vector3 sca) { m_sca = sca; }
	void Render(RenderContext& rc) override;

	void Update()override final;

private:
	int m_animNum;
	const char* m_fileNametkm = nullptr;
	const char* m_fileNametks = nullptr;

	Model m_model;			//モデル表示処理。
	ModelInitData initData;
	Animation m_animation;	//アニメション再生処理。
	AnimationClip* m_animClip;
	Skeleton m_skeleton;	//スケルトン。

	DirectionLight* m_directionLight = nullptr;

	Vector3 m_pos = Vector3::Zero;
	Vector3 m_sca = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;

	//struct DirectionLightData {
	//	Vector3 Direction;
	//	Vector3 Color;
	//};
	//DirectionLightData m_directionLightData;
};

