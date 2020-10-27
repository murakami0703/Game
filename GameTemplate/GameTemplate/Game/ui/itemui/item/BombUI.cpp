#include "stdafx.h"
#include "ui/itemui/item/BombUI.h"
#include "data/GameData.h"

#include "item/Bum.h"

BombUI::BombUI()
{
}


BombUI::~BombUI()
{
}
bool BombUI::Start() 
{
	//���e
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/bomb.dds", 250.0f, 250.0f);
	m_itemSprite->SetPosition(NEXT1_ITEM_POSITION);
	m_itemSprite->SetScale(NEXT1_ITEM_SCALE);
	return true;
}
void BombUI::NowItemSelect()
{
	//�I�𒆂̃A�C�e���B
	m_itemSprite->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
}
void BombUI::FirstItemSelect()
{
	//��1�̃A�C�e���B
	m_itemSprite->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
}
void BombUI::SecondItemSelect()
{
	//��2�̃A�C�e���B
	m_itemSprite->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
}

void BombUI::ThirdItemSelect()
{
	//��3�̃A�C�e���B
	m_itemSprite->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
}

void BombUI::UseItem(FontRender* itemContRender)
{
	//�A�C�e���g�p�B
	GameData* gamedate = GameData::GetInstance();
	gamedate->BumCalc(-1);
	wchar_t text[256];
	swprintf(text, L"%02d", gamedate->GetItemBum());
	itemContRender->SetText(text);
	g_goMgr->NewGameObject<Bum>();

}
void BombUI::OnNowItem(FontRender* itemContRender)
{
	//�I������Ă�̃A�C�e���̐���\���B
	GameData* gamedate = GameData::GetInstance();
	wchar_t text[256];
	swprintf(text, L"%02d", gamedate->GetItemBum());
	itemContRender->SetText(text);
}