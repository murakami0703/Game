#include "stdafx.h"
#include "ui/itemui/item/HpRecoveryUI.h"
#include "data/GameData.h"

HpRecoveryUI::HpRecoveryUI()
{
}


HpRecoveryUI::~HpRecoveryUI()
{
	g_goMgr->DeleteGameObject(m_itemSprite);
	g_goMgr->DeleteGameObject(hpRecovery);
}
bool HpRecoveryUI::Start() {

	//0�ԁ��񕜖�
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/HpRecovery.dds", 250.0f, 250.0f);
	m_itemSprite->SetPosition(NOW_ITEM_POSITION);
	m_itemSprite->SetScale(NOW_ITEM_SCALE);
	return true;
}
void HpRecoveryUI::NowItemSelect()
{
	//�I�𒆂̃A�C�e���B
	m_itemSprite->SetPosScale(NOW_ITEM_POSITION, NOW_ITEM_SCALE);
}
void HpRecoveryUI::FirstItemSelect()
{
	//��1�̃A�C�e���B
	m_itemSprite->SetPosScale(NEXT1_ITEM_POSITION, NEXT1_ITEM_SCALE);
}
void HpRecoveryUI::SecondItemSelect()
{
	//��2�̃A�C�e���B
	m_itemSprite->SetPosScale(NEXT2_ITEM_POSITION, NEXT2_ITEM_SCALE);
}

void HpRecoveryUI::ThirdItemSelect()
{
	//��3�̃A�C�e���B
	m_itemSprite->SetPosScale(NEXT3_ITEM_POSITION, NEXT3_ITEM_SCALE);
}

void HpRecoveryUI::UseItem(FontRender* itemContRender)
{
	//�A�C�e���g�p�B
	GameData* gamedata = GameData::GetInstance();
	gamedata->HPRecoveryCalc(-1);
	wchar_t text[MAX_PATH];
	swprintf(text, MAX_PATH - 1, L"%02d", gamedata->GetItemHpRecovery());
	itemContRender->SetText(text);

	//�A�C�e���g�p���t���O�I���B
	gamedata->SetItemInUseFlag(true);

	hpRecovery = g_goMgr->NewGameObject<HpRecovery>();

}
void HpRecoveryUI::OnNowItem(FontRender* itemContRender)
{
	//�I������Ă�̃A�C�e���̐���\���B
	GameData* gamedata = GameData::GetInstance();
	wchar_t text[MAX_PATH];
	swprintf(text, MAX_PATH - 1, L"%02d", gamedata->GetItemHpRecovery());
	itemContRender->SetText(text);
}

void HpRecoveryUI::ItemUseEnd()
{
	//�A�C�e���g���I���܂����B
	hpRecovery->SetState(HpRecovery::End_Use);
}
