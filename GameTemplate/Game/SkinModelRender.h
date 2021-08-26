#pragma once

class SkinModelRender : public IGameObject
{
	struct LightCameraData{
		Matrix m_viewProj;
		Vector3 eyePos;
	};

	struct SModelData {
		int ligID = 0;
	};
public:
	//SkinModelRender();
	//初期化。
	//directionFlg:ディレクションライトの影響を受けるか。
	//pointLightFlg:ポイントライトの影響を受けるか。
	void Init();

	//tkmファイルのロード。
	void SetFileNametkm(const char* name) { m_fileNametkm = name; }

	//tksファイルのロード。
	void SetFileNametks(const char* name) { m_fileNametks = name; }

	//カラーバッファーフォーマットの指定。
	void SetColorBufferFormat(DXGI_FORMAT colorBufferFormat) {
		initData.m_colorBufferFormat = colorBufferFormat;
	}

	//アニメーション初期化関数。
	void InitAnimation(AnimationClip* animClip, int animNum) {
		m_animClip = animClip;
		m_animNum = animNum;
	}

	void SetAnimFlg(bool flg) {
		m_animFlg = flg;
	}

	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	//モデルを取得。
	Model* GetModel() { return &m_model; }

	//スケルトンを取得。
	Skeleton* GetSkeleton() { return &m_skeleton; }
	
	void SetPosition(const Vector3& pos) { m_pos = pos; }
	void SetRotation(const Quaternion& rot) { m_rot = rot; }
	void SetScale(const Vector3& sca) { m_sca = sca; }
	void Render(RenderContext& rc) override;

	void Update()override final;
	//ワールド行列を更新する。
	//ワールド行列の更新は、毎フレーム一度行われていますが、
	//このクスの使用者の任意のタイミングで更新したいときは、
	//この関数を利用してください。
	void UpdateWorldMatrix()
	{
		m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
		m_zprepassModel.UpdateWorldMatrix(m_pos, m_rot, m_sca);
		m_shadowModel.UpdateWorldMatrix(m_pos, m_rot, m_sca);
	}

	void UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 sca)
	{
		m_model.UpdateWorldMatrix(pos, rot, sca);
		m_zprepassModel.UpdateWorldMatrix(pos, rot, sca);
		m_shadowModel.UpdateWorldMatrix(pos, rot, sca);
	}

	//シャドウキャスターフラグを設定。
	void SetShadowCasterFlag(bool flg) {

		m_shadowCasterFlag = flg;
	}

	void SetShadowReceiverFlag(bool flg) {

		m_shadowReceiverFlag = flg;
	}

	void SetZprepassFlag(bool flg) {
		m_zPrepassFlg = true;
	}

	void SetExpandShaderResourceView(IShaderResource* expandShaderResoruceView) {
		initData.m_expandShaderResoruceView = expandShaderResoruceView;
	}
	void SetExpandShaderResourceView_2(IShaderResource* expandShaderResoruceView_2) {
		initData.m_expandShaderResoruceView_2 = expandShaderResoruceView_2;
	}
	void SetUserModelOption(ModelOption* modelOption) {
		m_userModelOption = modelOption;
	}

	void SetLigID(int ligID) {
		m_modelData.ligID = ligID;
	}
private:
	bool m_animFlg = false;
	bool m_shadowCasterFlag = false;	//シャドウキャスターフラグ。
	bool m_shadowReceiverFlag = false;	//シャドウレシーバーフラグ。
	bool m_zPrepassFlg = false;
	int m_animNum = 0;
	const char* m_fileNametkm = nullptr;
	const char* m_fileNametks = nullptr;
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_sca = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;
	SModelData m_modelData;

	Model m_model;			//モデル表示処理。
	Model m_shadowModel;	//シャドウ作成用のモデル。
	Model m_zprepassModel;   // ZPrepassで描画されるモデル
	ModelInitData initData;
	Animation m_animation;	//アニメション再生処理。
	AnimationClip* m_animClip;
	Skeleton m_skeleton;	//スケルトン。

	LightCameraData m_lightCameraData;
	ModelOption* m_userModelOption = nullptr;	//モデルオプション

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	DirectionLight* m_directionLight = nullptr;
};

