#include "stdafx.h"
#include "HpRecovery.h"
#include "Player.h"
#include "GameData.h"


HpRecovery::HpRecovery()
{
}


HpRecovery::~HpRecovery()
{
}

bool HpRecovery::Start()
{
	//0�ԁ��񕜖�
	m_itemSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_itemSprite->Init(L"Assets/sprite/HpRecovery.dds", 250.0f, 250.0f);
	m_itemSprite->SetPosition(NOW_ITEM_POSITION);
	m_itemSprite->SetScale(NOW_ITEM_SCALE);

	m_number = 0;			//�A�C�e���ʒu�ԍ��i�I�𒆁j
	return true;
}

void HpRecovery::InUse()
{
	//�g�p���B
	if (GameData::GetInstance()->GetItemInUseFlag() != false) {
		//HP��+�P����B
		GameData::GetInstance()->HPCalc(1.0f);
		GameData::GetInstance()->SetItemInUseFlag(false);
	}
}
void HpRecovery::EndUse()
{
	//�I���B
}
