#pragma once

#include "Texture.h"
#include "../GameTemplate/Game/ConstValue.h"

class GraphicsEngine;

/**
 * @brief レンダリングターゲットのリスト
*/
enum RenderTargetList {
	enAlbedoAndShadowReceiverFlgMap,
	enNormalAndDepthMap,
	enWorldPosAndLigIDMap,

	enRenderTargetNum
};


/// レンダリングターゲット。

class RenderTarget {
public:
	
	/**
	 * @brief レンダリングターゲットの作成。
	 * @param w レンダリングターゲットの幅
	 * @param h レンダリングターゲットの高さ
	 * @param mipLevel ミップマップレベル。0を指定した場合はミップマップがサポートされているGPUでは1*1ピクセルまでのミップマップが作成される。
	 * @param arraySize テクスチャ配列のサイズ
	 * @param colorFormat カラーバッファのフォーマット。
	 * @param depthStencilFormat 深度ステンシルバッファのフォーマット。
	 * @param clearColor 初期カラー
	 * @return trueが返ってきたら作成成功
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
			DXGI_FORMAT_R32G32B32A32_FLOAT, // ワールド座標を記録するので、32ビット浮動小数点バッファを利用する
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
			RENDER_TARGET_W1280H720.x,       // 解像度はメインレンダリングターゲットと同じ
			RENDER_TARGET_W1280H720.y,        // 解像度はメインレンダリングターゲットと同じ
			MIP_LEVEL1,
			RENDER_ARRAY_SIZE1,
			// 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
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
			// 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
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
			// 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	static RenderTarget* GetFinalRenderTarget() {

		return m_finalRenderTarget;
	}
	
	/**
	 * @brief CPU側のレンダリングターゲットのディスクリプタハンドルを取得。
	 * @return レンダリングターゲットのディスクリプタハンドル
	*/
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCpuDescriptorHandle() const
	{
		return m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	}

	/**
	 * @brief CPU側のデプスステンシルバッファのディスクリプタハンドルを取得。
	 * @return デプスステンシルバッファのディスクリプタハンドル
	*/
	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCpuDescriptorHandle() const
	{
		return m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
	}

	/**
	 * @brief レンダリングターゲットとなるテクスチャを取得。
	 * @return レンダリングターゲットとなるテクスチャ
	*/
	Texture& GetRenderTargetTexture()
	{
		return m_renderTargetTexture;
	}

	/**
	 * @brief デプスステンシルバッファが存在しているか判定
	 * @return デプスステンシルバッファが存在している?
	*/
	bool IsExsitDepthStencilBuffer() const
	{
		return m_depthStencilTexture;
	}

	/**
	 * @brief レンダリングターゲットの幅を取得。
	 * @return レンダリングターゲットの幅
	*/
	int GetWidth() const
	{
		return m_width;
	}

	/**
	 * @brief レンダリングターゲットの高さを取得。
	 * @return レンダリングターゲットの高さ
	*/
	int GetHeight() const
	{
		return m_height;
	}

	/**
	 * @brief カラーバッファのフォーマットを取得。
	 * @return カラーバッファのフォーマット
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
	 * @brief ディスクリプタヒープを作成。
	 * @param ge グラフィックエンジン
	 * @param d3dDevice D3Dデバイス
	 * @return 作成に成功した？
	*/
	bool CreateDescriptorHeap(GraphicsEngine& ge, ID3D12Device5*& d3dDevice);

	/**
	 * @brief レンダリングターゲットとなるテクスチャを作成。
	 * @param ge グラフィックエンジン
	 * @param d3dDevice D3Dデバイス
	 * @param w テクスチャの幅
	 * @param h テクスチャの高さ
	 * @param mipLevel ミップマップレベル
	 * @param arraySize テクスチャ配列のサイズ
	 * @param format テクスチャのフォーマット
	 * @param clearColor 初期カラー
	 * @return 作成に成功した？
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
	 * @brief 深度ステンシルバッファとなるテクスチャを作成。
	 * @param ge グラフィックエンジン
	 * @param d3dDevice D3Dデバイス
	 * @param w テクスチャの幅
	 * @param h テクスチャの高さ
	 * @param format テクスチャのフォーマット
	 * @return 作成に成功した？
	*/
	bool CreateDepthStencilTexture(
		GraphicsEngine& ge,
		ID3D12Device5*& d3dDevice,
		int w,
		int h,
		DXGI_FORMAT format);

	/**
	 * @brief ディスクリプタの作成。
	 * @param d3dDevice D3Dデバイス
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

	Texture m_renderTargetTexture;				//レンダリングターゲットのテクスチャ。
	ID3D12Resource* m_renderTargetTextureDx12;	//レンダリングターゲットとなるテクスチャ。
	ID3D12Resource* m_depthStencilTexture;		//深度ステンシルバッファとなるテクスチャ。
	ID3D12DescriptorHeap*		m_rtvHeap;		//RTV用のディスクリプタヒープ。
	ID3D12DescriptorHeap*		m_dsvHeap;		//深度ステンシルバッファビューのディスクリプタヒープ。
	UINT m_rtvDescriptorSize = 0;				//フレームバッファのディスクリプタのサイズ。
	UINT m_dsvDescriptorSize = 0;				//深度ステンシルバッファのディスクリプタのサイズ。
	int m_width = 0;							//レンダリングターゲットの幅。
	int m_height = 0;							//レンダリングターゲットの高さ。
	float m_rtvClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	//レンダリングターゲットビューのクリアカラー。
	float m_dsvClearValue = 1.0f;							//DSVのクリアカラー。
};


