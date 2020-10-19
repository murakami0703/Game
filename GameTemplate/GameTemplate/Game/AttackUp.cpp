#include "stdafx.h"
#include "AttackUp.h"
#include "Player.h"
#include "EffectManager.h"


AttackUp::AttackUp()
{
}


AttackUp::~AttackUp()
{
}

bool AttackUp::Start()
{
	//攻撃力UP
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/attackUpRecovery.dds", 150.0f, 300.0f);
	m_itemSprite->SetPosition(NEXT2_ITEM_POSITION);
	m_itemSprite->SetScale(NEXT2_ITEM_SCALE);

	m_number = 1;			//アイテム位置番号（選択中）

	return true;
}

void AttackUp::InUse()
{
	//使用中。
}
void AttackUp::EndUse()
{
	//終わり。
}
