/*!
 * @brief	影が落とされるモデル用のシェーダー。
 */
static const int NUM_DIRECTIONAL_LIGHT = 8;
static const float PI = 3.1415926f;         // π


struct DirectionalLight
{
	float3 direction;
	float4 color;
};

//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

cbuffer ModelCb : register(b1) {
	int ligID;
}

//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 			: POSITION;		//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線。
	float3 tangent		: TANGENT;
	float3 biNormal		: BINORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線。
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD2;
	//ライトビュースクリーン空間での座標を追加。
	float4 posInLVP		: TEXCOORD1;	//ライトビュースクリーン空間でのピクセルの座標
	float4 posInProj    : TEXCOORD3;
};

struct SPSOut {
	float4 albedo : SV_TARGET0;
	float4 normalAndDepth : SV_TARGET1;
	float4 worldPosAndLigID : SV_TARGET2;
};

///////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////

Texture2D<float4> g_albedo : register(t0);		//アルベドマップ。
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_shadowMap : register(t10);	//シャドウマップ。
Texture2D<float4> g_depthTexture : register(t11);	//深度テクスチャ。

sampler g_sampler : register(s0);				// サンプラステート。

/// <summary>
/// 影が落とされる3Dモデル用の頂点シェーダー。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	//通常の座標変換。
	SPSIn psIn;
	psIn.worldPos = mul(mWorld, vsIn.pos);
	psIn.pos = mul(mView, float4( psIn.worldPos, 1.0f ));
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;
	psIn.normal = mul(mWorld, vsIn.normal);
	//psIn.normal = float3(vsIn.normal);
	psIn.tangent = mul(mWorld, vsIn.tangent);
	psIn.biNormal = mul(mWorld, vsIn.biNormal);

	//ライトビュースクリーン空間の座標を計算する。
	//psIn.posInLVP = mul( mLVP, float4( psIn.worldPos,1.0f ) );

	//psIn.posInProj = psIn.pos;
	

	return psIn;
}

SPSOut PSMain(SPSIn psIn)
{
	SPSOut psOut;
	
	psOut.albedo = g_albedo.Sample(g_sampler, psIn.uv);

	float3 localNormal = psIn.normal;
	
	psOut.normalAndDepth.xyz = localNormal;
	psOut.normalAndDepth.w = g_depthTexture.Sample(g_sampler, psIn.uv).r;
	psOut.worldPosAndLigID.xyz = psIn.worldPos;
	psOut.worldPosAndLigID.w = ligID;

	return psOut;
}