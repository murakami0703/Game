/*!
 * @brief	���f���V�F�[�_�[�B
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
Texture2D<float4> g_shadowMap : register(t2);		//�V���h�E�}�b�v�B
Texture2D<float4> g_normalMap : register(t3);		//	�@���}�b�v�B
Texture2D<float4> g_specularMap : register(t4);		//	�X�؃L�����}�b�v�B
Texture2D<float4> g_aoMap : register(t5);			//AO�}�b�v�B

//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;	//���C�g�r���[�s��B
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��B
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
	int isHasNormalMap;		//�@���}�b�v�t���O�B
	int isHasSpecularMap;	//�X�؃L�����}�b�v�t���O�B
	int isHasAmbientMap;	//�A���r�G���g�}�b�v�t���O
	float alpha;			//���l�B
};

/// <summary>
/// �f�B���N�V�������C�g�̒萔�o�b�t�@
/// </summary>
static const int Dcolor = 4;

struct SDirectionLight {
	float3 dligDirection[Dcolor];
	float4 dligColor[Dcolor];

};

/// <summary>
/// �|�C���g���C�g�̒萔�o�b�t�@
/// </summary>

static const int NUM_POINT_LIGHT = 4;

struct SPointLight {
	float3 position[NUM_POINT_LIGHT];
	float4 color[NUM_POINT_LIGHT];
	float4 range[NUM_POINT_LIGHT];

};

/// <summary>
/// ���C�g�p�̒萔�o�b�t�@
/// </summary>
cbuffer SLight : register(b1) {
	SDirectionLight		directionLight;		//�f�B���N�V�������C�g
//	SPointLight		pointLight;		//�|�C���g���C�g
	float3			eyePos;				//���_�̍��W�B
	float			specPow;			//���ʔ��˂̍i��B
	float3			EnvironmentLight;				//�����B
};

/// <summary>
/// �V���h�E�}�b�v�p�̒萔�o�b�t�@
/// </summary>
cbuffer ShadowMapCb : register(b2) {
	float4x4 lightViewProjMatrix;	//���C�g�r���[�v���W�F�N�V�����s��B
}

/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//���[���h���W
	float4 posInLVP		: TEXCOORD2;	//���C�g�r���[�v���W�F�N�V������Ԃł̍��W�B
};

/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�ւ̓��́B
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 	: SV_POSITION;	//���W�B
};

/*!
 *@brief	�X�L���s����v�Z�B
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
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	float4 shadowPos = pos;
	//���ʔ��˂̌v�Z�̂��߂ɁA���[���h���W���s�N�Z���V�F�[�_�[�ɓn���B
	psInput.worldPos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);


	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
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
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
	    pos = mul(skinning, In.Position);
	}


	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
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
/// �@���}�b�v�̌v�Z�B
/// </summary>
float3 NormalCalc(float3 normal, float3 tangent, float2 uv) {

	float3 normalCaleMap = 0;
	if (isHasNormalMap == 1) {	//�P�Ȃ�@���}�b�v���ݒ肳��Ă���B
		//�]�@���̌v�Z
		//�O�ς��g���B
		float3 biNormal = cross(normal, tangent);
		//�]�@���𐳋K������B
		biNormal = normalize(biNormal);
		//�@���}�b�v���烍�[�J���@�����Ƃ��Ă���B
		float4 normalMap = g_normalMap.Sample(Sampler, uv);
		//-1.0�`1.0�͈̔͂ɕϊ�����B
		normalMap = (normalMap * 2.0f) - 1.0f;
		//���[�J���@�������[���h�@���ɂ���B
		normalCaleMap = normalMap.x * tangent + normalMap.y * biNormal + normalMap.z * normal;
	}
	else {
		//�Ȃ��B
		normalCaleMap = normal;
	}
	return normalCaleMap;
}
/// <summary>
/// �f�B���N�V�������C�g�̌v�Z�B
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
/// �|�C���g���C�g�̌v�Z�B
/// </summary>
float3 PointCalc(float3 normal, float3 worldPos)
{
	float3 lig = 0.0f;
	//�|�C���g���C�g������ɂ�郉���o�[�g�g�U���˂��v�Z�B
/*	for (int i = 0; i < NUM_POINT_LIGHT; i++) {
		//�P�D��������T�[�t�@�C�X�ɓ��˂���x�N�g�����v�Z�B
		float3 ligDir = normalize(worldPos - pointLight.position[i]);
		//�Q�D��������T�[�t�F�C�X�܂ł̋������v�Z�B
		float distance = length(worldPos - pointLight.position[i]);
		//�R�D���̓��˃x�N�g���ƃT�[�t�F�C�X�̖@���œ��ς�����Ĕ��˂̋������v�Z����B
		float t = max(0.0f, dot(-ligDir, normal));
		//�S�D�e�������v�Z����B�e������0.0�`1.0�͈̔͂ŁA
		//    �w�肵������(pointLight[i].range)�𒴂�����A�e������0.0�ɂȂ�B
		float affect = 1.0f - min(1.0f, distance / pointLight.range[i]);
		lig += pointLight.color[i] * t * affect;
	}*/
	return lig;
}

/// <summary>
/// �X�؃L�������C�g�̌v�Z�B
/// </summary>
float3 SpecularCalc(float3 normal, float3 worldPos, float2 uv)
{
	float3 lig = 0.0f;
	for (int i = 0; i < Dcolor; i++) {

		//���_���烉�C�g�𓖂Ă镨�̂ɐL�т�x�N�g�������߂�B
		float3 toEye = normalize(eyePos - worldPos);

		//���˃x�N�g�������߂�B
		float3 reflectEye = -toEye + 2 * dot(normal, toEye)* normal;

		//���˃x�N�g���ƃf�B���N�V�������C�g�̕����Ƃ̓��ς�����āA�X�y�L�����̋������v�Z�B
		float t = max(0.0f, dot(-directionLight.dligDirection[i], reflectEye));
		//�X�؃L�����̍i��
		float specPower = 0.0f;
		if (isHasSpecularMap) {
			specPower = g_specularMap.Sample(Sampler, uv).r;
		}
		float3 specLig = pow(t, specPow) * directionLight.dligColor[i] * specPower * directionLight.dligColor[i].w;
		//���ʔ��˂𔽎ˌ��ɉ��Z����B
		lig += specLig;
	}
	return lig;

}
/// <summary>
/// �V���h�E�̌v�Z
/// </summary>
void ShadowCalc(inout float3 lig, float4 posInLvp)
{
	if (isShadowReciever == 1) {
		//�V���h�E���V�[�o�[�B
	//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = posInLvp.xy / posInLvp.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B

		///LVP��Ԃł̐[�x�l���v�Z�B
		float zInLVP = posInLvp.z / posInLvp.w;
		//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
		float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

		if ((shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f) && zInLVP > zInShadowMap + 0.001f) {
			//�e�������Ă���̂ŁA�����キ����
			lig *= 0.5f;
		}
	}


}
/// <summary>
/// �A���r�G���g���C�g�̌v�Z�B
/// </summary>
float3 AmbientCalc(float4 albedoColor, float2 uv)
{
	float3 Calc;
	if (isHasAmbientMap == 1) {
		//AO����yo
		float3 Ambient = g_aoMap.Sample(Sampler, uv);
		Calc = albedoColor.xyz * EnvironmentLight*Ambient;
	}
	else {
		Calc = albedoColor.xyz * EnvironmentLight;
	}
	return Calc;
}

//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	//�e�N�X�`���J���[�̃��l����Z�B
	albedoColor.a *= alpha;

	float3 normal = NormalCalc(In.Normal, In.Tangent, In.TexCoord);
	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
	float3 lig = 0.0f;

	//�f�B�t���[�Y���C�g�����Z�B
	lig += DirectionCalc(normal);

	//�|�C���g���C�g�����Z�B
	//lig +=PointCalc(normal, In.worldPos);

	//�X�y�L�������C�g�����Z�B
	lig += SpecularCalc(normal, In.worldPos, In.TexCoord);

	//�A���r�G���g���C�g�����Z�B
	lig += AmbientCalc(albedoColor, In.TexCoord);

	//�f�v�X�V���h�E�}�b�v���g���ĉe�𗎂Ƃ��B�B
	ShadowCalc(lig, In.posInLVP);
	
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}
//--------------------------------------------------------------------------------------
// �V���G�b�g�`��p�̃s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

/// <summary>
/// �V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
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
/// �X�L�����f������̃V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
/// </summary>
PSInput_ShadowMap VSMain_ShadowMapSkinModel(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 skinning = 0;
	float w = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
		//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
		//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
		skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
		w += In.Weights[i];
	}
	//�Ō�̃{�[�����v�Z����B
	skinning += boneMatrix[In.Indices[3]] * (1.0f - w);

	float4 pos = mul(skinning, In.Position);

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/// <summary>
/// �V���h�E�}�b�v�`��p�s�N�Z���V�F�[�_�[�̃G���g���֐��B
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}
