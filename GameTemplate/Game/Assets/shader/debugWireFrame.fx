/*!
 * @brief	ラインプリミティブ用のシェーダー。
 */

cbuffer CB : register(b0){
	float4x4 mView;
	//float4x4 mProj;
};

//頂点シェーダーへの入力。
struct SVSIn {
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float4 col		: COLOR;
};
//ピクセルシェーダーへの入力。
struct SPSIn {
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float4 col			: COLOR;
};


/*!
 * @brief	頂点シェーダー
 */
SPSIn VSMain(SVSIn vsIn)
{
	
	SPSIn psIn;
	
	psIn.pos = mul(mView, vsIn.pos);
	//psIn.pos = mul(mProj, psIn.pos);

	psIn.col = vsIn.col;
	return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{
	return float4( 0.0f, 0.0f, 1.0f, 1.0f );
	//return psIn.col;
}
