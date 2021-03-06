#include "stdafx.h"
#include "ui/itemui/item/HpRecoveryUI.h"
#include "data/GameData.h"

HpRecoveryUI::HpRecoveryUI()
{
}


HpRecoveryUI::~HpRecoveryUI()
{
	g_goMgr->DeleteGameObject(m_itemSprite);
	g_goMgr->DeleteGameObject(hpRecovery);
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
	GameData* gamedata = GameData::GetInstance();
	gamedata->HPRecoveryCalc(-1);
	wchar_t text[MAX_PATH];
	swprintf(text, MAX_PATH - 1, L"%02d", gamedata->GetItemHpRecovery());
	itemContRender->SetText(text);

	//アイテム使用中フラグオン。
	gamedata->SetItemInUseFlag(true);

	hpRecovery = g_goMgr->NewGameObject<HpRecovery>();

}
void HpRecoveryUI::OnNowItem(FontRender* itemContRender)
{
	//選択されてるのアイテムの数を表示。
	GameData* gamedata = GameData::GetInstance();
	wchar_t text[MAX_PATH];
	swprintf(text, MAX_PATH - 1, L"%02d", gamedata->GetItemHpRecovery());
	itemContRender->SetText(text);
}

void HpRecoveryUI::ItemUseEnd()
{
	//アイテム使い終わりました。
	hpRecovery->SetState(HpRecovery::End_Use);
}
