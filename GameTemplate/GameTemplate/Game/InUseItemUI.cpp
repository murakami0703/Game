#include "stdafx.h"
#include "InUseItemUI.h"


InUseItemUI::InUseItemUI()
{
}


InUseItemUI::~InUseItemUI()
{
}

bool InUseItemUI::Start()
{
	//0”Ô¨˜g
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 250.0f, 250.0f);
	//m_itemSprite->SetAlpha(m_backTexAlpha);
	m_spriteRender.push_back(m_itemSprite);
	//ƒAƒCƒeƒ€
	{
		//1”Ô¨HP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 250.0f, 250.0f);
		//m_itemSprite->SetPosition({ m_backTexXPos,0.0f,0.0f });
		//m_itemSprite->SetAlpha(m_backTexAlpha);
		m_spriteRender.push_back(m_itemSprite);
		//2”Ô¨AttackUp
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 250.0f, 250.0f);
		//m_itemSprite->SetPosition({ m_backTexXPos,0.0f,0.0f });
		//m_itemSprite->SetAlpha(m_backTexAlpha);
		m_spriteRender.push_back(m_itemSprite);
		//3”Ô¨SpeedUp
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/Result_Backgraund.dds", 250.0f, 250.0f);
		//m_itemSprite->SetPosition({ m_backTexXPos,0.0f,0.0f });
		//m_itemSprite->SetAlpha(m_backTexAlpha);
		m_spriteRender.push_back(m_itemSprite);
	}

	return true;
}

void InUseItemUI::Update()
{

}