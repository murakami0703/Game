#include "stdafx.h"
#include "Item.h"


Item::Item()
{
	//ACe
	{
		//0Ô¨ñò
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

		//1Ô¨e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

		//2Ô¨UÍUP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

		//3Ô¨Ú®¬xUP
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

