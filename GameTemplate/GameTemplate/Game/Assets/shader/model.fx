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
/// ���C�g�p�̒萔�o�b�t�@
/// </summary>
cbuffer SLight : register(b1) {
	SDirectionLight		directionLight;		//�f�B���N�V�������C�g
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
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);

	//�@�����v�Z����B
	float3 normal = 0;
	if (isHasNormalMap == 1) {	//�P�Ȃ�@���}�b�v���ݒ肳��Ă���B
		//�]�@���̌v�Z
		//�O�ς��g���B
		float3 biNormal = cross(In.Normal, In.Tangent);
		//�]�@���𐳋K������B
		biNormal = normalize(biNormal);
		//�@���}�b�v���烍�[�J���@�����Ƃ��Ă���B
		float4 normalMap = g_normalMap.Sample(Sampler, In.TexCoord);
		//-1.0�`1.0�͈̔͂ɕϊ�����B
		normalMap = (normalMap * 2.0f) - 1.0f;
		//���[�J���@�������[���h�@���ɂ���B
		normal = normalMap.x * In.Tangent + normalMap.y * biNormal + normalMap.z * In.Normal;
	}
	else{
		//�Ȃ��B
		normal = In.Normal;
	}

	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
	float3 lig = 0.0f;
	for (int i = 0; i < Dcolor; i++) {
		lig += max(0.0f, dot(normal * -1.0f, directionLight.dligDirection[i])) * directionLight.dligColor[i];

		//�f�B���N�V�������C�g�̋��ʔ��ˌ����v�Z����B
		{
			//���˃x�N�g�������߂�B
			float3 r = directionLight.dligDirection[i] + (2 * dot(normal, -directionLight.dligDirection[i]))* normal;

			//���_���烉�C�g�𓖂Ă镨�̂ɐL�т�x�N�g�������߂�B
			float3 e = normalize(In.worldPos - eyePos);

			//�x�N�g���̓��ς��v�Z�B
			float specPower = max(0, dot(r, -e));

			//�X�؃L�������˂����C�g�ɉ��Z����B
			lig += directionLight.dligColor[i].xyz*pow(specPower, specPow);

		}

	}
	if (isShadowReciever == 1) {
		//�V���h�E���V�[�o�[�B
	//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B

		///LVP��Ԃł̐[�x�l���v�Z�B
		float zInLVP = In.posInLVP.z / In.posInLVP.w;
		//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
		float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

		if ((shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f) && zInLVP > zInShadowMap + 0.01f) {
			//�e�������Ă���̂ŁA�����キ����
			lig *= 0.5f;
		}
	}
	

	//�����𓖂Ă�B
	lig += EnvironmentLight;

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
/// �V���h�E�}�b�v�`��p�s�N�Z���V�F�[�_�[�̃G���g���֐��B
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}
