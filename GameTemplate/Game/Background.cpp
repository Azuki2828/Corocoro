#include "stdafx.h"
#include "Background.h"
#include "Magnet.h"

bool Background::Start()
{
	m_magnet.resize(1);
	int sampleNum = 0;
	const char* MagnetName[] = {
		"Assets/modelData/tkm/SampleMagnet_N_01.tkm",
		"Assets/modelData/tkm/SampleMagnet_S_01.tkm"
	};
	//m_spriteRender = NewGO<SpriteRender>(0);
	//m_spriteRender->Init("Assets/Image/sample.dds", 1980.0f, 1080.0f);

	//���ꂪlevel��Load�̊�ՁB
	//����̃I�u�W�F�N�g���w�肷��i�����ł����t�b�N�j�ꍇ�́A���O��������Ȃ̂ˁB
	m_level.Init("Assets/level/SampleLevel.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"SampleMagnet_N_01") == true) {
			m_magnet.push_back(*(m_magnet.end()-1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init(MagnetName[sampleNum]);
			sampleNum++;
			return true;
		}
		/*else if (objData.EqualObjectName(L"SampleMagnet_S_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init(MagnetName[sampleNum]);
			sampleNum++;
			return true;
		}*/

		//if (objData.EqualObjectName(L"stage02_goal") == true) {
		//	return true;
		//}
		////else if (objData.EqualObjectName(L"") == true) {
		////	return true;
		////}
		//else if (objData.EqualObjectName(L"KeyBox") == true) {
		//	return true;
		//}
		return false;//level�̃I�u�W�F�N�g�����̂܂܃��[�h�B
	});
	//ModelInitData initData;
	//initData.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	////�V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��B
	//initData.m_fxFilePath = "Assets/shader/model.fx";
	////���_�V�F�[�_�[�̃G���g���[�|�C���g
	//initData.m_vsEntryPointFunc = "VSMain";
	//m_model.Init(initData);
	//
	////���b�V���R���C�_�[���쐬�B
	//m_physicsStaticObject.CreateFromModel(m_model, m_model.GetWorldMatrix());
	return true;
}
void Background::Update()
{

}
void Background::Render(RenderContext& rc)
{
	m_level.Draw(rc);
	m_model.Draw(rc);
}