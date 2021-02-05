/*!
 * @brief	シンプルなモデルシェーダー。
 */


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
	float3 ligDirection;
	float3 ligColor;
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
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
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
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	psIn.normal = mul(m, vsIn.normal);

	psIn.uv = vsIn.uv;

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
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{

	//拡散反射光の影響
	float t = dot(psIn.normal,ligDirection);

	t *= -1.0f;

	if (t < 0.0f) {
		t = 0.0f;
	}

	float3 diffuseLig = ligColor * t;
	diffuseLig /= 3.1415926;


	//鏡面反射光の影響
	//float3 refvec = reflect(ligDirection, psIn.normal);

	float3 toEye = eyePos - psIn.pos;
	toEye = normalize( toEye );

	//t = dot(refvec, toEye);

	//if (t < 0.0f) {
	//	t = 0.0f;
	//}

	//t = pow(t, 5.0f);

	//float3 specularLig = ligColor * t;

	//float3 lig = diffuseLig;// + specularLig;

	//環境光の影響
	//lig.x += 0.2f;
	//lig.y += 0.2f;
	//lig.z += 0.2f;

	//クックトランス
	//float3 spec = CookTrranceSpecular(-ligDirection, toEye, psIn.normal, metaric) * ligColor;

	//float specTerm = length(specColor.xyz);
	//spec *= lerp(float3(specTerm, specTerm, specTerm), specColor, metaric);



	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//albedoColor.xyz *= lig;
	



	//float3 specColor = g_specularMap.SampleLevel(g_sampler, psIn.uv, 0).rgb;

	//float3 metaric = g_specularMap.Sample(g_sampler, psIn.uv).a;


	//フレネル反射
	float3 H = normalize(ligDirection + toEye);
	float dotLH = saturate(dot(ligDirection, H));
	float dotNL = saturate(dot(psIn.normal, ligDirection));

	float3 lig = diffuseLig + (dotLH * dotNL);// / 3.1415926;
	//float3 lig = (dotLH * dotNL) / 3.1415926; //* (1.0 - specTerm) + spec;
	//return albedoColor;
	albedoColor.xyz *= lig;

	return albedoColor;
}
