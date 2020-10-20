#include "stdafx.h"
#include "ItemUI.h"
#include "GameData.h"

//�A�C�e��

#include "HpRecovery.h"
#include "bum.h"
#include "AttackUp.h"
#include "SpeedUp.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////
 
const CVector3 ITEMFONT_SET_COLOR = { 0.3,0.25f,0.2f };					//�A�C�e���t�H���g�̐F�B
const CVector2 ITEMFONT_SET_POSITION = { 470.0f,-250.0f };				//�A�C�e���t�H���g�̍��W�B

ItemUI::ItemUI(){}
ItemUI::~ItemUI(){}

bool ItemUI::Start()
{	
	m_uiItems[Item_HpRecovery] = g_goMgr->NewGameObject<HpRecoveryUI>();
	m_uiItems[Item_Bum] = g_goMgr->NewGameObject<BombUI>();
	m_uiItems[Item_AttackUp] = g_goMgr->NewGameObject<AttackUpUI>();
	m_uiItems[Item_SpeedUp] = g_goMgr->NewGameObject<SpeedUpUI>();

	//�A�C�e���������̕\���B
	GameData* m_gamedate = GameData::GetInstance();
	wchar_t text[256];
	m_itemCountFont = g_goMgr->NewGameObject<FontRender>();
	swprintf(text, L"%02d", m_gamedate->GetItemHpRecovery());
	m_itemCountFont->SetText(text);
	m_itemCountFont->SetColor(ITEMFONT_SET_COLOR);
	m_itemCountFont->SetPosition(ITEMFONT_SET_POSITION);

	return true;
}

void ItemUI::ItemUse(eItemState& m_State)
{
	GameData* m_gamedate = GameData::GetInstance();
	//�A�C�e���g�p
	switch (m_State) {
	case ItemUI::Item_HpRecovery:
	{
		m_gamedate->HPRecoveryCalc(-1);
		//�g�p��̃A�C�e�����\��
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemHpRecovery());
		//m_itemCountFont->SetText(text);

		//�A�C�e���g�p(�񕜖�)
		g_goMgr->NewGameObject<HpRecovery>();

		m_state = Item_InUse;
		break;
	}
	case ItemUI::Item_Bum:
	{
		m_gamedate->BumCalc(-1);
		//�g�p��̃A�C�e�����\��
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemBum());
		//m_itemCountFont->SetText(text);

		//�A�C�e���g�p(���e)
		g_goMgr->NewGameObject<Bum>();

		m_state = Item_InUse;
		break;
	}
	case ItemUI::Item_AttackUp:
	{
		m_gamedate->AttackUpCalc(-1);
		//�g�p��̃A�C�e�����\��
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemAttackUp());
		//m_itemCountFont->SetText(text);

		//�A�C�e���g�p(�U����Up)
		g_goMgr->NewGameObject<AttackUp>();

		m_state = Item_InUse;
		break;
	}
	case ItemUI::Item_SpeedUp:
	{
		m_gamedate->SpeedUpCalc(-1);
		//�g�p��̃A�C�e�����\��
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemSpeedUp());
		//m_itemCountFont->SetText(text);

		//�A�C�e���g�p(�ړ����xUp)
		SpeedUp* m_spedup = g_goMgr->NewGameObject<SpeedUp>();
		m_state = Item_InUse;
		break;
	}
	}

}

void ItemUI::ItemMove()
{
	//�A�C�e���I��
	GameData* m_gamedate = GameData::GetInstance();
	//���݂̃A�C�e�����X�V�B
	for (int i = 0; i < static_cast<int>(ItemUIBase::Third_Item_Select); i++){
		int itemNo = (m_itemState + i) % static_cast<int>(ItemUIBase::Third_Item_Select);
		m_uiItems[itemNo]->SetState(static_cast<ItemUIBase::eSelectState>(i));
	}

	m_uiItems[m_itemState]->OnNowItem(m_itemCountFont);
	m_state = Item_Now;
}
void ItemUI::ItemNow()
{
	//���ݑI������Ă���A�C�e��
	if (g_pad[0].IsTrigger(enButtonY)) {
		//Y�{�^���������ꂽ��A�C�e���g�p��ԂɑJ��
		m_state = Item_Use;
	}

	//LB1�܂���LB2�{�^���������ꂽ��A�C�e���ړ���ԂɑJ��
	if (g_pad[0].IsTrigger(enButtonRB1)) {
		m_upDounFlag = true;		//��
		int itemNo = static_cast<eItemState>(m_itemState + 1) % static_cast<int>(eItemState::Item_Num);
		m_itemState = static_cast<eItemState>(itemNo);
		m_state = Item_Move;
	}
	else if (g_pad[0].IsTrigger(enButtonLB1))
	{
		m_upDounFlag = false;		//��
		//m_itemState = static_cast<eItemState>(m_itemState - 1);
		m_state = Item_Move;
	}
}
void ItemUI::ItemInUse()
{
	//�A�C�e���g�p���B
	//�e�A�C�e���ɂ���ă��O��݂���B

}

void ItemUI::Update()
{
	switch (m_state)
	{
	case ItemUI::Item_Use:
		ItemUse(m_itemState);
		break;
	case ItemUI::Item_Move:
		ItemMove();
		break;
	case ItemUI::Item_Now:
		ItemNow();
		break;
	case ItemUI::Item_InUse:
		ItemInUse();
		break;

	}
}

