#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title* Title::m_instance = nullptr;

Title::Title()
{
	m_instance = this;

	{
		//3”Ô¨Title(”wŒi)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/title.dds", 1280.0f, 720.0f);
		m_spriteRender.push_back(m_titleSprite);

		//1”Ô¨light
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/light.dds", 1280.0f, 720.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_titleSprite);

		//2”Ô¨star_chips(¯‹û)
		m_titleSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_titleSprite->Init(L"Assets/sprite/star_chips.dds", 1280.0f, 720.0f);
		m_titleSprite->SetAlpha(0.0f);
		m_spriteRender.push_back(m_titleSprite);
	}
}


Title::~Title()
{
}
void Title::LightFlashing()
{
	m_flashingTimer++;
	if (m_flashingTimer <= 30.0f) {

	}
	else if (m_flashingTimer <= 60.0f)
	{

	}
}
void Title::Update()
{


	if (g_pad[0].IsTrigger(enButtonStart)) {
		g_goMgr->NewGameObject<Game>();

	}

}
