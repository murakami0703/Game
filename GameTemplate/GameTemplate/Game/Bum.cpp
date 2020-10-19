#include "stdafx.h"
#include "Bum.h"
#include "Player.h"


Bum::Bum()
{
}


Bum::~Bum()
{
}
bool Bum::Start()
{

	//爆弾
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/bomb.dds", 250.0f, 250.0f);
	m_itemSprite->SetPosition(NEXT1_ITEM_POSITION);
	m_itemSprite->SetScale(NEXT1_ITEM_SCALE);

	//スキンモデル。
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/box.cmo");
	m_position = Player::GetInstance()->GetPosition();
	m_position.y += 200.0f;
	m_skinModelRender->SetPosition(m_position);

	m_number = 1;			//アイテム位置番号（選択中）

	return true;
}

void Bum::InUse()
{
	//使用中。
}
void Bum::EndUse()
{
	//終わり。
}
