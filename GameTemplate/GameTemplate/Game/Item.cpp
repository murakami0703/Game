#include "stdafx.h"
#include "Item.h"
#include "GameData.h"

Item::Item()
{
	//アイテム
	{
		//0番→回復薬
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/spe.dds", 250.0f, 250.0f);
		m_itemSprite->SetPosition(m_item1Pos);
		m_itemSprite->SetScale({ 0.55f,0.55f ,0.55f });
		m_spriteRender.push_back(m_itemSprite);

		//1番→爆弾
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/test.dds", 250.0f, 250.0f);
		m_itemSprite->SetPosition(m_item2Pos);
		m_itemSprite->SetScale({ 0.35f,0.35f ,0.35f });
		m_spriteRender.push_back(m_itemSprite);

		//2番→攻撃力UP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/1.dds", 250.0f, 250.0f);
		m_itemSprite->SetPosition(m_item3Pos);
		m_itemSprite->SetScale({ 0.25f,0.25f ,0.25f });
		m_spriteRender.push_back(m_itemSprite);

		//3番→移動速度UP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/2.dds", 250.0f, 250.0f);
		m_itemSprite->SetPosition(m_item4Pos);
		m_itemSprite->SetScale({ 0.15f,0.15f ,0.15f });
		m_spriteRender.push_back(m_itemSprite);
		
	}
	//アイテムカウントフォントの設定。
	GameData* m_gamedate = GameData::GetInstance();
	m_itemCountFont = g_goMgr->NewGameObject<FontRender>();
	swprintf(ItemHpRecText, L"%02d", m_gamedate->GetItemHpRecovery());
	m_itemCountFont->SetText(ItemHpRecText);	
	m_itemCountFont->SetColor({0.5f,0.4f,0.0f});
	m_itemCountFont->SetPosition({ 480.0f,-240.0f});

}

Item::~Item()
{
}
void Item::ItemGet()
{
	//アイテム取得
	//fontアイテム加算
}
void Item::ItemUse(eItemState& m_State)
{		
	//アイテム使用
	switch (m_State) {
	case Item::Item_HpRecovery:
	{
		break;
	}
	case Item::Item_Bum:
	{
		break;
	}
	case Item::Item_AttackUp:
	{
		break;
	}
	case Item::Item_SpeedUp:
	{
		break;
	}
	}

}
void Item::ItemMoveSet(eItemState& m_State)
{
	//アイテムspriteの移動拡大設定。
	if (m_State == Item_HpRecovery) {
		m_spriteRender[0]->SetPosScale(m_item1Pos, m_item1Scale);
		m_spriteRender[1]->SetPosScale(m_item2Pos, m_item2Scale);
		m_spriteRender[2]->SetPosScale(m_item3Pos, m_item3Scale);
		m_spriteRender[3]->SetPosScale(m_item4Pos, m_item4Scale);
		m_itemMoveEndFlag = true;

	}
	else if (m_State == Item_Bum)
	{
		m_spriteRender[0]->SetPosScale(m_item4Pos, m_item4Scale);
		m_spriteRender[1]->SetPosScale(m_item1Pos, m_item1Scale);
		m_spriteRender[2]->SetPosScale(m_item2Pos, m_item2Scale);
		m_spriteRender[3]->SetPosScale(m_item3Pos, m_item3Scale);
		m_itemMoveEndFlag = true;

	}
	else if (m_State == Item_AttackUp)
	{
		m_spriteRender[0]->SetPosScale(m_item3Pos, m_item3Scale);
		m_spriteRender[1]->SetPosScale(m_item4Pos, m_item4Scale);
		m_spriteRender[2]->SetPosScale(m_item1Pos, m_item1Scale);
		m_spriteRender[3]->SetPosScale(m_item2Pos, m_item2Scale);
		m_itemMoveEndFlag = true;

	}
	else if (m_State == Item_SpeedUp)
	{
		m_spriteRender[0]->SetPosScale(m_item2Pos, m_item2Scale);
		m_spriteRender[1]->SetPosScale(m_item3Pos, m_item3Scale);
		m_spriteRender[2]->SetPosScale(m_item4Pos, m_item4Scale);
		m_spriteRender[3]->SetPosScale(m_item1Pos, m_item1Scale);
		m_itemMoveEndFlag = true;
	}
}
void Item::ItemMove(eItemState& m_State)
{	
	//アイテム選択
	//押されたボタンでそのアイテムを選択状態に。
	switch (m_State){
	case Item::Item_HpRecovery:
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
	case Item::Item_Bum:
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
	case Item::Item_AttackUp:
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
	case Item::Item_SpeedUp:
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
void Item::ItemNow()
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


void Item::Update()
{
	switch (m_state)
	{
	case Item::Item_Get:
		ItemGet();
		break;
	case Item::Item_Use:
		ItemUse(m_itemState);
		break;
	case Item::Item_Move:
		ItemMove(m_itemState);
		break;
	case Item::Item_Now:
		ItemNow();
		break;
	}
}

