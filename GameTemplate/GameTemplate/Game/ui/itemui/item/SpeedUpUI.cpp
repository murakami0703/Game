#include "stdafx.h"
#include "ui/itemui/item/SpeedUpUI.h"
#include "data/GameData.h"

SpeedUpUI::SpeedUpUI()
{
}


SpeedUpUI::~SpeedUpUI()
{
	g_goMgr->DeleteGameObject(m_itemSprite);
	g_goMgr->DeleteGameObject(speedUp);
}

bool SpeedUpUI::Start() {

	//移動速度UP
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/speedUpRecovery.dds", 150.0f, 300.0f);
	m_itemSprite->SetPosition(NEXT3_ITEM_POSITION);
	m_itemSprite->SetScale(NEXT3_ITEM_SCALE);
	return true;
}

void SpeedUpUI::NowItemSelect()
{
	//選択中のアイテム。
	m_itemSprite->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);

}
void SpeedUpUI::FirstItemSelect()
{
	//次1のアイテム。
	m_itemSprite->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
}
void SpeedUpUI::SecondItemSelect()
{
	//次2のアイテム。
	m_itemSprite->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
}

void SpeedUpUI::ThirdItemSelect()
{
	//次3のアイテム。
	m_itemSprite->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
}

void SpeedUpUI::UseItem(FontRender* itemContRender)
{
	//アイテム使用。
	GameData* gamedata = GameData::GetInstance();
	gamedata->SpeedUpCalc(-1);
	wchar_t text[256];
	swprintf(text, L"%02d", gamedata->GetItemSpeedUp());
	itemContRender->SetText(text);

	//アイテム使用中フラグオン。
	gamedata->SetItemInUseFlag(true);

	speedUp = g_goMgr->NewGameObject<SpeedUp>();

}
void SpeedUpUI::OnNowItem(FontRender* itemContRender)
{
	//選択されてるのアイテムの数を表示。
	GameData* gamedata = GameData::GetInstance();
	wchar_t text[256];
	swprintf(text, L"%02d", gamedata->GetItemSpeedUp());
	itemContRender->SetText(text);
}

void SpeedUpUI::ItemUseEnd()
{
	//アイテム使い終わりました。
	speedUp->SetState(SpeedUp::End_Use);
}
