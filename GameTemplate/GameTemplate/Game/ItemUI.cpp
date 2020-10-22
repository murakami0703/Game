#include "stdafx.h"
#include "ItemUI.h"
#include "GameData.h"

//アイテム

#include "HpRecovery.h"
#include "bum.h"
#include "AttackUp.h"
#include "SpeedUp.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////
 
const CVector3 ITEMFONT_SET_COLOR = { 0.3,0.2f,0.2f };					//アイテムフォントの色。
const CVector2 ITEMFONT_SET_POSITION = { 470.0f,-250.0f };				//アイテムフォントの座標。

const int  SELECTITEM_ADD_VALUE = 1;									//選択するアイテムを算出するときに加算する値。

ItemUI::ItemUI(){}
ItemUI::~ItemUI()
{
	//消す。
	for (int itemNo = 0; itemNo < static_cast<int>(eItemState::Item_Num); itemNo++) {
		g_goMgr->DeleteGameObject(m_uiItems[itemNo]);
	}
}

bool ItemUI::Start()
{	
	//各アイテムUI。
	m_uiItems[Item_HpRecovery] = g_goMgr->NewGameObject<HpRecoveryUI>();
	m_uiItems[Item_Bum] = g_goMgr->NewGameObject<BombUI>();
	m_uiItems[Item_AttackUp] = g_goMgr->NewGameObject<AttackUpUI>();
	m_uiItems[Item_SpeedUp] = g_goMgr->NewGameObject<SpeedUpUI>();

	//アイテム所持数の表示。
	GameData* m_gamedate = GameData::GetInstance();
	wchar_t text[MAX_PATH];
	//このフォントは必ず2Dより後で描画してほしいので、実行優先順位を低くする。
	m_itemCountFont = g_goMgr->NewGameObject<FontRender>(GameObjectPrio_Low);
	swprintf(text, MAX_PATH - 1, L"%02d", m_gamedate->GetItemHpRecovery());
	m_itemCountFont->SetText(text);
	m_itemCountFont->SetColor(ITEMFONT_SET_COLOR);
	m_itemCountFont->SetPosition(ITEMFONT_SET_POSITION);

	return true;
}

void ItemUI::ItemUse(const eItemState& m_State)
{
	//アイテム使用。
	m_uiItems[m_itemState]->UseItem(m_itemCountFont);
	m_state = Item_Now;
}
void ItemUI::ItemMove()
{
	//アイテム選択
	GameData* m_gamedate = GameData::GetInstance();
	//現在のアイテムを更新。
	for (int i = 0; i < static_cast<int>(ItemUIBase::Item_Select_Num); i++){
		int itemNo = (m_itemState + i) % static_cast<int>(ItemUIBase::Item_Select_Num);
		m_uiItems[itemNo]->SetState(static_cast<ItemUIBase::eSelectState>(i));
	}
	//選択中のアイテム数の表示。
	m_uiItems[m_itemState]->OnNowItem(m_itemCountFont);
	m_state = Item_Now;
}
void ItemUI::ItemNow()
{
	//現在選択されているアイテム。
	if (g_pad[0].IsTrigger(enButtonY)) {
		//Yボタンが押されたらアイテム使用状態に遷移。
		m_state = Item_Use;
	}

	//LB1またはLB2ボタンが押されたらアイテム移動状態に遷移。
	if (g_pad[0].IsTrigger(enButtonRB1)) {
		//右周りに選択。
		int itemSelectNo = static_cast<eItemState>(m_itemState + SELECTITEM_ADD_VALUE) % static_cast<int>(eItemState::Item_Num);
		m_itemState = static_cast<eItemState>(itemSelectNo);
		m_state = Item_Move;
	}
	else if (g_pad[0].IsTrigger(enButtonLB1))
	{
		//左回りに選択。
		if (m_itemState > 0) {
			int itemSelectNo = static_cast<eItemState>(m_itemState - SELECTITEM_ADD_VALUE) % static_cast<int>(eItemState::Item_Num);
			m_itemState = static_cast<eItemState>(itemSelectNo);
		}
		else {
			//一番後ろのアイテムを選択
			int itemSelectNo = static_cast<int>(eItemState::Item_Num - SELECTITEM_ADD_VALUE);
			m_itemState = static_cast<eItemState>(itemSelectNo);

		}
		m_state = Item_Move;
	}
}
void ItemUI::ItemInUse()
{
	//アイテム使用中。
	//各アイテムによってラグを設ける。

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

