#include "stdafx.h"
#include "HpRecoveryUI.h"
#include "GameData.h"

#include "HpRecovery.h"

HpRecoveryUI::HpRecoveryUI()
{
}


HpRecoveryUI::~HpRecoveryUI()
{
}
bool HpRecoveryUI::Start() {

	//0番→回復薬
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/HpRecovery.dds", 250.0f, 250.0f);
	m_itemSprite->SetPosition(NOW_ITEM_POSITION);
	m_itemSprite->SetScale(NOW_ITEM_SCALE);
	return true;
}
void HpRecoveryUI::NowItemSelect()
{
	//選択中のアイテム。
	m_itemSprite->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
}
void HpRecoveryUI::FirstItemSelect()
{
	//次1のアイテム。
	m_itemSprite->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
}
void HpRecoveryUI::SecondItemSelect()
{
	//次2のアイテム。
	m_itemSprite->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
}

void HpRecoveryUI::ThirdItemSelect()
{
	//次3のアイテム。
	m_itemSprite->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
}

void HpRecoveryUI::UseItem(FontRender* itemContRender)
{
	//アイテム使用。
	GameData* gamedate = GameData::GetInstance();
	gamedate->HPRecoveryCalc(-1);
	wchar_t text[256];
	swprintf(text, L"%02d", gamedate->GetItemHpRecovery());
	itemContRender->SetText(text);

	HpRecovery* m_hpRecovery = g_goMgr->NewGameObject<HpRecovery>();

}
void HpRecoveryUI::OnNowItem(FontRender* itemContRender)
{
	//選択されてるのアイテムの数を表示。
	GameData* gamedate = GameData::GetInstance();
	wchar_t text[256];
	swprintf(text, L"%02d", gamedate->GetItemHpRecovery());
	itemContRender->SetText(text);
}