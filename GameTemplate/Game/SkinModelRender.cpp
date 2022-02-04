#include "stdafx.h"
#include "DirectionLight.h"


extern GaussianBlur g_blur;

namespace {
	const char* VS_ENTRY_POINT_DEFAULT = "VSMain";
	const char* VS_ENTRY_POINT_DEFAULT_SKIN = "VSSkinMain";
	const char* FX_FILE_PATH_MODEL = "Assets/shader/model.fx";
	const char* FX_FILE_PATH_SHADOW_RECIEVER_MODEL = "Assets/shader/shadowReciever.fx";
	const char* FX_FILE_PATH_SHADOW_MAP = "Assets/shader/drawShadowMap.fx";
	const char* FX_FILE_PATH_ZPREPASS = "Assets/shader/ZPrepass.fx";
}

void SkinModelRender::Init() {

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

	initData.m_vsEntryPointFunc = VS_ENTRY_POINT_DEFAULT;
	initData.m_vsSkinEntryPointFunc = VS_ENTRY_POINT_DEFAULT_SKIN;


	if (!m_shadowReceiverFlag) {
		initData.m_fxFilePath = FX_FILE_PATH_SHADOW_RECIEVER_MODEL;
		initData.m_vsEntryPointFunc = VS_ENTRY_POINT_DEFAULT;
		initData.m_vsSkinEntryPointFunc = VS_ENTRY_POINT_DEFAULT_SKIN;
		//initData.m_expandConstantBufferSize = sizeof(*LightManager::GetInstance()->GetLigData());
		//initData.m_expandConstantBufferSize_2 = sizeof(*LightManager::GetInstance()->GetLigData());
	}
	else {
		m_modelData.ShadowRecieverflg = enShadowON;

		initData.m_fxFilePath = FX_FILE_PATH_SHADOW_RECIEVER_MODEL;
		initData.m_vsEntryPointFunc = VS_ENTRY_POINT_DEFAULT;
		initData.m_vsSkinEntryPointFunc = VS_ENTRY_POINT_DEFAULT;

		//�V���h�E�}�b�v���g��SRV�ɐݒ肷��B
		initData.m_expandShaderResoruceView = &RenderTarget::GetShadowMap()->GetRenderTargetTexture();
		initData.m_expandShaderResoruceView_2 = &g_blur.GetBokeTexture();

		//if (m_userModelOption) {
		//	LightManager::GetInstance()->AddModelOption(*m_userModelOption);
		//	//���[�U�[�ŗL�̃��C�g���g���B
		//	initData.m_expandConstantBuffer = &m_modelData;
		//}
		//else {
		//	//�O���[�o�����C�g���g���B
		//	//initData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
		//	//initData.m_expandConstantBuffer_2 = LightManager::GetInstance()->GetLigData();
		//}
		//initData.m_expandConstantBuffer = &m_modelData;
		//initData.m_expandConstantBufferSize = sizeof(m_modelData);
		//initData.m_expandConstantBufferSize = sizeof (*LightManager::GetInstance()->GetLigData());
		//initData.m_expandConstantBufferSize_2 = sizeof(*LightManager::GetInstance()->GetLigData());
	}

	if (m_userModelOption) {
		LightManager::GetInstance()->AddModelOption(*m_userModelOption, m_modelData.ligID);
		//���[�U�[�ŗL�̃��C�g���g���B
		//initData.m_expandConstantBuffer = &m_modelData;
	}
	else {
		//�O���[�o�����C�g���g���B
		//initData.m_expandConstantBuffer = &m_modelData;
	}
	initData.m_expandConstantBuffer = &m_modelData;
	initData.m_expandConstantBufferSize = sizeof(m_modelData);

	if (m_skeleton.IsInited()) {
		initData.m_skeleton = &m_skeleton;
	}

	if (m_shadowCasterFlag) {

		ModelInitData ShadowModelInitData;
		ShadowModelInitData.m_fxFilePath = FX_FILE_PATH_SHADOW_MAP;
		ShadowModelInitData.m_tkmFilePath = m_fileNametkm;
		ShadowModelInitData.m_colorBufferFormat = DXGI_FORMAT_R32_FLOAT;

		m_shadowModel.Init(ShadowModelInitData);
		m_shadowModel.UpdateWorldMatrix(
			m_pos,
			g_quatIdentity,
			g_vec3One
		);
	}
	if(m_zPrepassFlg) {
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = m_fileNametkm;
		modelInitData.m_fxFilePath = FX_FILE_PATH_ZPREPASS;
		modelInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

		m_zprepassModel.Init(modelInitData);
		m_zprepassModel.UpdateWorldMatrix(
			m_pos,
			m_rot,
			m_sca
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

	if (m_animFlg) {
		m_animation.Progress(GameTime().GameTimeFunc().GetFrameDeltaTime());
	}

	m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);


	m_shadowModel.UpdateWorldMatrix(
		m_pos,
		m_rot,
		m_sca
	);

	m_zprepassModel.UpdateWorldMatrix(
		m_pos,
		m_rot,
		m_sca
	);

	//�J�����̏���������߂�B
	Vector3 Vec_x = Vector3::AxisX;
	Vector3 TarPos = Camera::GetLightCamera()->GetTarget() - Camera::GetLightCamera()->GetPosition();
	TarPos.Normalize();
	Vector3 CameraUp;

	CameraUp.Cross(TarPos, Vec_x);
	CameraUp.Normalize();
	Camera::GetLightCamera()->SetUp(CameraUp);
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
	case RenderContext::Render_Mode::RenderMode_ZPrepass:
		m_zprepassModel.Draw(rc);
		break;
	}
}
