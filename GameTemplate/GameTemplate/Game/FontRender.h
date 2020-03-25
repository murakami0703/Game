#pragma once
#include "Font.h"
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
	void SetText(const wchar_t* text, CVector2 pos)
	{
		if (wcscmp(m_text.c_str(), text) != 0) {
			//文字列が変わった。
			m_text = text;
		}
		m_position.x = pos.x;
		m_position.y = pos.y;
	}
	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector2& pos)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
	}
	/// <summary>
	/// フォントのカラーを設定。
	/// </summary>
	/// <param name="color">色</param>
	void SetColor(const CVector3& color)
	{
		m_color = color;
	}
	void SetAlpha(float alpha) {
		m_color.w = alpha;
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
		m_pivot.x = pivot.x;
		m_pivot.y = pivot.y;
	}
	/// <summary>
	/// ゲームフォントを取得
	/// </summary>
	/// <returns>ふぉんとに？</returns>
	Font* GetFont() {
		return &m_font;
	}

	/// <summary>
	/// メッセージ送り中ならtrueを返す
	/// </summary>
	/// <returns>メッセージ送りフラグ</returns>
	bool GetMessageOkuriFlag() {
		return m_okuriFlag;
	}

	/// <summary>
	/// テキスト送り演出
	/// </summary>
	/// <param name="text">表示するテキスト</param>
	/// <param name="Interval">1文字ごとのインターバル</param>
	void SetTextOkuri(const wchar_t* text, int Interval);

	/// <summary>
	/// テキスト送りを一瞬で最後まで行います
	/// </summary>
	/// <remarks>
	/// m_okuriFlagはここでは変更されず、Updateのテキスト送り終了処理に一度引っかかります
	/// </remarks>
	void TextOkuriEnd() {
		m_textOkuri_NowLen = m_textOkuri_Len;
		m_textOkuri_Timer = m_textOkuri_Interval;
	}

private:
	Font m_font;
	std::wstring m_text;	//テキスト。
	CVector2 m_position = CVector2::Zero();	//座標。
	float m_rotation = 0.0f;		//回転。
	float m_scale = 1.0f;			//拡大率。
	CVector2 m_pivot;				//ピボット。
	CVector4 m_color = CVector4::White();	//カラー。

	//だんだん表示システム
	wchar_t m_text_stock[256] = L"";			//!<予備テキスト。
	int m_textOkuri_Interval = 0;				//!<テキスト送りのインターバルフレーム
	int m_textOkuri_Timer = 0;					//!<テキスト送りタイマー
	bool m_okuriFlag = false;					//!<メッセージ送り処理のフラグ
	int m_textOkuri_Len = 0;					//!<予備テキストの文字数
	int m_textOkuri_NowLen = 0;					//!<現在の文字数

};

