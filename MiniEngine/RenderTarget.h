#pragma once

#include "Texture.h"
#include "../GameTemplate/Game/ConstValue.h"

class GraphicsEngine;

enum RenderTargetList {
	enAlbedoMap,
	enNormalAndDepthMap,
	enWorldPosAndLigIDMap,

	enRenderTargetNum
};

/// <summary>
/// レンダリングターゲット。
/// </summary>
class RenderTarget {
public:
	/// <summary>
	/// レンダリングターゲットの作成。
	/// </summary>
	/// <param name="w">レンダリングターゲットの幅</param>
	/// <param name="h">レンダリングターゲットの高さ</param>
	/// <param name="mipLevel">ミップマップレベル。0を指定した場合はミップマップがサポートされているGPUでは1*1ピクセルまでのミップマップが作成される。</param>
	/// <param name="arraySize">テクスチャ配列のサイズ</param>
	/// <param name="colorFormat">カラーバッファのフォーマット。</param>
	/// <param name="depthStencilFormat">深度ステンシルバッファのフォーマット。</param>
	/// <returns>trueが返ってきたら作成成功</returns>
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
	}

	static RenderTarget* GetMainRenderTarget() {

		return m_mainRenderTarget;
	}

	static RenderTarget* GetRenderTarget(RenderTargetList renderTarget) {

		return m_GBuffer[renderTarget];
	}

	static void CreateAlbedoRenderTarget() {

		m_GBuffer[enAlbedoMap] = new RenderTarget;

		m_GBuffer[enAlbedoMap]->Create(
			RENDER_TARGET_W1280H720.x,
			RENDER_TARGET_W1280H720.y,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	static void CreateNormalAndDepthRenderTarget() {

		m_GBuffer[enNormalAndDepthMap] = new RenderTarget;

		m_GBuffer[enNormalAndDepthMap]->Create(
			RENDER_TARGET_W1280H720.x,
			RENDER_TARGET_W1280H720.y,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);
	}

	static void CreateWorldPosAndLigIDRenderTarget() {

		m_GBuffer[enWorldPosAndLigIDMap] = new RenderTarget;

		m_GBuffer[enWorldPosAndLigIDMap]->Create(
			RENDER_TARGET_W1280H720.x,
			RENDER_TARGET_W1280H720.y,
			1,
			1,
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
			1,
			1,
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
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	static RenderTarget* GetZPrepassRenderTarget() {

		return m_zprepassRenderTarget;
	}
	/// <summary>
	/// CPU側のレンダリングターゲットのディスクリプタハンドルを取得。
	/// </summary>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCpuDescriptorHandle() const
	{
		return m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	}
	/// <summary>
	/// CPU側のデプスステンシルバッファのディスクリプタハンドルを取得。
	/// </summary>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCpuDescriptorHandle() const
	{
		return m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
	}
	/// <summary>
	/// レンダリングターゲットとなるテクスチャを取得。
	/// </summary>
	/// <returns></returns>
	Texture& GetRenderTargetTexture()
	{
		return m_renderTargetTexture;
	}
	/// <summary>
	/// デプスステンシルバッファが存在しているか判定
	/// </summary>
	/// <returns></returns>
	bool IsExsitDepthStencilBuffer() const
	{
		return m_depthStencilTexture;
	}
	/// <summary>
	/// レンダリングターゲットの幅を取得。
	/// </summary>
	/// <returns></returns>
	int GetWidth() const
	{
		return m_width;
	}
	/// <summary>
	/// レンダリングターゲットの高さを取得。
	/// </summary>
	/// <returns></returns>
	int GetHeight() const
	{
		return m_height;
	}
	/// <summary>
	/// カラーバッファのフォーマットを取得。
	/// </summary>
	/// <returns></returns>
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
	/// <summary>
	/// ディスクリプタヒープを作成。
	/// </summary>
	/// <param name="ge">グラフィックエンジン</param>
	/// <param name="d3dDevice">D3Dデバイス</param>
	/// <returns></returns>
	bool CreateDescriptorHeap(GraphicsEngine& ge, ID3D12Device5*& d3dDevice);
	/// <summary>
	/// レンダリングターゲットとなるテクスチャを作成。
	/// </summary>
	/// <param name="ge">グラフィックエンジン</param>
	/// <param name="d3dDevice">D3Dデバイス</param>
	/// <param name="w">テクスチャの幅</param>
	/// <param name="h">テクスチャの高さ</param>
	/// <param name="mipLevel">ミップマップレベル</param>
	/// <param name="arraySize">テクスチャ配列のサイズ</param>
	/// <param name="format">テクスチャのフォーマット</param>
	/// <returns>trueが返ってきたら成功。</returns>
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
	/// <summary>
	/// 深度ステンシルバッファとなるテクスチャを作成。
	/// </summary>
	/// <param name="ge">グラフィックエンジン</param>
	/// <param name="d3dDevice">D3Dデバイス</param>
	/// <param name="w">テクスチャの幅</param>
	/// <param name="h">テクスチャの高さ</param>
	/// <param name="format">テクスチャのフォーマット</param>
	/// <returns>trueが返ってきたら成功</returns>
	bool CreateDepthStencilTexture(
		GraphicsEngine& ge,
		ID3D12Device5*& d3dDevice,
		int w,
		int h,
		DXGI_FORMAT format);
	/// <summary>
	/// ディスクリプタの作成。
	/// </summary>
	/// <param name="d3dDevice">D3Dデバイス</param>
	/// <returns>trueが返ってｋチアら成功。</returns>
	void CreateDescriptor(ID3D12Device5*& d3dDevice);
private:
	static RenderTarget* m_shadowMap;
	static RenderTarget* m_mainRenderTarget;
	static RenderTarget* m_zprepassRenderTarget;
	static RenderTarget* m_albedoRenderTarget;
	static RenderTarget* m_normalRenderTarget;
	static RenderTarget* m_depthRenderTarget;
	
	static RenderTarget* m_GBuffer[enRenderTargetNum];
	Texture m_renderTargetTexture;
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


