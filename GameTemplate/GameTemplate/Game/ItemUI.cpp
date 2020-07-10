#include "stdafx.h"
#include "ItemUI.h"
#include "GameData.h"


ItemUI::ItemUI()
{
}


ItemUI::~ItemUI()
{
}
bool ItemUI::Start()
{
	//�A�C�e��
	{
		//0�ԁ��񕜖�
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/spe.dds", 250.0f, 250.0f);
		m_itemSprite->SetPosition(m_item1Pos);
		m_itemSprite->SetScale({ 0.55f,0.55f ,0.55f });
		m_spriteRender.push_back(m_itemSprite);

		//1�ԁ����e
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/test.dds", 250.0f, 250.0f);
		m_itemSprite->SetPosition(m_item2Pos);
		m_itemSprite->SetScale({ 0.35f,0.35f ,0.35f });
		m_spriteRender.push_back(m_itemSprite);

		//2�ԁ��U����UP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/1.dds", 250.0f, 250.0f);
		m_itemSprite->SetPosition(m_item3Pos);
		m_itemSprite->SetScale({ 0.25f,0.25f ,0.25f });
		m_spriteRender.push_back(m_itemSprite);

		//3�ԁ��ړ����xUP
		m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_itemSprite->Init(L"Assets/sprite/2.dds", 250.0f, 250.0f);
		m_itemSprite->SetPosition(m_item4Pos);
		m_itemSprite->SetScale({ 0.15f,0.15f ,0.15f });
		m_spriteRender.push_back(m_itemSprite);

	}
	//�A�C�e���J�E���g�t�H���g�̐ݒ�B
	GameData* m_gamedate = GameData::GetInstance();
	m_itemCountFont = g_goMgr->NewGameObject<FontRender>();
	swprintf(ItemHpRecText, L"%02d", m_gamedate->GetItemHpRecovery());
	m_itemCountFont->SetText(ItemHpRecText);
	m_itemCountFont->SetColor({ 0.5f,0.4f,0.0f });
	m_itemCountFont->SetPosition({ 480.0f,-240.0f });

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

		m_state = Item_Now;
		break;
	}
	case ItemUI::Item_Bum:
	{
		m_gamedate->BumCalc(-1);
		//�g�p��̃A�C�e�����\��
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemBum());
		m_itemCountFont->SetText(text);

		m_state = Item_Now;
		break;
	}
	case ItemUI::Item_AttackUp:
	{
		m_gamedate->AttackUpCalc(-1);
		//�g�p��̃A�C�e�����\��
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemAttackUp());
		m_itemCountFont->SetText(text);

		m_state = Item_Now;
		break;
	}
	case ItemUI::Item_SpeedUp:
	{
		m_gamedate->SpeedUpCalc(-1);
		//�g�p��̃A�C�e�����\��
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemSpeedUp());
		m_itemCountFont->SetText(text);

		m_state = Item_Now;
		break;
	}
	}

}
void ItemUI::ItemMoveSet(eItemState& m_State)
{
	GameData* m_gamedate = GameData::GetInstance();

	//�A�C�e��sprite�̈ړ��g��ݒ�B
	if (m_State == Item_HpRecovery) {
		m_spriteRender[0]->SetPosScale(m_item1Pos, m_item1Scale);
		m_spriteRender[1]->SetPosScale(m_item2Pos, m_item2Scale);
		m_spriteRender[2]->SetPosScale(m_item3Pos, m_item3Scale);
		m_spriteRender[3]->SetPosScale(m_item4Pos, m_item4Scale);

		//�񕜖�̃A�C�e����
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemHpRecovery());
		m_itemCountFont->SetText(text);

		m_itemMoveEndFlag = true;

	}
	else if (m_State == Item_Bum)
	{
		m_spriteRender[0]->SetPosScale(m_item4Pos, m_item4Scale);
		m_spriteRender[1]->SetPosScale(m_item1Pos, m_item1Scale);
		m_spriteRender[2]->SetPosScale(m_item2Pos, m_item2Scale);
		m_spriteRender[3]->SetPosScale(m_item3Pos, m_item3Scale);

		//���e�̃A�C�e����
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemBum());
		m_itemCountFont->SetText(text);

		m_itemMoveEndFlag = true;

	}
	else if (m_State == Item_AttackUp)
	{
		m_spriteRender[0]->SetPosScale(m_item3Pos, m_item3Scale);
		m_spriteRender[1]->SetPosScale(m_item4Pos, m_item4Scale);
		m_spriteRender[2]->SetPosScale(m_item1Pos, m_item1Scale);
		m_spriteRender[3]->SetPosScale(m_item2Pos, m_item2Scale);

		//�U����UP�̃A�C�e����
		wchar_t text[256];
		swprintf(text, L"%02d", m_gamedate->GetItemAttackUp());
		m_itemCountFont->SetText(text);

		m_itemMoveEndFlag = true;

	}
	else if (m_State == Item_SpeedUp)
	{
		m_spriteRender[0]->SetPosScale(m_item2Pos, m_item2Scale);
		m_spriteRender[1]->SetPosScale(m_item3Pos, m_item3Scale);
		m_spriteRender[2]->SetPosScale(m_item4Pos, m_item4Scale);
		m_spriteRender[3]->SetPosScale(m_item1Pos, m_item1Scale);

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
	}
}

