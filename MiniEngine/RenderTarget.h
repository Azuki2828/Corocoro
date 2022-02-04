#pragma once

#include "Texture.h"
#include "../GameTemplate/Game/ConstValue.h"

class GraphicsEngine;

/**
 * @brief �����_�����O�^�[�Q�b�g�̃��X�g
*/
enum RenderTargetList {
	enAlbedoAndShadowReceiverFlgMap,
	enNormalAndDepthMap,
	enWorldPosAndLigIDMap,

	enRenderTargetNum
};


/// �����_�����O�^�[�Q�b�g�B

class RenderTarget {
public:
	
	/**
	 * @brief �����_�����O�^�[�Q�b�g�̍쐬�B
	 * @param w �����_�����O�^�[�Q�b�g�̕�
	 * @param h �����_�����O�^�[�Q�b�g�̍���
	 * @param mipLevel �~�b�v�}�b�v���x���B0���w�肵���ꍇ�̓~�b�v�}�b�v���T�|�[�g����Ă���GPU�ł�1*1�s�N�Z���܂ł̃~�b�v�}�b�v���쐬�����B
	 * @param arraySize �e�N�X�`���z��̃T�C�Y
	 * @param colorFormat �J���[�o�b�t�@�̃t�H�[�}�b�g�B
	 * @param depthStencilFormat �[�x�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
	 * @param clearColor �����J���[
	 * @return true���Ԃ��Ă�����쐬����
	*/
	bool Create(
		int w,
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT colorFormat,
		DXGI_FORMAT depthStencilFormat,
		float clearColor[4] = nullptr
	);

	static void CreateMainRenderTarget() {

		m_mainRenderTarget = new RenderTarget;

		RenderTarget::GetMainRenderTarget()->Create(
			RENDER_TARGET_W1280H720.x,
			RENDER_TARGET_W1280H720.y,
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	static RenderTarget* GetMainRenderTarget() {

		return m_mainRenderTarget;
	}

	static RenderTarget* GetRenderTarget(RenderTargetList renderTarget) {

		return m_GBuffer[renderTarget];
	}

	static void CreateAlbedoRenderTarget() {

		m_GBuffer[enAlbedoAndShadowReceiverFlgMap] = new RenderTarget;

		m_GBuffer[enAlbedoAndShadowReceiverFlgMap]->Create(
			RENDER_TARGET_W1280H720.x,
			RENDER_TARGET_W1280H720.y,
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	static void CreateNormalAndDepthRenderTarget() {

		m_GBuffer[enNormalAndDepthMap] = new RenderTarget;

		m_GBuffer[enNormalAndDepthMap]->Create(
			RENDER_TARGET_W1280H720.x,
			RENDER_TARGET_W1280H720.y,
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			DXGI_FORMAT_R16G16B16A16_SNORM,
			DXGI_FORMAT_UNKNOWN
		);
	}

	static void CreateWorldPosAndLigIDRenderTarget() {

		m_GBuffer[enWorldPosAndLigIDMap] = new RenderTarget;

		m_GBuffer[enWorldPosAndLigIDMap]->Create(
			RENDER_TARGET_W1280H720.x,
			RENDER_TARGET_W1280H720.y,
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			DXGI_FORMAT_R32G32B32A32_FLOAT, // ���[���h���W���L�^����̂ŁA32�r�b�g���������_�o�b�t�@�𗘗p����
			DXGI_FORMAT_UNKNOWN
		);
	}

	static void CreateShadowMap() {
		m_shadowMap = new RenderTarget;

		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_shadowMap->Create(
			1024,
			1024,
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}
	static RenderTarget* GetShadowMap() {

		return m_shadowMap;
	}

	static void CreateZPrepassRenderTarget() {

		m_zprepassRenderTarget = new RenderTarget;
		m_zprepassRenderTarget->Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	static RenderTarget* GetZPrepassRenderTarget() {

		return m_zprepassRenderTarget;
	}

	static void CreateLuminanceRenderTarget() {
		m_luminanceRenderTarget = new RenderTarget;

		m_luminanceRenderTarget->Create(
			RENDER_TARGET_W1280H720.x,       // �𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ���
			RENDER_TARGET_W1280H720.y,        // �𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ���
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			// �y���ځz�J���[�o�b�t�@�[�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	static RenderTarget* GetLuminanceRenderTarget() {

		return m_luminanceRenderTarget;
	}

	static void CreateSnapShotRenderTarget() {
		
		m_snapShotRenderTarget = new RenderTarget;
		m_snapShotRenderTarget->Create(
			RENDER_TARGET_W1280H720.x,
			RENDER_TARGET_W1280H720.y,
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			// �y���ځz�J���[�o�b�t�@�[�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	static RenderTarget* GetSnapShotRenderTarget() {

		return m_snapShotRenderTarget;
	}

	static void CreateFinalRenderTarget() {

		m_finalRenderTarget = new RenderTarget;

		m_finalRenderTarget->Create(
			RENDER_TARGET_W1280H720.x,
			RENDER_TARGET_W1280H720.y,
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			// �y���ځz�J���[�o�b�t�@�[�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	static RenderTarget* GetFinalRenderTarget() {

		return m_finalRenderTarget;
	}
	
	/**
	 * @brief CPU���̃����_�����O�^�[�Q�b�g�̃f�B�X�N���v�^�n���h�����擾�B
	 * @return �����_�����O�^�[�Q�b�g�̃f�B�X�N���v�^�n���h��
	*/
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCpuDescriptorHandle() const
	{
		return m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	}

	/**
	 * @brief CPU���̃f�v�X�X�e���V���o�b�t�@�̃f�B�X�N���v�^�n���h�����擾�B
	 * @return �f�v�X�X�e���V���o�b�t�@�̃f�B�X�N���v�^�n���h��
	*/
	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCpuDescriptorHandle() const
	{
		return m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
	}

	/**
	 * @brief �����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`�����擾�B
	 * @return �����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`��
	*/
	Texture& GetRenderTargetTexture()
	{
		return m_renderTargetTexture;
	}

	/**
	 * @brief �f�v�X�X�e���V���o�b�t�@�����݂��Ă��邩����
	 * @return �f�v�X�X�e���V���o�b�t�@�����݂��Ă���?
	*/
	bool IsExsitDepthStencilBuffer() const
	{
		return m_depthStencilTexture;
	}

	/**
	 * @brief �����_�����O�^�[�Q�b�g�̕����擾�B
	 * @return �����_�����O�^�[�Q�b�g�̕�
	*/
	int GetWidth() const
	{
		return m_width;
	}

	/**
	 * @brief �����_�����O�^�[�Q�b�g�̍������擾�B
	 * @return �����_�����O�^�[�Q�b�g�̍���
	*/
	int GetHeight() const
	{
		return m_height;
	}

	/**
	 * @brief �J���[�o�b�t�@�̃t�H�[�}�b�g���擾�B
	 * @return �J���[�o�b�t�@�̃t�H�[�}�b�g
	*/
	DXGI_FORMAT GetColorBufferFormat() const
	{
		return m_renderTargetTexture.GetFormat();
	}
	const float* GetRTVClearColor() const
	{
		return m_rtvClearColor;
	}
	float GetDSVClearValue() const
	{
		return m_dsvClearValue;
	}
private:

	/**
	 * @brief �f�B�X�N���v�^�q�[�v���쐬�B
	 * @param ge �O���t�B�b�N�G���W��
	 * @param d3dDevice D3D�f�o�C�X
	 * @return �쐬�ɐ��������H
	*/
	bool CreateDescriptorHeap(GraphicsEngine& ge, ID3D12Device5*& d3dDevice);

	/**
	 * @brief �����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬�B
	 * @param ge �O���t�B�b�N�G���W��
	 * @param d3dDevice D3D�f�o�C�X
	 * @param w �e�N�X�`���̕�
	 * @param h �e�N�X�`���̍���
	 * @param mipLevel �~�b�v�}�b�v���x��
	 * @param arraySize �e�N�X�`���z��̃T�C�Y
	 * @param format �e�N�X�`���̃t�H�[�}�b�g
	 * @param clearColor �����J���[
	 * @return �쐬�ɐ��������H
	*/
	bool CreateRenderTargetTexture(
		GraphicsEngine& ge,
		ID3D12Device5*& d3dDevice,
		int w, 
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT format,
		float clearColor[4]
	);

	/**
	 * @brief �[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`�����쐬�B
	 * @param ge �O���t�B�b�N�G���W��
	 * @param d3dDevice D3D�f�o�C�X
	 * @param w �e�N�X�`���̕�
	 * @param h �e�N�X�`���̍���
	 * @param format �e�N�X�`���̃t�H�[�}�b�g
	 * @return �쐬�ɐ��������H
	*/
	bool CreateDepthStencilTexture(
		GraphicsEngine& ge,
		ID3D12Device5*& d3dDevice,
		int w,
		int h,
		DXGI_FORMAT format);

	/**
	 * @brief �f�B�X�N���v�^�̍쐬�B
	 * @param d3dDevice D3D�f�o�C�X
	*/
	void CreateDescriptor(ID3D12Device5*& d3dDevice);
private:
	static RenderTarget* m_shadowMap;
	static RenderTarget* m_mainRenderTarget;
	static RenderTarget* m_zprepassRenderTarget;
	static RenderTarget* m_snapShotRenderTarget;
	static RenderTarget* m_luminanceRenderTarget;
	static RenderTarget* m_finalRenderTarget;
	static RenderTarget* m_GBuffer[enRenderTargetNum];

	Texture m_renderTargetTexture;				//�����_�����O�^�[�Q�b�g�̃e�N�X�`���B
	ID3D12Resource* m_renderTargetTextureDx12;	//�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
	ID3D12Resource* m_depthStencilTexture;		//�[�x�X�e���V���o�b�t�@�ƂȂ�e�N�X�`���B
	ID3D12DescriptorHeap*		m_rtvHeap;		//RTV�p�̃f�B�X�N���v�^�q�[�v�B
	ID3D12DescriptorHeap*		m_dsvHeap;		//�[�x�X�e���V���o�b�t�@�r���[�̃f�B�X�N���v�^�q�[�v�B
	UINT m_rtvDescriptorSize = 0;				//�t���[���o�b�t�@�̃f�B�X�N���v�^�̃T�C�Y�B
	UINT m_dsvDescriptorSize = 0;				//�[�x�X�e���V���o�b�t�@�̃f�B�X�N���v�^�̃T�C�Y�B
	int m_width = 0;							//�����_�����O�^�[�Q�b�g�̕��B
	int m_height = 0;							//�����_�����O�^�[�Q�b�g�̍����B
	float m_rtvClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	//�����_�����O�^�[�Q�b�g�r���[�̃N���A�J���[�B
	float m_dsvClearValue = 1.0f;							//DSV�̃N���A�J���[�B
};


