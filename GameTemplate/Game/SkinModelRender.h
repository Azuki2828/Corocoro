#pragma once

class DirectionLight;

class SkinModelRender : public IGameObject
{
public:
	//SkinModelRender();
	//初期化。
	//directionFlg:ディレクションライトの影響を受けるか。
	//pointLightFlg:ポイントライトの影響を受けるか。
	void Init(bool directionFlg = false, bool pointLightFlg = false);

	//tkmファイルのロード。
	void SetFileNametkm(const char* name) { m_fileNametkm = name; }

	//tksファイルのロード。
	void SetFileNametks(const char* name) { m_fileNametks = name; }

	//アニメーション初期化関数。
	void InitAnimation(AnimationClip* animClip, int animNum) {
		m_animClip = animClip;
		m_animNum = animNum;
	}

	//モデルを取得。
	Model* GetModel() { return &m_model; }

	//スケルトンを取得。
	Skeleton* GetSkeleton() { return &m_skeleton; }
	
	void SetPosition(Vector3 pos) { m_pos = pos; }
	void SetRotation(Quaternion rot) { m_rot = rot; }
	void SetScale(Vector3 sca) { m_sca = sca; }
	void Render(RenderContext& rc) override;

	void Update()override final;
	//ワールド行列を更新する。
	//ワールド行列の更新は、毎フレーム一度行われていますが、
	//このクスの使用者の任意のタイミングで更新したいときは、
	//この関数を利用してください。
	void UpdateWorldMatrix()
	{
		m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
	}

	void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 sca)
	{
		m_model.UpdateWorldMatrix(pos, rot, sca);
	}

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

