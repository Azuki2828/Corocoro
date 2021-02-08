#include "stdafx.h"
#include "SkinModelRender.h"
#include "DirectionLight.h"

void SkinModelRender::Init(bool DirectionFlg = false, bool PointLightFlg = false) {

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
	initData.m_skeleton = &m_skeleton;
	initData.m_modelUpAxis = enModelUpAxisY;

	//ディレクションライトの設定。
	if (DirectionFlg) {
		m_directionLight = NewGO<DirectionLight>(0);
		m_directionLight->SetLigDirection(1.0f, 1.0f, 1.0f);
		m_directionLight->SetLigColor(0.5f, 0.5f, 0.5f);
		m_directionLight->SetEyePos();
	}
}


void SkinModelRender::InitSkeleton() {
	
}
