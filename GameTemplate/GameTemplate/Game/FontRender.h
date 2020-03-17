#pragma once

class FontRender : public IGameObject
{
public:
	FontRender();
	~FontRender();

	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// 描画。
	/// </summary>
	void Render();
	void PostRender();

public:
	/// <summary>
	/// フォントを設定。
	/// </summary>
	void SetFont(DirectX::SpriteFont* font) {
		m_font.SetFont(font);
	}
	/// <summary>
	/// テキストを設定。
	/// </summary>
	void SetText(const wchar_t* text) {
		if (wcscmp(m_text.c_str(), text) != 0) {
			m_text = text;
		}
	}
	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector2& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// フォントのカラーを設定。
	/// </summary>
	/// <param name="color">色</param>
	void SetColor(const CVector3& color)
	{
		m_color = color;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	/// <param name="color">回転</param>
	void SetRotation(float rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 拡大率を設定。
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(float scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ピボットを設定。
	/// </summary>
	/// <param name="pibot">ピボット</param>
	void SetPibot(const CVector2& pivot)
	{
		m_pivot = pivot;
	}

private:
	Font m_font;
	std::wstring m_text;	//テキスト。
	CVector2 m_position = CVector2::Zero();	//座標。
	float m_rotation = 0.0f;		//回転。
	float m_scale = 1.0f;			//拡大率。
	CVector2 m_pivot;				//ピボット。
	CVector4 m_color = CVector4::White();	//カラー。

};

