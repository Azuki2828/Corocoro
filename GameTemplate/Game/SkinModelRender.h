#pragma once

class DirectionLight;

class SkinModelRender : public IGameObject
{
public:
	SkinModelRender() {}
	void Init(const char* ModelFileName, bool DirectionFlg = false, bool PointLightFlg = false);

	void InitSkeleton();
	void InitModel(void* data);
	void InitAnimation();

	Model m_model;			//モデル表示処理。
	ModelInitData initData;
	Animation m_animation;	//アニメション再生処理。
	Skeleton m_skeleton;	//スケルトン。

	DirectionLight* m_directionLight = nullptr;

private:
	const char* m_modelFileName = nullptr;
	struct DirectionLightData {
		Vector3 Direction;
		Vector3 Color;
	};
	DirectionLightData m_directionLightData;
};

