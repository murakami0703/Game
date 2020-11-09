/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
Texture2D<float4> g_shadowMap : register(t2);		//シャドウマップ。
Texture2D<float4> g_normalMap : register(t3);		//	法線マップ。
Texture2D<float4> g_specularMap : register(t4);		//	スぺキュラマップ。
Texture2D<float4> g_aoMap : register(t5);			//AOマップ。

//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
	int isHasNormalMap;		//法線マップフラグ。
	int isHasSpecularMap;	//スぺキュラマップフラグ。
	int isHasAmbientMap;	//アンビエントマップフラグ
	float alpha;			//α値。
};

/// <summary>
/// ディレクションライトの定数バッファ
/// </summary>
static const int Dcolor = 4;

struct SDirectionLight {
	float3 dligDirection[Dcolor];
	float4 dligColor[Dcolor];

};

/// <summary>
/// ポイントライトの定数バッファ
/// </summary>

static const int NUM_POINT_LIGHT = 4;

struct SPointLight {
	float3 position[NUM_POINT_LIGHT];
	float4 color[NUM_POINT_LIGHT];
	float4 range[NUM_POINT_LIGHT];

};

/// <summary>
/// ライト用の定数バッファ
/// </summary>
cbuffer SLight : register(b1) {
	SDirectionLight		directionLight;		//ディレクションライト
//	SPointLight		pointLight;		//ポイントライト
	float3			eyePos;				//視点の座標。
	float			specPow;			//鏡面反射の絞り。
	float3			EnvironmentLight;				//環境光。
};

/// <summary>
/// シャドウマップ用の定数バッファ
/// </summary>
cbuffer ShadowMapCb : register(b2) {
	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
}

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション空間での座標。
};

/// <summary>
/// シャドウマップ用のピクセルシェーダへの入力。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 	: SV_POSITION;	//座標。
};

/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	float4 shadowPos = pos;
	//鏡面反射の計算のために、ワールド座標をピクセルシェーダーに渡す。
	psInput.worldPos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);


	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, shadowPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;

	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	}


	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, pos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
/// <summary>
/// 法線マップの計算。
/// </summary>
float3 NormalCalc(float3 normal, float3 tangent, float2 uv) {

	float3 normalCaleMap = 0;
	if (isHasNormalMap == 1) {	//１なら法線マップが設定されている。
		//従法線の計算
		//外積を使う。
		float3 biNormal = cross(normal, tangent);
		//従法線を正規化する。
		biNormal = normalize(biNormal);
		//法線マップからローカル法線をとってくる。
		float4 normalMap = g_normalMap.Sample(Sampler, uv);
		//-1.0～1.0の範囲に変換する。
		normalMap = (normalMap * 2.0f) - 1.0f;
		//ローカル法線をワールド法線にする。
		normalCaleMap = normalMap.x * tangent + normalMap.y * biNormal + normalMap.z * normal;
	}
	else {
		//ない。
		normalCaleMap = normal;
	}
	return normalCaleMap;
}
/// <summary>
/// ディレクションライトの計算。
/// </summary>
float3 DirectionCalc(float3 normal)
{
	float3 lig = 0.0f;
	for (int i = 0; i < Dcolor; i++) {
		lig += max(0.0f, dot(normal * -1.0f, directionLight.dligDirection[i])) * directionLight.dligColor[i];
	}
	return lig;
}
/// <summary>
/// ポイントライトの計算。
/// </summary>
float3 PointCalc(float3 normal, float3 worldPos)
{
	float3 lig = 0.0f;
	//ポイントライトから光によるランバート拡散反射を計算。
/*	for (int i = 0; i < NUM_POINT_LIGHT; i++) {
		//１．光源からサーファイスに入射するベクトルを計算。
		float3 ligDir = normalize(worldPos - pointLight.position[i]);
		//２．光源からサーフェイスまでの距離を計算。
		float distance = length(worldPos - pointLight.position[i]);
		//３．光の入射ベクトルとサーフェイスの法線で内積を取って反射の強さを計算する。
		float t = max(0.0f, dot(-ligDir, normal));
		//４．影響率を計算する。影響率は0.0～1.0の範囲で、
		//    指定した距離(pointLight[i].range)を超えたら、影響率は0.0になる。
		float affect = 1.0f - min(1.0f, distance / pointLight.range[i]);
		lig += pointLight.color[i] * t * affect;
	}*/
	return lig;
}

/// <summary>
/// スぺキュラライトの計算。
/// </summary>
float3 SpecularCalc(float3 normal, float3 worldPos, float2 uv)
{
	float3 lig = 0.0f;
	for (int i = 0; i < Dcolor; i++) {

		//視点からライトを当てる物体に伸びるベクトルを求める。
		float3 toEye = normalize(eyePos - worldPos);

		//反射ベクトルを求める。
		float3 reflectEye = -toEye + 2 * dot(normal, toEye)* normal;

		//反射ベクトルとディレクションライトの方向との内積を取って、スペキュラの強さを計算。
		float t = max(0.0f, dot(-directionLight.dligDirection[i], reflectEye));
		//スぺキュラの絞り
		float specPower = 0.0f;
		if (isHasSpecularMap) {
			specPower = g_specularMap.Sample(Sampler, uv).r;
		}
		float3 specLig = pow(t, specPow) * directionLight.dligColor[i] * specPower * directionLight.dligColor[i].w;
		//鏡面反射を反射光に加算する。
		lig += specLig;
	}
	return lig;

}
/// <summary>
/// シャドウの計算
/// </summary>
void ShadowCalc(inout float3 lig, float4 posInLvp)
{
	if (isShadowReciever == 1) {
		//シャドウレシーバー。
	//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
		float2 shadowMapUV = posInLvp.xy / posInLvp.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//シャドウマップの範囲内かどうかを判定する。

		///LVP空間での深度値を計算。
		float zInLVP = posInLvp.z / posInLvp.w;
		//シャドウマップに書き込まれている深度値を取得。
		float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

		if ((shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f) && zInLVP > zInShadowMap + 0.001f) {
			//影が落ちているので、光を弱くする
			lig *= 0.5f;
		}
	}


}
/// <summary>
/// アンビエントライトの計算。
/// </summary>
float3 AmbientCalc(float4 albedoColor, float2 uv)
{
	float3 Calc;
	if (isHasAmbientMap == 1) {
		//AOあるyo
		float3 Ambient = g_aoMap.Sample(Sampler, uv);
		Calc = albedoColor.xyz * EnvironmentLight*Ambient;
	}
	else {
		Calc = albedoColor.xyz * EnvironmentLight;
	}
	return Calc;
}

//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	//テクスチャカラーのα値を乗算。
	albedoColor.a *= alpha;

	float3 normal = NormalCalc(In.Normal, In.Tangent, In.TexCoord);
	//ディレクションライトの拡散反射光を計算する。
	float3 lig = 0.0f;

	//ディフューズライトを加算。
	lig += DirectionCalc(normal);

	//ポイントライトを加算。
	//lig +=PointCalc(normal, In.worldPos);

	//スペキュラライトを加算。
	lig += SpecularCalc(normal, In.worldPos, In.TexCoord);

	//アンビエントライトを加算。
	lig += AmbientCalc(albedoColor, In.TexCoord);

	//デプスシャドウマップを使って影を落とす。。
	ShadowCalc(lig, In.posInLVP);
	
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}
//--------------------------------------------------------------------------------------
// シルエット描画用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

/// <summary>
/// シャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In) 
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
/// <summary>
/// スキンモデルありのシャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMain_ShadowMapSkinModel(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 skinning = 0;
	float w = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		//boneMatrixにボーン行列が設定されていて、
		//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
		//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
		skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
		w += In.Weights[i];
	}
	//最後のボーンを計算する。
	skinning += boneMatrix[In.Indices[3]] * (1.0f - w);

	float4 pos = mul(skinning, In.Position);

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/// <summary>
/// シャドウマップ描画用ピクセルシェーダーのエントリ関数。
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}
