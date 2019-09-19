#pragma once

/// <summary>
/// 3Dモデル描画クラス。
/// </summary>
class C3DModelDraw
{
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
	};

	std::unique_ptr<DirectX::Model>		m_modelDx;				//DirectXTKが提供するモデル。
	ID3D11Buffer*		m_cb = nullptr;						//!<定数バッファ。
	ID3D11SamplerState* m_samplerState = nullptr;			//!<サンプラーステート。
	ID3D11ShaderResourceView* m_albedoTextureSRV = nullptr;	//!<アルベドテクスチャのSRV

public:
	~C3DModelDraw();

	void Init();//初期化
	void InitAlbedoTexture();	//アルベドテクスチャを初期化。
	void InitSamplerState();	//サンプラステートの初期化。
	void InitConstantBuffer();	//定数バッファの初期化。
	void Update();				//更新。
	void Draw();				//描画処理。


};

