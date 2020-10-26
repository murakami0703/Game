#include "stdafx.h"
#include "item/HpRecovery.h"
#include "player/Player.h"
#include "data/GameData.h"


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
