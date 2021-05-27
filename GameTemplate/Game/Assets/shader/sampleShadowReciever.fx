/*!
 * @brief	影が落とされるモデル用のシェーダー。
 */
static const int NUM_DIRECTIONAL_LIGHT = 8;
static const float PI = 3.1415926f;         // π


struct DirectionalLight
{
	float3 direction;
	float4 color;
	//float4x4 mLVP;
};

//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};
//ライトビュープロジェクション行列にアクセする定数バッファを定義。
cbuffer ShadowCb : register(b1){
	DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];
	float3 eyePos;
	float3 ambinet;
	float4x4 mLVP;
	float metaric;
	float smooth;
	int edge;
	float powValue;
	float uvNoiseMul;
	float uvNoiseOffset;
};

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

///////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////

Texture2D<float4> g_albedo : register(t0);		//アルベドマップ。
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_shadowMap : register(t10);	//シャドウマップ。
Texture2D<float4> g_depthTexture : register(t11);	//深度テクスチャ。
sampler g_sampler : register(s0);				// サンプラステート。


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

	psIn.tangent = mul(mWorld, vsIn.tangent);
	psIn.biNormal = mul(mWorld, vsIn.biNormal);

	//ライトビュースクリーン空間の座標を計算する。
	psIn.posInLVP = mul( mLVP, float4( psIn.worldPos,1.0f ) );

	psIn.posInProj = psIn.pos;
	

	return psIn;
}
/// <summary>
/// 影が落とされる3Dモデル用のピクセルシェーダー。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	//float4 color = g_albedo.Sample(g_sampler, psIn.uv);

	psIn.posInProj.xy /= psIn.posInProj.w;

	// 法線を計算
	float3 normal = GetNormal(psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv);

	float2 uv = psIn.posInProj.xy * float2(0.5f, -0.5f) + 0.5f;

	// シンプレックスノイズを利用して、UVオフセットを計算する
	float uOffset = SimplexNoise(float3(uv+ uvNoiseOffset, 0.0f) * 256.0f) * 0.5f;

	// step-2 アルベドカラー、スペキュラカラー、金属度をサンプリングする
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv + uOffset * uvNoiseMul);
	float3 specColor = albedoColor;
	
	
	// 視線に向かって伸びるベクトルを計算する
	float3 toEye = normalize(eyePos - psIn.worldPos);

	float3 lig = 0;
	for (int ligNo = 0; ligNo < NUM_DIRECTIONAL_LIGHT; ligNo++)
	{
		// step-3 ディズニーベースの拡散反射を実装する
		float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -directionalLight[ligNo].direction, toEye, 1.0f - smooth);

		float NdotL = saturate(dot(normal, -directionalLight[ligNo].direction));

		float3 lambertDiffuse = directionalLight[ligNo].color * NdotL / PI;
		//return float4(toEye, 1.0f);
		float3 diffuse = albedoColor * diffuseFromFresnel * lambertDiffuse;
		//return float4(diffuse, 1.0f);

		// step-5 クックトランスモデルを利用した鏡面反射率を計算する
		float3 spec = CookTorranceSpecular(-directionalLight[ligNo].direction,
			toEye, normal, metaric, 1.0f - smooth) * directionalLight[ligNo].color;


		spec *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, smooth);

		// step-6 鏡面反射率を使って、拡散反射光と鏡面反射光を合成する

		lig += diffuse * (1.0f - smooth) + spec * smooth;
	}

	// step-7 環境光による底上げ
	lig += ambinet * albedoColor;

	float4 finalColor = 1.0f;
	finalColor.xyz = lig;
	//return finalColor;

	//ライトビュースクリーン空間からUV空間に座標変換。
	float2 shadowMapUV = psIn.posInLVP.xy / psIn.posInLVP.w;

	/*
	ライトビューの座標系を.wで割ることで正規化スクリーン座標系に変換できる。(重要)
	*/
	shadowMapUV *= float2( 0.5f, -0.5f);
	shadowMapUV += 0.5f; 

	//step-4 ライトビュースクリーン空間でのZ値を計算する。
	float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;



	if( shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
		&& shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f
		&& zInLVP > 0.0f && zInLVP  < 1.0f
	){
		//step-5 シャドウマップに描き込まれているZ値と比較する。
		
		float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
		if (zInLVP > zInShadowMap) {
			finalColor.xyz *= 0.5f;
		}
	} 

	if (edge > 0) {
		float2 uv = psIn.posInProj.xy * float2(0.5f, -0.5f) + 0.5f;
	
		float2 uvOffset[8] = {
			float2(0.0f,  0.5f / 720.0f),
			float2(0.0f, -0.5f / 720.0f),
			float2(0.5f / 1280.0f,           0.0f),
			float2(-0.5f / 1280.0f,           0.0f),
			float2(0.5f / 1280.0f,  0.5f / 720.0f),
			float2(-0.5f / 1280.0f,  0.5f / 720.0f),
			float2(0.5f / 1280.0f, -0.5f / 720.0f),
			float2(-0.5f / 1280.0f, -0.5f / 720.0f)
		};
	
		float depth = g_depthTexture.Sample(g_sampler, uv).x;
	
		float depth2 = 0.0f;
		for (int i = 0; i < 8; i++) {
			depth2 += g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).x;
		}
		depth2 /= 8.0f;
		/*if (abs(depth - depth2) > 0.0005f) {
			return float4(0.0f, 0.0f, 0.0f, 1.0f);
		}*/
		
		float3 normalDistance1 = g_depthTexture.Sample(g_sampler, uv).xyz;
		float3 normalDistance2 = 0.0f;
		for (int i = 0; i < 8; i++) {
			normalDistance2 = g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).xyz;
			
			
			if (edge == 1) {
				float t = dot(normalDistance1, normalDistance2);
				if (t < 0.5f) {
					//法線が結構違う。
					t = max(0.0f, t);
					t += 0.5f;
					finalColor *= pow(t, powValue);
					break;
				}
			}
			else if (edge == 2) {

				float t = dot(normalDistance1, normalDistance2);
				if (t > 0.5f) {
					//法線が結構違う。
					t = max(0.0f, t);
					t -= 0.5f;
					t *= 2.0f;
					finalColor *= pow(1.0-t, 0.5f);
					break;
				}
			}
		}
		
		/*float normalDistance1a = g_depthTexture.Sample(g_sampler, uv).y;
		float normalDistance2a = 0.0f;
		for (int i = 0; i < 8; i++) {
			normalDistance2a += g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).y;
		}
		normalDistance2a /= 8.0f;
		if (abs(normalDistance1a - normalDistance2a) > 0.1f) {
			return float4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	
		float normalDistance3a = g_depthTexture.Sample(g_sampler, uv).z;
		float normalDistance4a = 0.0f;
		for (int i = 0; i < 8; i++) {
			normalDistance4a += g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).z;
		}
		normalDistance4a /= 8.0f;
		if (abs(normalDistance3a - normalDistance4a) > 0.1f) {
			return float4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	
		float normalDistance5a = g_depthTexture.Sample(g_sampler, uv).w;
		float normalDistance6a = 0.0f;
		for (int i = 0; i < 8; i++) {
			normalDistance6a += g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).w;
		}
		normalDistance6a /= 8.0f;
		if (abs(normalDistance5a - normalDistance6a) > 0.1f) {
			return float4(0.0f, 0.0f, 0.0f, 1.0f);
		}*/
	}

	return finalColor;
	//return albedoColor;
}