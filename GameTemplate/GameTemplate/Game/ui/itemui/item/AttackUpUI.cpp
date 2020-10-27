#include "stdafx.h"
#include "ui/itemui/item/AttackUpUI.h"
#include "data/GameData.h"

#include "item/AttackUp.h"

AttackUpUI::AttackUpUI()
{
}


AttackUpUI::~AttackUpUI()
{
}
bool AttackUpUI::Start() 
{
	//�U����UP
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/attackUpRecovery.dds", 150.0f, 300.0f);
	m_itemSprite->SetPosition(NEXT2_ITEM_POSITION);
	m_itemSprite->SetScale(NEXT2_ITEM_SCALE);

	return true;
}
void AttackUpUI::NowItemSelect()
{
	//�I�𒆂̃A�C�e���B
	m_itemSprite->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
}
void AttackUpUI::FirstItemSelect()
{
	//��1�̃A�C�e���B
	m_itemSprite->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
}
void AttackUpUI::SecondItemSelect()
{
	//��2�̃A�C�e���B
	m_itemSprite->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
}

void AttackUpUI::ThirdItemSelect()
{
	//��3�̃A�C�e���B
	m_itemSprite->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
}


void AttackUpUI::UseItem(FontRender* itemContRender)
{
	//�A�C�e���g�p�B
	GameData* gamedate = GameData::GetInstance();
	gamedate->AttackUpCalc(-1);
	wchar_t text[256];
	swprintf(text, L"%02d", gamedate->GetItemAttackUp());
	itemContRender->SetText(text);

	attackUp = g_goMgr->NewGameObject<AttackUp>();

}

void AttackUpUI::ItemUseEnd() 
{
	attackUp->SetState(AttackUp::End_Use);
}
void AttackUpUI::OnNowItem(FontRender* itemContRender)
{
	//�I������Ă�̃A�C�e���̐���\���B
	GameData* gamedate = GameData::GetInstance();
	wchar_t text[256];
	swprintf(text, L"%02d", gamedate->GetItemAttackUp());
	itemContRender->SetText(text);
}