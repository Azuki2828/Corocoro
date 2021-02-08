#pragma once

class DirectionLight;

class SkinModelRender : public IGameObject
{
public:
	void Init(bool directionFlg = false, bool pointLightFlg = false);
	void SetFileNametkm(const char* name) { m_fileNametkm = name; }
	void SetFileNametks(const char* name) { m_fileNametks = name; }
	void InitAnimation(AnimationClip* animClip, int animNum) {
		m_animation.Init(m_skeleton, animClip, animNum);
	}

	Model m_model;			//モデル表示処理。
	ModelInitData initData;
	Animation m_animation;	//アニメション再生処理。
	AnimationClip m_animClip;
	Skeleton m_skeleton;	//スケルトン。

	DirectionLight* m_directionLight = nullptr;

private:
	const char* m_fileNametkm = nullptr;
	const char* m_fileNametks = nullptr;
	//struct DirectionLightData {
	//	Vector3 Direction;
	//	Vector3 Color;
	//};
	//DirectionLightData m_directionLightData;
};

