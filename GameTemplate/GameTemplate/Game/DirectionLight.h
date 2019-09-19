#pragma once
class DirectionLight
{
	/// <summary>
	/// ディレクションライト
	/// </summary>
	struct SDirectionLight {
		CVector4 direction;		//ライトの方向。
		CVector4 color;			//ライトのカラー。
	};
	ID3D11Buffer*		m_lightCb = nullptr;				//!<ライト用の定数バッファ。
	SDirectionLight		m_dirLight;							//!<ディレクションライト。
	
public:
	~DirectionLight();
	void Init();				//初期化。
	void InitDirectionLight();	//ディレクションライトの初期化。
	void InitConstantBuffer();	//定数バッファの初期化
	void Update();				//更新。
	void Draw();				//描画。
};

