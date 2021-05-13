#include "stdafx.h"
#include "DirectionLight.h"


void SkinModelRender::Init(bool DirectionFlg, bool PointLightFlg) {

	//char textureDir[256];
	//strncpy_s(textureDir, ModelFileName, 256);
	//auto p = strrchr(textureDir, '/');
	//if (p == nullptr) {
	//	//\�}�[�N�������B
	//	p = strrchr(textureDir,'\\');
	//	if (p == nullptr) {
	//		
	//	}
	//}
	//*p = '\0';
	////�X�P���g���̃f�[�^��ǂݍ��݁B
	//std::string skeletonFilePath = ModelFileName;
	//int pos = (int)skeletonFilePath.find(".tkm");
	//skeletonFilePath.replace(pos, 4, ".tks");
	//m_skeleton.Init(skeletonFilePath.c_str());
	//initData.m_tkmFilePath = m_modelFileName;



	//tkm�t�@�C���̃��[�h�B
	if (m_fileNametkm != nullptr) {
		initData.m_tkmFilePath = m_fileNametkm;
	}
	else {
		//�G���[�����B
	}

	//tks�t�@�C���̃��[�h�B
	if (m_fileNametks != nullptr) {
		m_skeleton.Init(m_fileNametks);
	}
	else {
		//�G���[�����B
	}

	initData.m_vsEntryPointFunc = "VSMain";
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";


	if (!m_shadowReceiverFlag) {
		initData.m_fxFilePath = "Assets/shader/model.fx";
		if(m_userLigData){
			//���[�U�[�ŗL�̃��C�g���g���B
			//initData.m_expandConstantBuffer = m_userLigData;

			//�܂������r���Ȃ̂ŋ��ʂ̃��C�g���g���B
			initData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
		}
		else {
			//�O���[�o�����C�g���g���B
			initData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
		}
		
		initData.m_expandConstantBufferSize = sizeof(*LightManager::GetInstance()->GetLigData());
	}
	else {
		initData.m_fxFilePath = "Assets/shader/sampleShadowReciever.fx";
		//initData.m_fxFilePath = "Assets/shader/model.fx";
		initData.m_vsEntryPointFunc = "VSMain";
		initData.m_vsSkinEntryPointFunc = "VSMain";
		//�V���h�E�}�b�v���g��SRV�ɐݒ肷��B
		initData.m_expandShaderResoruceView = &RenderTarget::GetShadowMap()->GetRenderTargetTexture();

		//m_lightCameraData.m_viewProj = Camera::GetLightCamera()->GetViewProjectionMatrix();
		//m_lightCameraData.eyePos = g_camera3D->GetPosition();

		if (m_userLigData) {
			//���[�U�[�ŗL�̃��C�g���g���B
			//initData.m_expandConstantBuffer = m_userLigData;
			initData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
		}
		else {
			//�O���[�o�����C�g���g���B
			initData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
		}
		initData.m_expandConstantBufferSize = sizeof (*LightManager::GetInstance()->GetLigData());
		////���C�g�r���[�v���W�F�N�V�����s����g���萔�o�b�t�@�ɐݒ肷��B
		//initData.m_expandConstantBuffer = (void*)&(Camera::GetLightCamera()->GetViewProjectionMatrix());
		//initData.m_expandConstantBufferSize = sizeof(Camera::GetLightCamera()->GetViewProjectionMatrix());

		//initData.m_expandConstantBuffer = (void*)&m_lightCameraData;
		//initData.m_expandConstantBufferSize = sizeof(m_lightCameraData);
		
	}

	if (m_skeleton.IsInited()) {
		initData.m_skeleton = &m_skeleton;
	}
//	initData.m_modelUpAxis = enModelUpAxisY;

	//�f�B���N�V�������C�g�̐ݒ�B
	//if (DirectionFlg) {
		//m_directionLight = NewGO<DirectionLight>(0);
		//m_directionLight->SetLigDirection(1.0f, 1.0f, 1.0f);
		//m_directionLight->SetLigColor(0.5f, 0.5f, 0.5f);
		//initData.m_expandConstantBuffer = m_directionLight->GetLigData();
	//}

	if (m_shadowCasterFlag) {

		ModelInitData ShadowModelInitData;
		ShadowModelInitData.m_fxFilePath = "Assets/shader/sampleDrawShadowMap.fx";
		ShadowModelInitData.m_tkmFilePath = m_fileNametkm;
		ShadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32_FLOAT;

		m_shadowModel.Init(ShadowModelInitData);
		m_shadowModel.UpdateWorldMatrix(
			m_pos,
			g_quatIdentity,
			g_vec3One
		);
	}

	//�쐬�����������f�[�^�����ƂɃ��f��������������A
	m_model.Init(initData);

	m_animation.Init(m_skeleton, m_animClip, m_animNum);
}

void SkinModelRender::Update() {

	//�X�P���g�����X�V�B
	m_skeleton.Update(m_model.GetWorldMatrix());
	//�A�j���[�V������i�߂�B
	m_animation.Progress(1.0f / 60.0f);

	m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
	m_shadowModel.UpdateWorldMatrix(
		m_pos,
		m_rot,
		m_sca
	);

	//�J�����̏���������߂�B
	Vector3 Vec_x = { 1.0f,0.0f,0.0f };
	Vector3 TarPos = Camera::GetLightCamera()->GetTarget() - Camera::GetLightCamera()->GetPosition();
	TarPos.Normalize();
	Vector3 CameraUp;

	CameraUp.Cross(TarPos, Vec_x);
	CameraUp.Normalize();

	//Camera::GetLightCamera()->SetPosition(Cpos);
	//Camera::GetLightCamera()->SetTarget(CTar);
	Camera::GetLightCamera()->SetUp(CameraUp);
	//Camera::GetLightCamera()->SetUp(1, 0, 0);
	Camera::GetLightCamera()->Update();
}

void SkinModelRender::Render(RenderContext& rc)
{
	auto ligCame = Camera::GetLightCamera();
	switch (rc.GetRenderMode()) {
	case RenderContext::Render_Mode::RenderMode_Shadow:
		m_shadowModel.Draw(rc,*Camera::GetLightCamera());
		break;
	case RenderContext::Render_Mode::RenderMode_Normal:
		m_model.Draw(rc);
		break;
	}
}
