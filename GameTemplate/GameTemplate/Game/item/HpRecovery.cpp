#include "stdafx.h"
#include "item/HpRecovery.h"
#include "player/Player.h"
#include "data/GameData.h"

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const float HPRECOVERY_USE_ADD_HP = 1.0f;		//�񕜖�g�p����HP�㏸�l�B

HpRecovery::HpRecovery()
{
}


HpRecovery::~HpRecovery()
{
}

bool HpRecovery::Start()
{
	return true;
}

void HpRecovery::InUse()
{
	//�g�p���B
	GameData* gamedata = GameData::GetInstance();

	if (gamedata->GetItemInUseFlag() != false) {
		//HP��+�P���Z����B
		gamedata->HPCalc(HPRECOVERY_USE_ADD_HP);
		gamedata->SetItemInUseFlag(false);
	}
}
void HpRecovery::EndUse()
{
	//�I���B
	//���X�폜������B
	g_goMgr->DeleteGameObject(this);
}
