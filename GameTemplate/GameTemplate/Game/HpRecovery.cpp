#include "stdafx.h"
#include "HpRecovery.h"
#include "Player.h"
#include "GameData.h"


HpRecovery::HpRecovery()
{
}


HpRecovery::~HpRecovery()
{
}

bool HpRecovery::Start()
{
	//0番→回復薬
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/HpRecovery.dds", 250.0f, 250.0f);
	m_itemSprite->SetPosition(NOW_ITEM_POSITION);
	m_itemSprite->SetScale(NOW_ITEM_SCALE);

	m_number = 0;			//アイテム位置番号（選択中）
	return true;
}

void HpRecovery::InUse()
{
	//使用中。
	if (GameData::GetInstance()->GetItemInUseFlag() != false) {
		//HPを+１する。
		GameData::GetInstance()->HPCalc(1.0f);
		GameData::GetInstance()->SetItemInUseFlag(false);
	}
}
void HpRecovery::EndUse()
{
	//終わり。
}
