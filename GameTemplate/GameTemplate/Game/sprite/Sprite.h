#pragma once
#include "graphics/Shader.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="texFilePath">テクスチャのファイルパス</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	void Init(const wchar_t* texFilePath, float w, float h);
	/// <summary>
	/// テクスチャのSRVを指定して初期化。
	/// </summary>
	/// <param name="srv"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void Init(ID3D11ShaderResourceView* srv, float w, float h);

	/// <summary>
	/// 更新。
	/// </summary>
	/// <param name="pos">平行移動</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大</param>
	/// <param name="pivot">基点</param>
	/// <remarks>
	///		0.5, 0.5で画像の中心が基点。
	/// </remarks>
	void Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });
	//描画。
	void Draw();
	/// <summary>
	/// 乗算カラーを設定
	/// </summary>
	/// <param name="mulColor">乗算カラー</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;
	}
	/// <summary>
	/// 乗算カラーを取得
	/// </summary>
	/// <returns>乗算カラー</returns>
	CVector4 GetMulColor()
	{
		return m_mulColor;
	}

	/// <summary>
	/// a値の設定
	/// </summary>
	void SetAlpha(const float& alpha)
	{
		m_alpha = alpha;
	}
	/// <summary>
	/// a値を取得
	/// </summary>
	float GetAlpha()
	{
		return m_alpha;
	}

	/// <summary>
	/// α値を変位させる
	/// </summary>
	/// <param name="delta">乗算αを変位させる量</param>
	void DeltaAlpha(float delta)
	{
		m_alpha += delta;
		//数値の境界チェック。
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}
	}

	/// <summary>
	/// ブレンドステートを取得。
	/// </summary>
	/// <returns></returns>
	ID3D11BlendState* GetID3D11BlendState()
	{
		return m_translucentBlendState;
	}

	/// <summary>
	/// 表示の設定
	/// </summary>
	/// <param name="flag">false(非表示)</param>
	/// <param name="flag">true(表示)</param>
	void SetActiveFlag(bool& flag)
	{
		m_activeFlag = flag;
	}


	struct ConstantBuffer {
		CMatrix WVP;		//ワールドビュープロジェクション行列。
		CVector4 mulColor;	//乗算カラー。
		float alpha;		//α値。
	};
	ID3D11Buffer*				m_vertexBuffer = NULL;					//頂点バッファ。
	ID3D11Buffer*				m_indexBuffer = NULL;					//インデックスバッファ。
	Shader						m_ps;							//!<ピクセルシェーダー。
	Shader						m_vs;							//!<頂点シェーダー。
	ID3D11ShaderResourceView*	m_texture = NULL;						//テクスチャ。
	ID3D11SamplerState*			m_samplerState = NULL;					//サンプラステート。
	CVector3					m_position = CVector3::Zero();			//座標。
	CQuaternion					m_rotation = CQuaternion::Identity();	//回転
	CVector3					m_scale = CVector3::One();				//拡大率
	CVector4					m_mulColor = {1.0f, 1.0f, 1.0f, 1.0f};	//乗算カラー。
	CMatrix						m_world = CMatrix::Identity();			//ワールド行列。
	CVector2					m_size = CVector2::Zero();				//画像のサイズ。
	ID3D11Buffer*				m_cb = nullptr;							//定数バッファ。
	bool						m_isInited = false;				//!<初期化フラグ。
	float						m_alpha = 1.0f;							//スプライトのα値。
	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。
	bool						m_activeFlag = true;				//表示しますか？

private:
	/*!
	 *@brief	定数バッファの初期化。
	 */
	void InitConstantBuffer();
	/// <summary>
	/// 初期化の共通処理。
	/// </summary>
	void InitCommon(float w, float h);

	/// <summary>
	/// ブレンドステートの初期化
	/// </summary>
	void InitTranslucentBlendState();

};

