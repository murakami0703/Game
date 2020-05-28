#include "stdafx.h"
#include "FontRender.h"


FontRender::FontRender()
{
}


FontRender::~FontRender()
{
}

void FontRender::Update()
{
}
void FontRender::PostRender()
{
	m_font.Begin();

	const wchar_t* text = nullptr;

	if (m_text.c_str() != nullptr) {
		text = m_text.c_str();
	}
	
	m_font.Draw(
		text,
		m_position,
		m_color,
		m_rotation,
		m_scale,
		m_pivot
	);
	m_font.End();
}
void FontRender::SetTextOkuri(const wchar_t* text, int Interval) {

	//‰Šú‰»‚Æİ’è
	m_text = { L"" };

	m_textOkuri_Len = (int)wcslen(text);	//•¶š”‚ğæ“¾
	for (int n = 0; n < m_textOkuri_Len + 1; n++) {
		m_text_stock[n] = text[n];
	}

	m_textOkuri_Interval = Interval;
	m_textOkuri_Timer = 0;
	m_okuriFlag = true;
	m_textOkuri_NowLen = -1;

}