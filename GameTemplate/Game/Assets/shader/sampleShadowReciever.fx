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
//cbuffer Lightcb : register(b1){
//	DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];
//	float3 eyePos;
//	float3 ambinet;
//	float4x4 mLVP;
//	float metaric;
//	float smooth;
//	int edge;
//	float powValue;
//	float uvNoiseMul;
//	float uvNoiseOffset;
//	unsigned int ligID;
//};

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
/// <summary>
/// 影が落とされる3Dモデル用のピクセルシェーダー。
/// </summary>
//float4 PSMain( SPSIn psIn ) : SV_Target0
//{
//	//float4 color = g_albedo.Sample(g_sampler, psIn.uv);
//
//	psIn.posInProj.xy /= psIn.posInProj.w;
//
//	// 法線を計算
//	float3 normal = GetNormal(psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv);
//
//	float2 uv = psIn.posInProj.xy * float2(0.5f, -0.5f) + 0.5f;
//
//	// シンプレックスノイズを利用して、UVオフセットを計算する
//	float uOffset = SimplexNoise(float3(uv+ uvNoiseOffset, 0.0f) * 256.0f) * 0.5f;
//
//	// step-2 アルベドカラー、スペキュラカラー、金属度をサンプリングする
//	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv + uOffset * uvNoiseMul);
//	float3 specColor = albedoColor;
//	
//	
//	// 視線に向かって伸びるベクトルを計算する
//	float3 toEye = normalize(eyePos - psIn.worldPos);
//
//	float3 lig = 0;
//	for (int ligNo = 0; ligNo < NUM_DIRECTIONAL_LIGHT; ligNo++)
//	{
//		// step-3 ディズニーベースの拡散反射を実装する
//		float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -directionalLight[ligNo].direction, toEye, 1.0f - smooth);
//
//		float NdotL = saturate(dot(normal, -directionalLight[ligNo].direction));
//
//		float3 lambertDiffuse = directionalLight[ligNo].color * NdotL / PI;
//		//return float4(toEye, 1.0f);
//		float3 diffuse = albedoColor * diffuseFromFresnel * lambertDiffuse;
//		//return float4(diffuse, 1.0f);
//
//		// step-5 クックトランスモデルを利用した鏡面反射率を計算する
//		float3 spec = CookTorranceSpecular(-directionalLight[ligNo].direction,
//			toEye, normal, metaric, 1.0f - smooth) * directionalLight[ligNo].color;
//
//		spec *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, smooth);
//
//		// step-6 鏡面反射率を使って、拡散反射光と鏡面反射光を合成する
//
//		lig += diffuse * (1.0f - smooth) + spec * smooth;
//	}
//
//	// step-7 環境光による底上げ
//	lig += ambinet * albedoColor;
//
//	float4 finalColor = 1.0f;
//	finalColor.xyz = lig; 
//
//	if (edge > 0) {
//		float2 uv = psIn.posInProj.xy * float2(0.5f, -0.5f) + 0.5f;
//	
//		float2 uvOffset[8] = {
//			float2(0.0f,  0.5f / 720.0f),
//			float2(0.0f, -0.5f / 720.0f),
//			float2(0.5f / 1280.0f,           0.0f),
//			float2(-0.5f / 1280.0f,           0.0f),
//			float2(0.5f / 1280.0f,  0.5f / 720.0f),
//			float2(-0.5f / 1280.0f,  0.5f / 720.0f),
//			float2(0.5f / 1280.0f, -0.5f / 720.0f),
//			float2(-0.5f / 1280.0f, -0.5f / 720.0f)
//		};
//	
//		float depth = g_depthTexture.Sample(g_sampler, uv).x;
//	
//		float depth2 = 0.0f;
//		for (int i = 0; i < 8; i++) {
//			depth2 += g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).x;
//		}
//		depth2 /= 8.0f;
//		if (abs(depth - depth2) > 0.0005f) {
//			return float4(0.0f, 0.0f, 0.0f, 1.0f);
//		}
//		
//		float3 normalDistance1 = g_depthTexture.Sample(g_sampler, uv).xyz;
//		float3 normalDistance2 = 0.0f;
//		for (int i = 0; i < 8; i++) {
//			normalDistance2 = g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).xyz;
//			
//			
//			if (edge == 1) {
//				float t = dot(normalDistance1, normalDistance2);
//				if (t < 0.5f) {
//					//法線が結構違う。
//					t = max(0.0f, t);
//					t += 0.5f;
//					finalColor *= pow(t, powValue);
//					break;
//				}
//			}
//			else if (edge == 2) {
//
//				float t = dot(normalDistance1, normalDistance2);
//				if (t > 0.5f) {
//					//法線が結構違う。
//					t = max(0.0f, t);
//					t -= 0.5f;
//					t *= 2.0f;
//					finalColor *= pow(1.0-t, 0.5f);
//					break;
//				}
//			}
//		}
//
//		//ライトビュースクリーン空間からUV空間に座標変換。
//		float2 shadowMapUV = psIn.posInLVP.xy / psIn.posInLVP.w;
//
//		/*
//		ライトビューの座標系を.wで割ることで正規化スクリーン座標系に変換できる。(重要)
//		*/
//		shadowMapUV *= float2(0.5f, -0.5f);
//		shadowMapUV += 0.5f;
//
//		//step-4 ライトビュースクリーン空間でのZ値を計算する。
//		float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;
//
//		if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
//			&& shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f
//			&& zInLVP > 0.0f && zInLVP < 1.0f
//			) {
//			//step-5 シャドウマップに描き込まれているZ値と比較する。
//			float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
//			if (zInLVP > zInShadowMap) {
//				finalColor.xyz *= 0.5f;
//			}
//		}
//	}
//
//	return finalColor;
//	//return albedoColor;
//}

SPSOut PSMain(SPSIn psIn)
{
	SPSOut psOut;
	
	psOut.albedo = g_albedo.Sample(g_sampler, psIn.uv);

	float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;

	float3 normal = psIn.tangent * localNormal.x + psIn.biNormal * localNormal.y + psIn.normal * localNormal.z;

	psOut.normalAndDepth.xyz = (normal / 2.0f) + 0.5f;
	psOut.normalAndDepth.w = g_depthTexture.Sample(g_sampler, psIn.uv).r;
	psOut.worldPosAndLigID.xyz = psIn.worldPos;
	psOut.worldPosAndLigID.w = ligID;

	return psOut;
}