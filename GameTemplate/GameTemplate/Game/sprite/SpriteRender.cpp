#include "stdafx.h"
#include "SpriteRender.h"




	void SpriteRender::Init(const wchar_t* texFilePath, float w, float h)
	{
		m_sprite.Init(texFilePath, w, h);
	}

	void SpriteRender::Init(ID3D11ShaderResourceView* srv, float w, float h)
	{
		m_sprite.Init(srv, w, h);
	}

	void SpriteRender::Update()
	{
		m_sprite.Update(m_position, m_rotation, m_scale);
	}
	void SpriteRender::PostRender()
	{
		m_sprite.Draw();
	}
