#include "stdafx.h"
#include "SkinModelRender.h"

void SkinModelRender::Init(const char* ModelFileName) {

	m_modelFileName = ModelFileName;

	char textureDir[256];
	strncpy_s(textureDir, ModelFileName, 256);
	auto p = strrchr(textureDir, '/');
	if (p == nullptr) {
		//\�}�[�N�������B
		p = strrchr(textureDir,'\\');
		if (p == nullptr) {
			
		}
	}
	*p = '\0';
	//�X�P���g���̃f�[�^��ǂݍ��݁B
	std::string skeletonFilePath = ModelFileName;
	int pos = (int)skeletonFilePath.find(".tkm");
	skeletonFilePath.replace(pos, 4, ".tks");
	m_skeleton.Init(skeletonFilePath.c_str());

	//���f���f�[�^�����[�h�B
	//m_modelDx = GraphicsEngine().GetDirectXModelResource().Load(filePath, m_skeleton);
	//if (m_modelDx != nullptr) {
	//	//�C���X�^���X�����p�\�B
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
