#include "stdafx.h"
#include "Item.h"


Item::Item()
{
	//ƒAƒCƒeƒ€
	{
		//0”Ô¨‰ñ•œ–ò
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

		//1”Ô¨”š’e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

		//2”Ô¨UŒ‚—ÍUP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

		//3”Ô¨ˆÚ“®‘¬“xUP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

	}

}


Item::~Item()
{
}

void Item::Update()
{

}

