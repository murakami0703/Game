#include "stdafx.h"
#include "SpriteStandby.h"


/// <summary>
/// ���_�o�b�t�@�̏������B
/// </summary>
/// <param name="vertexBuffer">���_�o�b�t�@</param>
/// <param name="w">��</param>
/// <param name="h">����</param>
void InitVertexBuffer(ID3D11Buffer*& vertexBuffer, float w, float h)
{
	//���_�̒�`�B
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;
	SVertex vertex[4] = {
		//���_1
			{
				-halfW,  -halfH, 0.0f, 1.0f,		//���W�@position[4]
				0.0f, 1.0f							//UV���W uv[2]
			},
		//���_�Q
			{
				halfW, -halfH, 0.0f, 1.0f,
				1.0f, 1.0f
			},
		//���_�R
			{
				-halfW,  halfH, 0.0f, 1.0f,
				0.0f, 0.0f
			},
		//���_�S
		{
				halfW,  halfH, 0.0f, 1.0f,
				1.0f, 0.0f
		},


	};
	//��Œ�`�������_���g�p���Ē��_�o�b�t�@�̍쐬�B
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));	//�������B
	bd.Usage = D3D11_USAGE_DEFAULT;	//�ǂݍ��݋y�я������݂̕��@�B���͋C�ɂ��Ȃ��B

	bd.ByteWidth = sizeof(vertex);	//���_�o�b�t�@�̃T�C�Y�B
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;	//���ꂩ��쐬����o�b�t�@�����_�o�b�t�@�ł��邱�Ƃ��w��B

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;	//���������ɐݒ肷��o�b�t�@�f�[�^

	//���_�o�b�t�@�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &vertexBuffer);
}
/// <summary>
/// �C���f�b�N�X�o�b�t�@�̏������B
/// </summary>
/// <param name="indexBuffer">�C���f�b�N�X�o�b�t�@</param>
void InitIndexBuffer(ID3D11Buffer*& indexBuffer)
{
	//�C���f�b�N�X�B���_�ԍ��B
	int index[6] = {
		0,1,2,		//�O�p�`���
		2,1,3		//�O�p�`���
	};
	//��Œ�`�����C���f�b�N�X���g�p���ăC���f�b�N�X�o�b�t�@���쐬�B
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));	//�������B
	bd.Usage = D3D11_USAGE_DEFAULT;	//�ǂݍ��݋y�я������݂̕��@�B���͋C�ɂ��Ȃ��B
	
	bd.ByteWidth = sizeof(index);	//�C���f�b�N�X�o�b�t�@�̃T�C�Y�B
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;	//���ꂩ��쐬����o�b�t�@���C���f�b�N�X�o�b�t�@�ł��邱�Ƃ��w��B

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = index;	//���������ɐݒ肷��o�b�t�@�f�[�^

	//�C���f�b�N�X�o�b�t�@�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &indexBuffer);
}
/// <summary>
/// �T���v���X�e�[�g�̏������B
/// </summary>
/// <param name="samplerState">�T���v���X�e�[�g</param>
void InitSamplerState(ID3D11SamplerState*& samplerState)
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &samplerState);

}
