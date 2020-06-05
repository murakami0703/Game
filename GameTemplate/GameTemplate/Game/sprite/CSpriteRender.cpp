#include "stdafx.h"
#include "sprite/CSpriteRender.h"
#include "Sprite.h"



CSpriteRender::CSpriteRender() {

}
CSpriteRender::~CSpriteRender()
{

}
void CSpriteRender::Init(const wchar_t* texFilePath, float w, float h)
{
		m_sprite.Init(texFilePath, w, h);
}

void CSpriteRender::Update()
{
		m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
		m_sprite.Draw();
}