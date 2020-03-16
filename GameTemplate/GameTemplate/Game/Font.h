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

private:
	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//スプライトバッチ。
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//スプライトフォント。

};

