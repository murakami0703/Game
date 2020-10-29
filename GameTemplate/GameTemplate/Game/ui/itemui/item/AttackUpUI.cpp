#include "stdafx.h"
#include "ui/itemui/item/AttackUpUI.h"
#include "data/GameData.h"

AttackUpUI::AttackUpUI(){}
AttackUpUI::~AttackUpUI()
{
	g_goMgr->DeleteGameObject(m_itemSprite);
	g_goMgr->DeleteGameObject(attackUp);
}

bool AttackUpUI::Start() 
{
	//攻撃力UP
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/attackUpRecovery.dds", 150.0f, 300.0f);
	m_itemSprite->SetPosition(NEXT2_ITEM_POSITION);
	m_itemSprite->SetScale(NEXT2_ITEM_SCALE);

	return true;
}
void AttackUpUI::NowItemSelect()
{
	//選択中のアイテム。
	m_itemSprite->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
}
void AttackUpUI::FirstItemSelect()
{
	//次1のアイテム。
	m_itemSprite->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
}
void AttackUpUI::SecondItemSelect()
{
	//次2のアイテム。
	m_itemSprite->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
}

void AttackUpUI::ThirdItemSelect()
{
	//次3のアイテム。
	m_itemSprite->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
}


void AttackUpUI::UseItem(FontRender* itemContRender)
{
	//アイテム使用。
	GameData* gamedata = GameData::GetInstance();
	gamedata->AttackUpCalc(-1);
	wchar_t text[256];
	swprintf(text, L"%02d", gamedata->GetItemAttackUp());
	itemContRender->SetText(text);

	//アイテム使用中フラグオン。
	gamedata->SetItemInUseFlag(true);

	attackUp = g_goMgr->NewGameObject<AttackUp>();

}

void AttackUpUI::OnNowItem(FontRender* itemContRender)
{
	//選択されてるのアイテムの数を表示。
	GameData* gamedata = GameData::GetInstance();
	wchar_t text[256];
	swprintf(text, L"%02d", gamedata->GetItemAttackUp());
	itemContRender->SetText(text);
}

void AttackUpUI::ItemUseEnd()
{
	//アイテム使い終わりました。
	attackUp->SetState(AttackUp::End_Use);
}
