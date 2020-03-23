#pragma once
class Font
{
	/// <summary>
	/// フォント
	/// </summary>
public:
	Font();
	~Font();
	/// <summary>
	/// フォントを設定。
	/// </summary>
	/// <param name="font">差し替えたいフォント</param>
	void SetFont(DirectX::SpriteFont* font) {
		m_spriteFont = font;
	}
	//描画開始。
	void Begin();
	//描画終了。。
	void End();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="text">表示したいテキスト</param>
	/// <param name="position">座標</param>
	/// <param name="color">カラー</param>
	/// <param name="rotation">回転</param>
	/// <param name="scale">拡大率</param>
	/// <param name="pivot">ピボット</param>
	void Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color = CVector4::White(),
		float rotation = 0.0f,
		float scale = 1.0f,
		CVector2 pivot = { 0.5f, 0.5f }
	);
	/*!
	*@brief	影のパラメータを設定。
	*@param[in]	isDrawShadow		影を描く？
	*@param[in]	shadowOffset		影を描くときのピクセルのオフセット量。
	*@param[in]	shadowColor			影の色。
	*/
	void SetShadowParam(bool isDrawShadow, float shadowOffset, const CVector4& shadowColor = { 0.2f,0.2f,0.2f,1.0f })
	{
		m_isDrawShadow = isDrawShadow;
		m_shadowOffset = shadowOffset;
		m_shadowColor = shadowColor;
	}

private:
	void InitTranslucentBlendState();
	ID3D11Buffer* m_cb = nullptr;		//定数バッファ
	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。

	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//スプライトバッチ。
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//スプライトフォント。

	const CVector4 ShadowColorDef = { 1.0f,1.0f,1.0f,1.0f };	//影の初期色

	bool m_isDrawShadow = false;						//!<影を書く？
	float m_shadowOffset = 0.0f;						//!<影を書くときのピクセルのオフセット量。
	CVector4 m_shadowColor = ShadowColorDef;			//!<影の色。
	CMatrix m_scaleMat;

	ID3D11DepthStencilState*	m_depthStencilStateBackup = nullptr;	//!<現在のデプスステンシルステート。
	ID3D11RasterizerState*		m_rasterrizerStateBackup = nullptr;		//!<現在のラスタライザステート。
	ID3D11BlendState*			m_blendStateBackup = nullptr;			//!<現在のブレンドステート。

};

