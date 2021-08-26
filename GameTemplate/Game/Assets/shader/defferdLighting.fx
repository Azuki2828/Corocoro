/*!
 * @brief	�X�v���C�g�p�̃V�F�[�_�[�B
 */
static const int MAX_DIRECTION_LIGHT = 8;
static const int MAX_MODEL_OPTION = 100;
static const float PI = 3.1415926f;         // π

struct DirectionalLight
{
	float3 direction;
	float4 color;
	//float4x4 mLVP;
};

struct ModelOption {
	DirectionalLight directionLigData[MAX_DIRECTION_LIGHT];	//ディレクションライトのデータ
	float3 ambient;
	float metaric;
	float smooth;
	int edge;
	float powValue;
	unsigned int LigID;
	float uvNoiseMul;
	float uvNoiseOffset;
};

cbuffer DefferdLightingCb : register(b1) {
	DirectionalLight directionalLight[MAX_DIRECTION_LIGHT];
	ModelOption modelOption[MAX_MODEL_OPTION];
	float3 eyePos;
	float4x4 mLVP;
};

cbuffer cb : register(b0){
	float4x4 mvp;		//���[���h�r���[�v���W�F�N�V�����s��B
	float4 mulColor;	//��Z�J���[�B
};
struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

//Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);
Texture2D<float4> normalAndDepthTexture : register(t1);
Texture2D<float4> worldPosAndLigIDTexture : register(t2);
Texture2D<float4> g_shadowMap : register(t10);	//シャドウマップ。
Texture2D<float4> g_depthTexture : register(t11);	//深度テクスチャ。


sampler g_sampler : register(s0);

///////
//関数
//////
float3 GetNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
	float3 binSpaceNormal = normalAndDepthTexture.SampleLevel(g_sampler, uv, 0.0f).xyz;
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
float CookTorranceSpecular(float3 L, float3 V, float3 N, float metaric, float microfacet)
{
	// 金属度を垂直入射の時のフレネル反射率として扱う
	// 金属度が高いほどフレネル反射は大きくなる
	float f0 = 1.0f - microfacet;

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
	if (m == 0.0f)
		//0割り防止
		return 0.0f;

	// ここまで求めた、値を利用して、クックトランスモデルの鏡面反射を求める
	return max(F * D * G / m, 0.0);
}

/// <summary>
/// フレネル反射を考慮した拡散反射を計算
/// </summary>
float CalcDiffuseFromFresnel(float3 N, float3 L, float3 V, float roughness)
{
	// step-1 ディズニーベースのフレネル反射による拡散反射を真面目に実装する。
   // 光源に向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
	float3 H = normalize(L + V);

	float energyBias = lerp(0.0f, 0.5f, roughness);
	float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);

	// 光源に向かうベクトルとハーフベクトルがどれだけ似ているかを内積で求める
	float dotLH = saturate(dot(L, H));

	// 光源に向かうベクトルとハーフベクトル、
	// 光が平行に入射したときの拡散反射量を求めている
	float Fd90 = energyBias + 2.0 * dotLH * dotLH * roughness;

	// 法線と光源に向かうベクトルwを利用して拡散反射率を求める
	float dotNL = saturate(dot(N, L));
	float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

	// 法線と視点に向かうベクトルを利用して拡散反射率を求める
	float dotNV = saturate(dot(N, V));
	float FV = (1 + (Fd90 - 1) * pow(1 - dotNV, 5));

	// 法線と光源への方向に依存する拡散反射率と、法線と視点ベクトルに依存する拡散反射率を
	// 乗算して最終的な拡散反射率を求めている。PIで除算しているのは正規化を行うため
	return (FL * FV * energyFactor);
}
// ハッシュ関数
float hash(float n)
{
	return frac(sin(n) * 43758.5453);
}

// 3次元ベクトルからシンプレックスノイズを生成する関数
float SimplexNoise(float3 x)
{
	// The noise function returns a value in the range -1.0f -> 1.0f
	float3 p = floor(x);
	float3 f = frac(x);

	f = f * f * (3.0 - 2.0 * f);
	float n = p.x + p.y * 57.0 + 113.0 * p.z;

	return lerp(lerp(lerp(hash(n + 0.0), hash(n + 1.0), f.x),
		lerp(hash(n + 57.0), hash(n + 58.0), f.x), f.y),
		lerp(lerp(hash(n + 113.0), hash(n + 114.0), f.x),
			lerp(hash(n + 170.0), hash(n + 171.0), f.x), f.y), f.z);
}
PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
//float4 PSMain( PSInput In ) : SV_Target0
//{
//	return colorTexture.Sample(Sampler, In.uv) * mulColor;
//}


float4 PSMain(PSInput In) : SV_Target0
{
	float3 normal = normalAndDepthTexture.Sample(g_sampler, In.uv).xyz;

	normal = (normal * 2.0f) - 1.0f;

	//return float4(normal.xyz, 1.0f);

	float3 worldPos = worldPosAndLigIDTexture.Sample(g_sampler, In.uv).xyz;
	unsigned int ligID = worldPosAndLigIDTexture.Sample(g_sampler, In.uv).w;

	float uOffset = SimplexNoise(float3(In.uv + modelOption[ligID].uvNoiseOffset, 0.0f) * 256.0f) * 0.5f;

	float4 albedoColor = albedoTexture.Sample(g_sampler, In.uv + uOffset * modelOption[ligID].uvNoiseMul);
	float3 specColor = albedoColor;

	float3 toEye = normalize(eyePos - worldPos);

	float3 lig;

	for (int ligNo = 0; ligNo < MAX_DIRECTION_LIGHT; ligNo++) {

		float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -directionalLight[ligNo].direction, toEye, 1.0f - modelOption[ligID].smooth);

		float NdotL = saturate(dot(normal, -directionalLight[ligNo].direction));

		float3 lambertDiffuse = directionalLight[ligNo].color * NdotL / PI;

		float3 diffuse = albedoColor * diffuseFromFresnel * lambertDiffuse;

		float3 spec = CookTorranceSpecular(-directionalLight[ligNo].direction,
			toEye, normal, modelOption[ligID].metaric, 1.0f - modelOption[ligID].smooth) * directionalLight[ligNo].color;

		spec *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, modelOption[ligID].smooth);

		//鏡面反射率を使って、拡散反射光と鏡面反射光を合成する
		//return float4(diffuse, 1.0f);
		lig += diffuse * (1.0f - modelOption[ligID].smooth) + spec * modelOption[ligID].smooth;
	}

	lig += modelOption[ligID].ambient * albedoColor;

	float4 finalColor = albedoColor;
	finalColor.xyz = lig;

	//float4 posInProj = In.pos;
	//if (modelOption[ligID].edge > 0) {
	//	//float2 uv = psIn.posInProj.xy * float2(0.5f, -0.5f) + 0.5f;

	//	float2 uvOffset[8] = {
	//		float2(0.0f,  0.5f / 720.0f),
	//		float2(0.0f, -0.5f / 720.0f),
	//		float2(0.5f / 1280.0f,           0.0f),
	//		float2(-0.5f / 1280.0f,           0.0f),
	//		float2(0.5f / 1280.0f,  0.5f / 720.0f),
	//		float2(-0.5f / 1280.0f,  0.5f / 720.0f),
	//		float2(0.5f / 1280.0f, -0.5f / 720.0f),
	//		float2(-0.5f / 1280.0f, -0.5f / 720.0f)
	//	};

	//	float depth = normalAndDepthTexture.Sample(g_sampler, In.uv).w;

	//	float depth2 = 0.0f;
	//	for (int i = 0; i < 8; i++) {
	//		depth2 += normalAndDepthTexture.Sample(g_sampler, In.uv + uvOffset[i]).w;
	//	}
	//	depth2 /= 8.0f;
	//	if (abs(depth - depth2) > 0.0005f) {
	//		return float4(0.0f, 0.0f, 0.0f, 1.0f);
	//	}

	//	float3 normalDistance1 = g_depthTexture.Sample(g_sampler, In.uv).xyz;
	//	float3 normalDistance2 = 0.0f;
	//	for (int i = 0; i < 8; i++) {
	//		normalDistance2 = g_depthTexture.Sample(g_sampler, In.uv + uvOffset[i]).xyz;


	//		if (modelOption[ligID].edge == 1) {
	//			float t = dot(normalDistance1, normalDistance2);
	//			if (t < 0.5f) {
	//				//法線が結構違う。
	//				t = max(0.0f, t);
	//				t += 0.5f;
	//				finalColor *= pow(t, modelOption[ligID].powValue);
	//				break;
	//			}
	//		}
	//		else if (modelOption[ligID].edge == 2) {

	//			float t = dot(normalDistance1, normalDistance2);
	//			if (t > 0.5f) {
	//				//法線が結構違う。
	//				t = max(0.0f, t);
	//				t -= 0.5f;
	//				t *= 2.0f;
	//				finalColor *= pow(1.0 - t, 0.5f);
	//				break;
	//			}
	//		}
	//	}

	//	//ライトビュースクリーン空間からUV空間に座標変換。
	//	float2 shadowMapUV = In.uv;

	//	/*
	//	ライトビューの座標系を.wで割ることで正規化スクリーン座標系に変換できる。(重要)
	//	*/
	//	shadowMapUV *= float2(0.5f, -0.5f);
	//	shadowMapUV += 0.5f;

	//	float4 posInLVP = mul(mLVP, float4(worldPos, 1.0f));

	//	// ライトビュースクリーン空間でのZ値を計算する。
	//	float zInLVP = posInLVP.z / posInLVP.w;

	//	if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
	//		&& shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f
	//		&& zInLVP > 0.0f && zInLVP < 1.0f
	//		) {
	//		//シャドウマップに描き込まれているZ値と比較する。
	//		float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
	//		if (zInLVP > zInShadowMap) {
	//			finalColor.xyz *= 0.5f;
	//		}
	//	}
	//}

	return finalColor;





	//ここから↓今まで通り


	//float4 color = g_albedo.Sample(g_sampler, psIn.uv);

	//psIn.posInProj.xy /= psIn.posInProj.w;

	//// 法線を計算
	//float3 normal = GetNormal(psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv);

	//float2 uv = psIn.posInProj.xy * float2(0.5f, -0.5f) + 0.5f;

	//// シンプレックスノイズを利用して、UVオフセットを計算する
	//float uOffset = SimplexNoise(float3(uv+ uvNoiseOffset, 0.0f) * 256.0f) * 0.5f;

	////アルベドカラー、スペキュラカラー、金属度をサンプリングする
	//float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv + uOffset * uvNoiseMul);
	//float3 specColor = albedoColor;

	//float3 lig = float3(1.0f, 1.0f, 1.0f, 1.0f);

	//for (int ligNo = 0; ligNo < MAX_DIRECTION_LIGHT; ligNo++) {

	//	float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -directionalLight[ligNo].direction, toEye, 1.0f - smooth);
	//}

	//
	//
	//// 視線に向かって伸びるベクトルを計算する
	//float3 toEye = normalize(eyePos - psIn.worldPos);

	//float3 lig = 0;
	//for (int ligNo = 0; ligNo < NUM_DIRECTIONAL_LIGHT; ligNo++)
	//{
	//	//ディズニーベースの拡散反射を実装する
	//	float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -directionalLight[ligNo].direction, toEye, 1.0f - smooth);

	//	float NdotL = saturate(dot(normal, -directionalLight[ligNo].direction));

	//	float3 lambertDiffuse = directionalLight[ligNo].color * NdotL / PI;
	//	//return float4(toEye, 1.0f);
	//	float3 diffuse = albedoColor * diffuseFromFresnel * lambertDiffuse;
	//	//return float4(diffuse, 1.0f);

	//	//クックトランスモデルを利用した鏡面反射率を計算する
	//	float3 spec = CookTorranceSpecular(-directionalLight[ligNo].direction,
	//		toEye, normal, metaric, 1.0f - smooth) * directionalLight[ligNo].color;

	//	spec *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, smooth);

	//	//鏡面反射率を使って、拡散反射光と鏡面反射光を合成する

	//	lig += diffuse * (1.0f - smooth) + spec * smooth;
	//}

	//// step-7 環境光による底上げ
	//lig += ambinet * albedoColor;

	//float4 finalColor = 1.0f;
	//finalColor.xyz = lig; 

	//if (edge > 0) {
	//	float2 uv = psIn.posInProj.xy * float2(0.5f, -0.5f) + 0.5f;
	//
	//	float2 uvOffset[8] = {
	//		float2(0.0f,  0.5f / 720.0f),
	//		float2(0.0f, -0.5f / 720.0f),
	//		float2(0.5f / 1280.0f,           0.0f),
	//		float2(-0.5f / 1280.0f,           0.0f),
	//		float2(0.5f / 1280.0f,  0.5f / 720.0f),
	//		float2(-0.5f / 1280.0f,  0.5f / 720.0f),
	//		float2(0.5f / 1280.0f, -0.5f / 720.0f),
	//		float2(-0.5f / 1280.0f, -0.5f / 720.0f)
	//	};
	//
	//	float depth = g_depthTexture.Sample(g_sampler, uv).x;
	//
	//	float depth2 = 0.0f;
	//	for (int i = 0; i < 8; i++) {
	//		depth2 += g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).x;
	//	}
	//	depth2 /= 8.0f;
	//	if (abs(depth - depth2) > 0.0005f) {
	//		return float4(0.0f, 0.0f, 0.0f, 1.0f);
	//	}
	//	
	//	float3 normalDistance1 = g_depthTexture.Sample(g_sampler, uv).xyz;
	//	float3 normalDistance2 = 0.0f;
	//	for (int i = 0; i < 8; i++) {
	//		normalDistance2 = g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).xyz;
	//		
	//		
	//		if (edge == 1) {
	//			float t = dot(normalDistance1, normalDistance2);
	//			if (t < 0.5f) {
	//				//法線が結構違う。
	//				t = max(0.0f, t);
	//				t += 0.5f;
	//				finalColor *= pow(t, powValue);
	//				break;
	//			}
	//		}
	//		else if (edge == 2) {

	//			float t = dot(normalDistance1, normalDistance2);
	//			if (t > 0.5f) {
	//				//法線が結構違う。
	//				t = max(0.0f, t);
	//				t -= 0.5f;
	//				t *= 2.0f;
	//				finalColor *= pow(1.0-t, 0.5f);
	//				break;
	//			}
	//		}
	//	}

	//	//ライトビュースクリーン空間からUV空間に座標変換。
	//	float2 shadowMapUV = psIn.posInLVP.xy / psIn.posInLVP.w;

	//	/*
	//	ライトビューの座標系を.wで割ることで正規化スクリーン座標系に変換できる。(重要)
	//	*/
	//	shadowMapUV *= float2(0.5f, -0.5f);
	//	shadowMapUV += 0.5f;

	//	// ライトビュースクリーン空間でのZ値を計算する。
	//	float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;

	//	if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
	//		&& shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f
	//		&& zInLVP > 0.0f && zInLVP < 1.0f
	//		) {
	//		//シャドウマップに描き込まれているZ値と比較する。
	//		float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
	//		if (zInLVP > zInShadowMap) {
	//			finalColor.xyz *= 0.5f;
	//		}
	//	}
	//}

	//return finalColor;
}