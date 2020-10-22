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
 
const CVector3 ITEMFONT_SET_COLOR = { 0.3,0.2f,0.2f };					//�A�C�e���t�H���g�̐F�B
const CVector2 ITEMFONT_SET_POSITION = { 470.0f,-250.0f };				//�A�C�e���t�H���g�̍��W�B

const int  SELECTITEM_ADD_VALUE = 1;									//�I������A�C�e�����Z�o����Ƃ��ɉ��Z����l�B

ItemUI::ItemUI(){}
ItemUI::~ItemUI()
{
	//�����B
	for (int itemNo = 0; itemNo < static_cast<int>(eItemState::Item_Num); itemNo++) {
		g_goMgr->DeleteGameObject(m_uiItems[itemNo]);
	}
}

bool ItemUI::Start()
{	
	//�e�A�C�e��UI�B
	m_uiItems[Item_HpRecovery] = g_goMgr->NewGameObject<HpRecoveryUI>();
	m_uiItems[Item_Bum] = g_goMgr->NewGameObject<BombUI>();
	m_uiItems[Item_AttackUp] = g_goMgr->NewGameObject<AttackUpUI>();
	m_uiItems[Item_SpeedUp] = g_goMgr->NewGameObject<SpeedUpUI>();

	//�A�C�e���������̕\���B
	GameData* m_gamedate = GameData::GetInstance();
	wchar_t text[MAX_PATH];
	//���̃t�H���g�͕K��2D����ŕ`�悵�Ăق����̂ŁA���s�D�揇�ʂ�Ⴍ����B
	m_itemCountFont = g_goMgr->NewGameObject<FontRender>(GameObjectPrio_Low);
	swprintf(text, MAX_PATH - 1, L"%02d", m_gamedate->GetItemHpRecovery());
	m_itemCountFont->SetText(text);
	m_itemCountFont->SetColor(ITEMFONT_SET_COLOR);
	m_itemCountFont->SetPosition(ITEMFONT_SET_POSITION);

	return true;
}

void ItemUI::ItemUse(const eItemState& m_State)
{
	//�A�C�e���g�p�B
	m_uiItems[m_itemState]->UseItem(m_itemCountFont);
	m_state = Item_Now;
}
void ItemUI::ItemMove()
{
	//�A�C�e���I��
	GameData* m_gamedate = GameData::GetInstance();
	//���݂̃A�C�e�����X�V�B
	for (int i = 0; i < static_cast<int>(ItemUIBase::Item_Select_Num); i++){
		int itemNo = (m_itemState + i) % static_cast<int>(ItemUIBase::Item_Select_Num);
		m_uiItems[itemNo]->SetState(static_cast<ItemUIBase::eSelectState>(i));
	}
	//�I�𒆂̃A�C�e�����̕\���B
	m_uiItems[m_itemState]->OnNowItem(m_itemCountFont);
	m_state = Item_Now;
}
void ItemUI::ItemNow()
{
	//���ݑI������Ă���A�C�e���B
	if (g_pad[0].IsTrigger(enButtonY)) {
		//Y�{�^���������ꂽ��A�C�e���g�p��ԂɑJ�ځB
		m_state = Item_Use;
	}

	//LB1�܂���LB2�{�^���������ꂽ��A�C�e���ړ���ԂɑJ�ځB
	if (g_pad[0].IsTrigger(enButtonRB1)) {
		//�E����ɑI���B
		int itemSelectNo = static_cast<eItemState>(m_itemState + SELECTITEM_ADD_VALUE) % static_cast<int>(eItemState::Item_Num);
		m_itemState = static_cast<eItemState>(itemSelectNo);
		m_state = Item_Move;
	}
	else if (g_pad[0].IsTrigger(enButtonLB1))
	{
		//�����ɑI���B
		if (m_itemState > 0) {
			int itemSelectNo = static_cast<eItemState>(m_itemState - SELECTITEM_ADD_VALUE) % static_cast<int>(eItemState::Item_Num);
			m_itemState = static_cast<eItemState>(itemSelectNo);
		}
		else {
			//��Ԍ��̃A�C�e����I��
			int itemSelectNo = static_cast<int>(eItemState::Item_Num - SELECTITEM_ADD_VALUE);
			m_itemState = static_cast<eItemState>(itemSelectNo);

		}
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

