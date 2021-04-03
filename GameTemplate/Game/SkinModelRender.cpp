#include "stdafx.h"
#include "DirectionLight.h"


void SkinModelRender::Init(bool DirectionFlg, bool PointLightFlg) {

	//char textureDir[256];
	//strncpy_s(textureDir, ModelFileName, 256);
	//auto p = strrchr(textureDir, '/');
	//if (p == nullptr) {
	//	//\マークを試す。
	//	p = strrchr(textureDir,'\\');
	//	if (p == nullptr) {
	//		
	//	}
	//}
	//*p = '\0';
	////スケルトンのデータを読み込み。
	//std::string skeletonFilePath = ModelFileName;
	//int pos = (int)skeletonFilePath.find(".tkm");
	//skeletonFilePath.replace(pos, 4, ".tks");
	//m_skeleton.Init(skeletonFilePath.c_str());
	//initData.m_tkmFilePath = m_modelFileName;



	//tkmファイルのロード。
	if (m_fileNametkm != nullptr) {
		initData.m_tkmFilePath = m_fileNametkm;
	}
	else {
		//エラー処理。
	}

	//tksファイルのロード。
	if (m_fileNametks != nullptr) {
		m_skeleton.Init(m_fileNametks);
	}
	else {
		//エラー処理。
	}


	initData.m_fxFilePath = "Assets/shader/model.fx";

	initData.m_vsEntryPointFunc = "VSMain";
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";

	initData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
	initData.m_expandConstantBufferSize = sizeof*(LightManager::GetInstance()->GetLigData());

	if (m_skeleton.IsInited()) {
		initData.m_skeleton = &m_skeleton;
	}
//	initData.m_modelUpAxis = enModelUpAxisY;

	//ディレクションライトの設定。
	//if (DirectionFlg) {
		//m_directionLight = NewGO<DirectionLight>(0);
		//m_directionLight->SetLigDirection(1.0f, 1.0f, 1.0f);
		//m_directionLight->SetLigColor(0.5f, 0.5f, 0.5f);
		//initData.m_expandConstantBuffer = m_directionLight->GetLigData();
	//}

	//作成した初期化データをもとにモデルを初期化する、
	m_model.Init(initData);

	m_animation.Init(m_skeleton, m_animClip, m_animNum);
}

void SkinModelRender::Update() {

	//スケルトンを更新。
	m_skeleton.Update(m_model.GetWorldMatrix());
	//アニメーションを進める。
	m_animation.Progress(1.0f / 60.0f);

	
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
}

void SkinModelRender::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}
