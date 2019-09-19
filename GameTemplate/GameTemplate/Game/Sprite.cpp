#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	//解放。
	if (m_vertexBuffer != NULL) {
		m_vertexBuffer->Release();
	}
	if (m_indexBuffer != NULL) {
		m_indexBuffer->Release();
	}
	if (m_samplerState != NULL) {
		m_samplerState->Release();
	}
	if (m_texture != NULL) {
		m_texture->Release();
	}

}

//定数バッファの初期化。
void Sprite::InitConstantBuffer()
{
	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_cb);
}

// 初期化。
void Sprite::Init(const wchar_t* texFilePath, float w, float h)
{
	//シェーダーロード。
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);

	m_size.x = w;
	m_size.y = h;
	//頂点バッファの初期化。
	InitVertexBuffer(m_vertexBuffer, w, h);
	//インデックスバッファの初期化。
	InitIndexBuffer(m_indexBuffer);
	//サンプラステートの初期化。
	InitSamplerState(m_samplerState);
	//テクスチャのロード。
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),				//D3Dデバイス。
		texFilePath,				//読み込む画像データのファイルパス。
		0,                          //今は気にしなくてよい。
		D3D11_USAGE_DEFAULT,		//今は気にしなくてよい。
		D3D11_BIND_SHADER_RESOURCE,	//今は気にしなくてよい。
		0,							//今は気にしなくてよい。
		0,							//今は気にしなくてよい。
		false,						//今は気にしなくてよい。
		nullptr,					//今は気にしなくてよい。
		&m_texture					//読み込んだテクスチャに
									//アクセスするためのインターフェースの格納先。
	);

	//定数バッファを初期化。
	InitConstantBuffer();
	m_isInited = true;

}
//更新
void Sprite::Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot)
{
	if (m_isInited == false) {
		//初期化されてない。
		return;
	}
	//ピポットを考慮に入れた平行移動行列を作成。
	//ピボットは真ん中が0.0, 0.0、左上が-1.0f, -1.0、右下が1.0、1.0になるようにする。
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= 2.0f;
	localPivot.x *= 2.0f;
	//画像のハーフサイズを求める。
	CVector2 halfSize = m_size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix m_PivotTrans;

	m_PivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world.Mul(m_PivotTrans, mScale);
	m_world.Mul(m_world, mRot);
	m_world.Mul(m_world, mTrans);

}

//描画
void Sprite::Draw()
{
	if (m_isInited == false) {
		//初期化されていない。
		return;
	}
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	unsigned int vertexSize = sizeof(SVertex);	//頂点のサイズ。
	unsigned int offset = 0;
	deviceContext->IASetVertexBuffers(	//頂点バッファを設定。
		0,					//StartSlot番号。今は0でいい。
		1,					//バッファの数。今は1でいい。
		&m_vertexBuffer,	//頂点バッファ。
		&vertexSize,		//頂点のサイズ。
		&offset				//気にしなくてよい。
	);
	deviceContext->IASetIndexBuffer(	//インデックスバッファを設定。
		m_indexBuffer,			//インデックスバッファ。
		DXGI_FORMAT_R32_UINT,	//インデックスのフォーマット。
								//今回は32bitなので、DXGI_FORMAT_R32_UINTでいい。
		0						//オフセット0でいい。
	);

	//テクスチャを設定。
	deviceContext->PSSetShaderResources(0, 1, &m_texture);
	//サンプラステートを設定。
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//ワールドビュープロジェクション行列を作成。
	ConstantBuffer cb;
	cb.WVP = m_world;
	cb.WVP.Mul(cb.WVP, g_camera2D.GetViewMatrix());
	cb.WVP.Mul(cb.WVP, g_camera2D.GetProjectionMatrix());
	cb.mulColor = m_mulColor;
	deviceContext->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	deviceContext->PSSetConstantBuffers(0, 1, &m_cb);

	deviceContext->IASetInputLayout(m_vs.GetInputLayout());
	deviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
	deviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
	//プリミティブのトポロジーは
	//トライアングルストリップを設定する。
	deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->DrawIndexed(	//描画命令。
		6,				//インデックス数。
		0,				//開始インデックス番号。0でいい。
		0				//開始頂点番号。0でいい。
	);

}
