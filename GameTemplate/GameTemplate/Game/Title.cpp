#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title* Title::m_instance = nullptr;

Title::Title()
{
	m_instance = this;

	{
	
		//3”Ô¨Title(”wŒi)
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/title.dds", 1280.0f, 720.0f);
		m_spriteRender.push_back(r);

		//1”Ô¨light
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/light.dds", 1280.0f, 720.0f);
		m_spriteRender.push_back(r);

		//2”Ô¨star_chips(¯‹û)
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/star_chips.dds", 1280.0f, 720.0f);
		m_spriteRender.push_back(r);

	
	}
}


Title::~Title()
{
}

void Title::Update()
{

	if (g_pad[0].IsTrigger(enButtonStart)) {
		g_goMgr->NewGameObject<Game>();

	}

}
