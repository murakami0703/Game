#include "stdafx.h"
#include "Font.h"


Font::Font()
{
}


Font::~Font()
{
}

void Font::Draw(wchar_t const* text,const CVector2& position,const CVector4& color,float rotation,float scale,
CVector2 pivot)
{
	pivot.y = 1.0f - pivot.y;
	DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
	//座標系をスプライトと合わせる。
	CVector2 pos = position;
	float frameBufferHalfWidth;
	float frameBufferHalfHeight;
	pos.x += frameBufferHalfWidth;
	pos.y = -pos.y + frameBufferHalfHeight;


	m_spriteFont->DrawString(
		m_spriteBatch,
		text,
		pos.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		scale
	);

}

