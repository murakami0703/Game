#include "stdafx.h"
#include "Item.h"


Item::Item()
{
	//�A�C�e��
	{
		//0�ԁ��񕜖�
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

		//1�ԁ����e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

		//2�ԁ��U����UP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/title.dds", 100.0f, 100.0f);
		m_spriteRender.push_back(m_itemSprite);

		//3�ԁ��ړ����xUP
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

