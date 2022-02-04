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
	int shadowReceiverFlg;
}
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn {
	int4  Indices  	: BLENDINDICES0;
	float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn {
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
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
	float4 albedoAndShadowReceiver : SV_TARGET0;
	float4 normalAndDepth : SV_TARGET1;
	float4 worldPosAndLigID : SV_TARGET2;
};

///////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////

Texture2D<float4> g_albedo : register(t0);		//アルベドマップ。
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
Texture2D<float4> g_shadowMap : register(t10);	//シャドウマップ。
Texture2D<float4> g_depthTexture : register(t11);	//深度テクスチャ。

sampler g_sampler : register(s0);				// サンプラステート。

float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;
	float w = 0.0f;
	[unroll]
	for (int i = 0; i < 3; i++)
	{
		skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
		w += skinVert.Weights[i];
	}

	skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

	return skinning;
}

/// <summary>
/// 影が落とされる3Dモデル用の頂点シェーダー。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	//通常の座標変換。
	SPSIn psIn;
	float4x4 m;
	if (hasSkin) {
		m = CalcSkinMatrix(vsIn.skinVert);
	}
	else {
		m = mWorld;
	}
	psIn.worldPos = mul(m, vsIn.pos);
	psIn.pos = mul(mView, float4( psIn.worldPos, 1.0f ));
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;
	psIn.normal = mul(m, vsIn.normal);
	//psIn.normal = float3(vsIn.normal);
	psIn.tangent = mul(m, vsIn.tangent);
	psIn.biNormal = mul(m, vsIn.biNormal);

	//ライトビュースクリーン空間の座標を計算する。
	//psIn.posInLVP = mul( mLVP, float4( psIn.worldPos,1.0f ) );

	//psIn.posInProj = psIn.pos;
	

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, true);
}

SPSOut PSMain(SPSIn psIn)
{
	SPSOut psOut;
	
	psOut.albedoAndShadowReceiver.xyz = g_albedo.Sample(g_sampler, psIn.uv).xyz;
	psOut.albedoAndShadowReceiver.w = shadowReceiverFlg;

	float3 localNormal = psIn.normal;
	
	psOut.normalAndDepth.xyz = localNormal;
	psOut.normalAndDepth.w = g_depthTexture.Sample(g_sampler, psIn.uv).r;
	psOut.worldPosAndLigID.xyz = psIn.worldPos;
	psOut.worldPosAndLigID.w = ligID;

	return psOut;
}