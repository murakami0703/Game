#include "stdafx.h"
#include "SpriteStandby.h"


/// <summary>
/// 頂点バッファの初期化。
/// </summary>
/// <param name="vertexBuffer">頂点バッファ</param>
/// <param name="w">幅</param>
/// <param name="h">高さ</param>
void InitVertexBuffer(ID3D11Buffer*& vertexBuffer, float w, float h)
{
	//頂点の定義。
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;
	SVertex vertex[4] = {
		//頂点1
			{
				-halfW,  -halfH, 0.0f, 1.0f,		//座標　position[4]
				0.0f, 1.0f							//UV座標 uv[2]
			},
		//頂点２
			{
				halfW, -halfH, 0.0f, 1.0f,
				1.0f, 1.0f
			},
		//頂点３
			{
				-halfW,  halfH, 0.0f, 1.0f,
				0.0f, 0.0f
			},
		//頂点４
		{
				halfW,  halfH, 0.0f, 1.0f,
				1.0f, 0.0f
		},


	};
	//上で定義した頂点を使用して頂点バッファの作成。
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));	//初期化。
	bd.Usage = D3D11_USAGE_DEFAULT;	//読み込み及び書き込みの方法。今は気にしない。

	bd.ByteWidth = sizeof(vertex);	//頂点バッファのサイズ。
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;	//これから作成するバッファが頂点バッファであることを指定。

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;	//初期化時に設定するバッファデータ

	//頂点バッファの作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &vertexBuffer);
}
/// <summary>
/// インデックスバッファの初期化。
/// </summary>
/// <param name="indexBuffer">インデックスバッファ</param>
void InitIndexBuffer(ID3D11Buffer*& indexBuffer)
{
	//インデックス。頂点番号。
	int index[6] = {
		0,1,2,		//三角形一つ目
		2,1,3		//三角形二つ目
	};
	//上で定義したインデックスを使用してインデックスバッファを作成。
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));	//初期化。
	bd.Usage = D3D11_USAGE_DEFAULT;	//読み込み及び書き込みの方法。今は気にしない。
	
	bd.ByteWidth = sizeof(index);	//インデックスバッファのサイズ。
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;	//これから作成するバッファがインデックスバッファであることを指定。

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = index;	//初期化時に設定するバッファデータ

	//インデックスバッファの作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &indexBuffer);
}
/// <summary>
/// サンプラステートの初期化。
/// </summary>
/// <param name="samplerState">サンプラステート</param>
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
