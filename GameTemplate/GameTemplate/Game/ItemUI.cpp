#include "stdafx.h"
#include "ItemUI.h"
#include "GameData.h"

//�A�C�e��
#include "HpRecovery.h"
#include "Bum.h"
#include "AttackUp.h"
#include "SpeedUp.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////
 
///////////////////////
///sprite
const int HPRECOVERY = 0;				//�񕜖�B
const int BOMB = 1;						//���e�B
const int ATTACKUPRECOVERY = 2;			//�U����Up��B
const int SPEEDUPRECOVERY = 3;			//�ړ����x�㏸��B
///////////////////////

const CVector3 NOW_ITEM_SCALE = { 0.45f, 0.45f ,0.45f };			//�I�𒆃A�C�e���̊g�嗦
const CVector3 NEXT1_ITEM_SCALE = { 0.35f,0.35f ,0.35f };			//��1�A�C�e���̊g�嗦
const CVector3 NEXT2_ITEM_SCALE = { 0.25f,0.25f ,0.25f };			//��2�A�C�e���̊g�嗦
const CVector3 NEXT3_ITEM_SCALE = { 0.15f,0.15f ,0.15f };			//��3�A�C�e���̊g�嗦

const CVector3 NOW_ITEM_POSITION = { 460.0f,-240.0f,0.0f };			//�I�𒆃A�C�e���̍��W
const CVector3 NEXT1_ITEM_POSITION = { 560.0f,-120.0f,0.0f };		//��1�A�C�e���̍��W
const CVector3 NEXT2_ITEM_POSITION = { 475.0f,-50.0f,0.0f };		//��2�A�C�e���̍��W
const CVector3 NEXT3_ITEM_POSITION = { 545.0f,-3.0f,0.0f };			//��3�A�C�e���̍��W

const CVector3 ITEMFONT_SET_COLOR = { 0.3,0.25f,0.2f };					//�A�C�e���t�H���g�̐F�B
const CVector2 ITEMFONT_SET_POSITION = { 470.0f,-250.0f };				//�A�C�e���t�H���g�̍��W�B

ItemUI::ItemUI(){}
ItemUI::~ItemUI(){}

bool ItemUI::Start()
{

	//�A�C�e���J�E���g�t�H���g�̐ݒ�B
	
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
	//�A�C�e���g�p
	switch (m_State) {
	case ItemUI::Item_HpRecovery:
	{
		m_gamedate->HPRecoveryCalc(-1);
		//�g�p��̃A�C�e�����\��
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemHpRecovery());
		m_itemCountFont->SetText(text);

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
		m_itemCountFont->SetText(text);

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
		m_itemCountFont->SetText(text);

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
		m_itemCountFont->SetText(text);

		//�A�C�e���g�p(�ړ����xUp)
		SpeedUp* m_spedup = g_goMgr->NewGameObject<SpeedUp>();
		m_state = Item_InUse;
		break;
	}
	}

}

void ItemUI::ItemMoveSet(eItemState& m_State)
{
	GameData* m_gamedate = GameData::GetInstance();
	
	
	//�A�C�e��sprite�̈ړ��g��ݒ�B
	if (m_State == Item_HpRecovery) {
		m_spriteRender[0]->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
		m_spriteRender[1]->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
		m_spriteRender[2]->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
		m_spriteRender[3]->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);

		//�񕜖�̃A�C�e����
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

		//���e�̃A�C�e����
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

		//�U����UP�̃A�C�e����
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

		//�ړ����xUP�̃A�C�e����
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemSpeedUp());
		m_itemCountFont->SetText(text);

		m_itemMoveEndFlag = true;
	}
}
void ItemUI::ItemMove(eItemState& m_State)
{
	//�A�C�e���I��
	//�����ꂽ�{�^���ł��̃A�C�e����I����ԂɁB
	switch (m_State) {
	case ItemUI::Item_HpRecovery:
	{
		if (m_upDounFlag == true) {
			//��@���e�B
			m_itemState = Item_Bum;
		}
		else {
			//���@�ړ����xUP�B
			m_itemState = Item_SpeedUp;
		}
		//sprite�̈ʒu�g��̐ݒ�B
		ItemMoveSet(m_State);
		//�����ł����̂őI����ԂɑJ�ځB
		if (m_itemMoveEndFlag == true) {
			m_itemMoveEndFlag = false;
			m_state = Item_Now;
		}
		break;
	}
	case ItemUI::Item_Bum:
	{
		if (m_upDounFlag == true) {
			//��@�U����UP�B
			m_itemState = Item_AttackUp;
		}
		else {
			//���@�񕜖�B
			m_itemState = Item_HpRecovery;
		}
		//sprite�̈ʒu�g��̐ݒ�B
		ItemMoveSet(m_State);
		//�����ł����̂őI����ԂɑJ�ځB
		if (m_itemMoveEndFlag == true) {
			m_itemMoveEndFlag = false;
			m_state = Item_Now;
		}
		break;
	}
	case ItemUI::Item_AttackUp:
	{
		if (m_upDounFlag == true) {
			//��@�ړ����xUP�B
			m_itemState = Item_SpeedUp;
		}
		else {
			//���@���e�B
			m_itemState = Item_Bum;
		}
		//sprite�̈ʒu�g��̐ݒ�B
		ItemMoveSet(m_State);
		//�����ł����̂őI����ԂɑJ�ځB
		if (m_itemMoveEndFlag == true) {
			m_itemMoveEndFlag = false;
			m_state = Item_Now;
		}
		break;
	}
	case ItemUI::Item_SpeedUp:
	{
		if (m_upDounFlag == true) {
			//��@�񕜖�B
			m_itemState = Item_HpRecovery;
		}
		else {
			//���@�U����UP�B
			m_itemState = Item_AttackUp;

		}
		//sprite�̈ʒu�g��̐ݒ�B
		ItemMoveSet(m_State);
		//�����ł����̂őI����ԂɑJ�ځB
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
	//���ݑI������Ă���A�C�e��
	if (g_pad[0].IsTrigger(enButtonY)) {
		//Y�{�^���������ꂽ��A�C�e���g�p��ԂɑJ��
		m_state = Item_Use;
	}

	//LB1�܂���LB2�{�^���������ꂽ��A�C�e���ړ���ԂɑJ��
	if (g_pad[0].IsTrigger(enButtonRB1)) {
		m_upDounFlag = true;		//��
		m_state = Item_Move;
	}
	else if (g_pad[0].IsTrigger(enButtonLB1))
	{
		m_upDounFlag = false;		//��
		m_state = Item_Move;
	}
}
void ItemUI::ItemInUse()
{
	//�A�C�e���g�p���B
	//�e�A�C�e���ɂ���ă��O��݂���B

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

