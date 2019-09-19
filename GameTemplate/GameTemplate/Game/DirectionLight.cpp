#include "stdafx.h"
#include "DirectionLight.h"



DirectionLight::~DirectionLight()
{
	//ライト用の定数バッファの解放。
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
}

void DirectionLight::Init()
{
	//ディレクションライトの初期化。
	InitDirectionLight();

}
//ディレクションライトの初期化。
void DirectionLight::InitDirectionLight() {
	m_dirLight.direction = { 1.0f, 0.0f, 0.0f, 0.0f };
	m_dirLight.color = { 1.0f, 0.0f, 0.0f, 1.0f };

}
//定数バッファの初期化
void DirectionLight::InitConstantBuffer()
{
	//どんなバッファを作成するのかをbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	//ライト用の定数バッファを作成。
	//作成するバッファのサイズを変更するだけ。
	bufferDesc.ByteWidth = sizeof(SDirectionLight);				//SDirectionLightは16byteの倍数になっているので、切り上げはやらない。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);

}
//更新
void DirectionLight::Update()
{
	//ライトを回す。
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	qRot.Multiply(m_dirLight.direction);
	

}
//描画処理
void DirectionLight::Draw()
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	//ライト用の定数バッファを更新。
	deviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);
	//定数バッファをシェーダースロットに設定。
	deviceContext->PSSetConstantBuffers(0, 1, &m_lightCb);

}
