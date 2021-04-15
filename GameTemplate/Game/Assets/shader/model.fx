/*!
 * @brief	シンプルなモデルシェーダー。
 */

static const int NUM_DIRECTIONAL_LIGHT = 8;
static const float PI = 3.1415926f;         // π

struct DirectionalLight
{
	float3 direction;
	float4 color;
	//float4x4 mLVP;
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

cbuffer DirectionLightCb : register(b1) {
	DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];
	float3 eyePos;
}

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
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
	float3 normal		: NORMAL;
	float3 tangent : TANGENT;
	float3 biNormal : BINORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos : TEXCOORD1;    // ワールド空間でのピクセルの座標
	//ライトビュースクリーン空間での座標を追加。
	//float4 posInLVP		: TEXCOORD1;	//ライトビュースクリーン空間でのピクセルの座標
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);

StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
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
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	psIn.normal = mul(m, vsIn.normal);

	psIn.tangent = mul(m, vsIn.tangent);
	psIn.biNormal = mul(m, vsIn.biNormal);

	psIn.uv = vsIn.uv;

	//ライトビュースクリーン空間の座標を計算する。
	//psIn.posInLVP = mul(mLVP, worldPos);

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
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}

///////////////////////////////////////////////////
// 関数
///////////////////////////////////////////////////
float3 GetNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
	float3 binSpaceNormal = g_normalMap.SampleLevel(g_sampler, uv, 0.0f).xyz;
	binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;

	float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;

	return newNormal;
}

// ベックマン分布を計算する
float Beckmann(float m, float t)
{
	float t2 = t * t;
	float t4 = t * t * t * t;
	float m2 = m * m;
	float D = 1.0f / (4.0f * m2 * t4);
	D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
	return D;
}

// フレネルを計算。Schlick近似を使用
float SpcFresnel(float f0, float u)
{
	// from Schlick
	return f0 + (1 - f0) * pow(1 - u, 5);
}

/// <summary>
/// クックトランスモデルの鏡面反射を計算
/// </summary>
/// <param name="L">光源に向かうベクトル</param>
/// <param name="V">視点に向かうベクトル</param>
/// <param name="N">法線ベクトル</param>
/// <param name="metaric">金属度</param>
float CookTorranceSpecular(float3 L, float3 V, float3 N, float metaric)
{
	float microfacet = 0.76f;

	// 金属度を垂直入射の時のフレネル反射率として扱う
	// 金属度が高いほどフレネル反射は大きくなる
	float f0 = metaric;

	// ライトに向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
	float3 H = normalize(L + V);

	// 各種ベクトルがどれくらい似ているかを内積を利用して求める
	float NdotH = saturate(dot(N, H));
	float VdotH = saturate(dot(V, H));
	float NdotL = saturate(dot(N, L));
	float NdotV = saturate(dot(N, V));

	// D項をベックマン分布を用いて計算する
	float D = Beckmann(microfacet, NdotH);

	// F項をSchlick近似を用いて計算する
	float F = SpcFresnel(f0, VdotH);

	// G項を求める
	float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));

	// m項を求める
	float m = PI * NdotV * NdotH;

	// ここまで求めた、値を利用して、クックトランスモデルの鏡面反射を求める
	return max(F * D * G / m, 0.0);
}

/// <summary>
/// フレネル反射を考慮した拡散反射を計算
/// </summary>
float CalcDiffuseFromFresnel(float3 N, float3 L, float3 V)
{
	float3 H = normalize(L + V);

	float roughness = 0.5f;
	float energyBias = lerp(0.0f, 0.5f, roughness);

	float dotLH = saturate(dot(L, H));

	float Fd90 = energyBias + 2.0 * dotLH * dotLH * roughness;

	float dotNL = saturate(dot(N, L));

	float FL = Fd90 + (dotNL - Fd90);

	float dotNV = saturate(dot(N, V));

	float FV = Fd90 + (dotNV - Fd90);

	return (FL * FV) / PI;
}


/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{

	// 法線を計算
	float3 normal = GetNormal(psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv);

	// step-2 アルベドカラー、スペキュラカラー、金属度をサンプリングする
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	float3 specColor = g_specularMap.SampleLevel(g_sampler, psIn.uv, 0).rgb;
	float metaric = g_specularMap.Sample(g_sampler, psIn.uv).a;

	// 視線に向かって伸びるベクトルを計算する
	float3 toEye = normalize(eyePos - psIn.worldPos);

	float3 lig = 0;
	for (int ligNo = 0; ligNo < NUM_DIRECTIONAL_LIGHT; ligNo++)
	{
		// step-3 ディズニーベースの拡散反射を実装する
		float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -directionalLight[ligNo].direction, toEye);

		float NdotL = saturate(dot(normal, -directionalLight[ligNo].direction));

		float3 lambertDiffuse = directionalLight[ligNo].color * NdotL / PI;
		//return float4(toEye, 1.0f);
		float3 diffuse = albedoColor * diffuseFromFresnel * lambertDiffuse;
		//return float4(diffuse, 1.0f);

		// step-5 クックトランスモデルを利用した鏡面反射率を計算する
		float3 spec = CookTorranceSpecular(-directionalLight[ligNo].direction,
			toEye, normal, metaric) * directionalLight[ligNo].color;

		float specTerm = length(specColor.xyz);

		spec *= lerp(float3(specTerm, specTerm, specTerm), specColor, metaric);

		// step-6 鏡面反射率を使って、拡散反射光と鏡面反射光を合成する

		lig += diffuse * (1.0f - specTerm) + spec;
	}

	// step-7 環境光による底上げ

	float4 finalColor = 1.0f;
	finalColor.xyz = lig;
	return finalColor;

	////拡散反射光の影響
	//float t = dot(psIn.normal,ligDirection);

	//t *= -1.0f;

	//if (t < 0.0f) {
	//	t = 0.0f;
	//}

	//float3 diffuseLig = ligColor * t;
	//diffuseLig /= 3.1415926;


	////鏡面反射光の影響
	////float3 refvec = reflect(ligDirection, psIn.normal);

	//float3 toEye = eyePos - psIn.pos;
	//toEye = normalize( toEye );

	////t = dot(refvec, toEye);

	////if (t < 0.0f) {
	////	t = 0.0f;
	////}

	////t = pow(t, 5.0f);

	////float3 specularLig = ligColor * t;

	////float3 lig = diffuseLig;// + specularLig;

	////環境光の影響
	////lig.x += 0.2f;
	////lig.y += 0.2f;
	////lig.z += 0.2f;

	////クックトランス
	////float3 spec = CookTrranceSpecular(-ligDirection, toEye, psIn.normal, metaric) * ligColor;

	////float specTerm = length(specColor.xyz);
	////spec *= lerp(float3(specTerm, specTerm, specTerm), specColor, metaric);



	//float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	////albedoColor.xyz *= lig;
	//



	////float3 specColor = g_specularMap.SampleLevel(g_sampler, psIn.uv, 0).rgb;

	////float3 metaric = g_specularMap.Sample(g_sampler, psIn.uv).a;


	////フレネル反射
	//float3 H = normalize(ligDirection + toEye);
	//float dotLH = saturate(dot(ligDirection, H));
	//float dotNL = saturate(dot(psIn.normal, ligDirection));

	//float3 lig = diffuseLig + (dotLH * dotNL);// / 3.1415926;
	////float3 lig = (dotLH * dotNL) / 3.1415926; //* (1.0 - specTerm) + spec;
	////return albedoColor;
	////albedoColor.xyz *= lig;

	//return albedoColor;
}
