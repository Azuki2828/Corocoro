#include "stdafx.h"
#include "SkinModelRender.h"

void SkinModelRender::Init(const char* ModelFileName) {

	m_modelFileName = ModelFileName;

	char textureDir[256];
	strncpy_s(textureDir, ModelFileName, 256);
	auto p = strrchr(textureDir, '/');
	if (p == nullptr) {
		//\マークを試す。
		p = strrchr(textureDir,'\\');
		if (p == nullptr) {
			
		}
	}
	*p = '\0';
	//スケルトンのデータを読み込み。
	std::string skeletonFilePath = ModelFileName;
	int pos = (int)skeletonFilePath.find(".tkm");
	skeletonFilePath.replace(pos, 4, ".tks");
	m_skeleton.Init(skeletonFilePath.c_str());

	//モデルデータをロード。
	//m_modelDx = GraphicsEngine().GetDirectXModelResource().Load(filePath, m_skeleton);
	//if (m_modelDx != nullptr) {
	//	//インスタンスが利用可能。
	//	m_isAvailable = true;
	//}
	//return true;


	initData.m_tkmFilePath = m_modelFileName;
	initData.m_fxFilePath = "Assets/shader/model.fx";

	initData.m_vsEntryPointFunc = "VSMain";
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";
	initData.m_skeleton = &m_skeleton;
	initData.m_modelUpAxis = enModelUpAxisY;
}


void SkinModelRender::InitSkeleton() {
	
}
