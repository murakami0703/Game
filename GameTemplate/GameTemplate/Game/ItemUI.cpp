#include "stdafx.h"
#include "ItemUI.h"
#include "GameData.h"

//アイテム
#include "HpRecovery.h"
#include "Bum.h"
#include "AttackUp.h"
#include "SpeedUp.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////
 
///////////////////////
///sprite
const int HPRECOVERY = 0;				//回復薬。
const int BOMB = 1;						//爆弾。
const int ATTACKUPRECOVERY = 2;			//攻撃力Up薬。
const int SPEEDUPRECOVERY = 3;			//移動速度上昇薬。
///////////////////////

const CVector3 NOW_ITEM_SCALE = { 0.45f, 0.45f ,0.45f };			//選択中アイテムの拡大率
const CVector3 NEXT1_ITEM_SCALE = { 0.35f,0.35f ,0.35f };			//次1アイテムの拡大率
const CVector3 NEXT2_ITEM_SCALE = { 0.25f,0.25f ,0.25f };			//次2アイテムの拡大率
const CVector3 NEXT3_ITEM_SCALE = { 0.15f,0.15f ,0.15f };			//次3アイテムの拡大率

const CVector3 NOW_ITEM_POSITION = { 460.0f,-240.0f,0.0f };			//選択中アイテムの座標
const CVector3 NEXT1_ITEM_POSITION = { 560.0f,-120.0f,0.0f };		//次1アイテムの座標
const CVector3 NEXT2_ITEM_POSITION = { 475.0f,-50.0f,0.0f };		//次2アイテムの座標
const CVector3 NEXT3_ITEM_POSITION = { 545.0f,-3.0f,0.0f };			//次3アイテムの座標

const CVector3 ITEMFONT_SET_COLOR = { 0.3,0.25f,0.2f };					//アイテムフォントの色。
const CVector2 ITEMFONT_SET_POSITION = { 470.0f,-250.0f };				//アイテムフォントの座標。

ItemUI::ItemUI(){}
ItemUI::~ItemUI(){}

bool ItemUI::Start()
{

	//アイテムカウントフォントの設定。
	
		GameData* m_gamedate = GameData::GetInstance();
		m_itemCountFont = g_goMgr->NewGameObject<FontRender>();
		swprintf(ItemHpRecText, L"%02d", m_gamedate->GetItemHpRecovery());
		m_itemCountFont->SetText(ItemHpRecText);
		m_itemCountFont->SetColor(ITEMFONT_SET_COLOR);
		m_itemCountFont->SetPosition(ITEMFONT_SET_POSITION);
	
	return true;
}

void ItemUI::ItemUse(eItemState& m_State)
{
	GameData* m_gamedate = GameData::GetInstance();
	//アイテム使用
	switch (m_State) {
	case ItemUI::Item_HpRecovery:
	{
		m_gamedate->HPRecoveryCalc(-1);
		//使用後のアイテム数表示
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemHpRecovery());
		m_itemCountFont->SetText(text);

		//アイテム使用(回復薬)
		g_goMgr->NewGameObject<HpRecovery>();

		m_state = Item_InUse;
		break;
	}
	case ItemUI::Item_Bum:
	{
		m_gamedate->BumCalc(-1);
		//使用後のアイテム数表示
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemBum());
		m_itemCountFont->SetText(text);

		//アイテム使用(爆弾)
		g_goMgr->NewGameObject<Bum>();
		m_state = Item_InUse;
		break;
	}
	case ItemUI::Item_AttackUp:
	{
		m_gamedate->AttackUpCalc(-1);
		//使用後のアイテム数表示
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemAttackUp());
		m_itemCountFont->SetText(text);

		//アイテム使用(攻撃力Up)
		g_goMgr->NewGameObject<AttackUp>();

		m_state = Item_InUse;
		break;
	}
	case ItemUI::Item_SpeedUp:
	{
		m_gamedate->SpeedUpCalc(-1);
		//使用後のアイテム数表示
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemSpeedUp());
		m_itemCountFont->SetText(text);

		//アイテム使用(移動速度Up)
		SpeedUp* m_spedup = g_goMgr->NewGameObject<SpeedUp>();
		m_state = Item_InUse;
		break;
	}
	}

}

void ItemUI::ItemMoveSet(eItemState& m_State)
{
	GameData* m_gamedate = GameData::GetInstance();
	
	
	//アイテムspriteの移動拡大設定。
	if (m_State == Item_HpRecovery) {
		m_spriteRender[0]->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
		m_spriteRender[1]->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
		m_spriteRender[2]->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
		m_spriteRender[3]->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);

		//回復薬のアイテム数
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemHpRecovery());
		m_itemCountFont->SetText(text);

		m_itemMoveEndFlag = true;

	}
	else if (m_State == Item_Bum)
	{
		m_spriteRender[0]->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
		m_spriteRender[1]->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
		m_spriteRender[2]->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
		m_spriteRender[3]->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);

		//爆弾のアイテム数
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemBum());
		m_itemCountFont->SetText(text);

		m_itemMoveEndFlag = true;

	}
	else if (m_State == Item_AttackUp)
	{
		m_spriteRender[0]->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
		m_spriteRender[1]->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
		m_spriteRender[2]->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
		m_spriteRender[3]->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);

		//攻撃力UPのアイテム数
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemAttackUp());
		m_itemCountFont->SetText(text);

		m_itemMoveEndFlag = true;

	}
	else if (m_State == Item_SpeedUp)
	{
		m_spriteRender[0]->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
		m_spriteRender[1]->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
		m_spriteRender[2]->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
		m_spriteRender[3]->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);

		//移動速度UPのアイテム数
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemSpeedUp());
		m_itemCountFont->SetText(text);

		m_itemMoveEndFlag = true;
	}
}
void ItemUI::ItemMove(eItemState& m_State)
{
	//アイテム選択
	//押されたボタンでそのアイテムを選択状態に。
	switch (m_State) {
	case ItemUI::Item_HpRecovery:
	{
		if (m_upDounFlag == true) {
			//上　爆弾。
			m_itemState = Item_Bum;
		}
		else {
			//下　移動速度UP。
			m_itemState = Item_SpeedUp;
		}
		//spriteの位置拡大の設定。
		ItemMoveSet(m_State);
		//準備できたので選択状態に遷移。
		if (m_itemMoveEndFlag == true) {
			m_itemMoveEndFlag = false;
			m_state = Item_Now;
		}
		break;
	}
	case ItemUI::Item_Bum:
	{
		if (m_upDounFlag == true) {
			//上　攻撃力UP。
			m_itemState = Item_AttackUp;
		}
		else {
			//下　回復薬。
			m_itemState = Item_HpRecovery;
		}
		//spriteの位置拡大の設定。
		ItemMoveSet(m_State);
		//準備できたので選択状態に遷移。
		if (m_itemMoveEndFlag == true) {
			m_itemMoveEndFlag = false;
			m_state = Item_Now;
		}
		break;
	}
	case ItemUI::Item_AttackUp:
	{
		if (m_upDounFlag == true) {
			//上　移動速度UP。
			m_itemState = Item_SpeedUp;
		}
		else {
			//下　爆弾。
			m_itemState = Item_Bum;
		}
		//spriteの位置拡大の設定。
		ItemMoveSet(m_State);
		//準備できたので選択状態に遷移。
		if (m_itemMoveEndFlag == true) {
			m_itemMoveEndFlag = false;
			m_state = Item_Now;
		}
		break;
	}
	case ItemUI::Item_SpeedUp:
	{
		if (m_upDounFlag == true) {
			//上　回復薬。
			m_itemState = Item_HpRecovery;
		}
		else {
			//下　攻撃力UP。
			m_itemState = Item_AttackUp;

		}
		//spriteの位置拡大の設定。
		ItemMoveSet(m_State);
		//準備できたので選択状態に遷移。
		if (m_itemMoveEndFlag == true) {
			m_itemMoveEndFlag = false;
			m_state = Item_Now;
		}
		break;
	}
	}
}
void ItemUI::ItemNow()
{
	//現在選択されているアイテム
	if (g_pad[0].IsTrigger(enButtonY)) {
		//Yボタンが押されたらアイテム使用状態に遷移
		m_state = Item_Use;
	}

	//LB1またはLB2ボタンが押されたらアイテム移動状態に遷移
	if (g_pad[0].IsTrigger(enButtonRB1)) {
		m_upDounFlag = true;		//上
		m_state = Item_Move;
	}
	else if (g_pad[0].IsTrigger(enButtonLB1))
	{
		m_upDounFlag = false;		//下
		m_state = Item_Move;
	}
}
void ItemUI::ItemInUse()
{
	//アイテム使用中。
	//各アイテムによってラグを設ける。

	if (m_itemState == Item_HpRecovery) {
	}
	else if (m_itemState == Item_Bum){

	}
	else if (m_itemState == Item_AttackUp){
	}
	else if (m_itemState == Item_SpeedUp){

	}

}

void ItemUI::Update()
{
	switch (m_state)
	{
	case ItemUI::Item_Use:
		ItemUse(m_itemState);
		break;
	case ItemUI::Item_Move:
		ItemMove(m_itemState);
		break;
	case ItemUI::Item_Now:
		ItemNow();
		break;
	case ItemUI::Item_InUse:
		ItemInUse();
		break;

	}
}

