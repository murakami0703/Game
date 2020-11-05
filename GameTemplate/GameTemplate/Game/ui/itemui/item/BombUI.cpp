#include "stdafx.h"
#include "ui/itemui/item/BombUI.h"
#include "data/GameData.h"

BombUI::BombUI()
{
}


BombUI::~BombUI()
{
	g_goMgr->DeleteGameObject(m_itemSprite);
	g_goMgr->DeleteGameObject(bomb);
}
bool BombUI::Start() 
{
	//爆弾
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/bomb.dds", 250.0f, 250.0f);
	m_itemSprite->SetPosition(NEXT1_ITEM_POSITION);
	m_itemSprite->SetScale(NEXT1_ITEM_SCALE);
	return true;
}
void BombUI::NowItemSelect()
{
	//選択中のアイテム。
	m_itemSprite->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
}
void BombUI::FirstItemSelect()
{
	//次1のアイテム。
	m_itemSprite->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
}
void BombUI::SecondItemSelect()
{
	//次2のアイテム。
	m_itemSprite->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
}

void BombUI::ThirdItemSelect()
{
	//次3のアイテム。
	m_itemSprite->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
}

void BombUI::UseItem(FontRender* itemContRender)
{
	//アイテム使用。
	GameData* gamedata = GameData::GetInstance();
	gamedata->BumCalc(-1);
	wchar_t text[256];
	swprintf(text, L"%02d", gamedata->GetItemBum());
	itemContRender->SetText(text);

	//アイテム使用中フラグオン。
	gamedata->SetItemInUseFlag(true);

	bomb = g_goMgr->NewGameObject<Bomb>();

}
void BombUI::OnNowItem(FontRender* itemContRender)
{
	//選択されてるのアイテムの数を表示。
	GameData* gamedata = GameData::GetInstance();
	wchar_t text[256];
	swprintf(text, L"%02d", gamedata->GetItemBum());
	itemContRender->SetText(text);
}

void BombUI::ItemUseEnd()
{
	//アイテム使い終わりました。
	bomb->SetState(Bomb::End_Use);
}
