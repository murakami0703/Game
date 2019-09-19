#include "stdafx.h"
#include "DirectionLight.h"



DirectionLight::~DirectionLight()
{
	//���C�g�p�̒萔�o�b�t�@�̉���B
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
}

void DirectionLight::Init()
{
	//�f�B���N�V�������C�g�̏������B
	InitDirectionLight();

}
//�f�B���N�V�������C�g�̏������B
void DirectionLight::InitDirectionLight() {
	m_dirLight.direction = { 1.0f, 0.0f, 0.0f, 0.0f };
	m_dirLight.color = { 1.0f, 0.0f, 0.0f, 1.0f };

}
//�萔�o�b�t�@�̏�����
void DirectionLight::InitConstantBuffer()
{
	//�ǂ�ȃo�b�t�@���쐬����̂���bufferDesc�ɐݒ肷��B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//�O�ŃN���A�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�őz�肳��Ă���A�ǂݍ��݂���я������ݕ��@�B
	//���C�g�p�̒萔�o�b�t�@���쐬�B
	//�쐬����o�b�t�@�̃T�C�Y��ύX���邾���B
	bufferDesc.ByteWidth = sizeof(SDirectionLight);				//SDirectionLight��16byte�̔{���ɂȂ��Ă���̂ŁA�؂�グ�͂��Ȃ��B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);

}
//�X�V
void DirectionLight::Update()
{
	//���C�g���񂷁B
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	qRot.Multiply(m_dirLight.direction);
	

}
//�`�揈��
void DirectionLight::Draw()
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	//���C�g�p�̒萔�o�b�t�@���X�V�B
	deviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);
	//�萔�o�b�t�@���V�F�[�_�[�X���b�g�ɐݒ�B
	deviceContext->PSSetConstantBuffers(0, 1, &m_lightCb);

}
