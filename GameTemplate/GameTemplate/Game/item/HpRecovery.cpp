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
	//使用中。
	if (GameData::GetInstance()->GetItemInUseFlag() != false) {
		//HPを+１する。
		GameData::GetInstance()->HPCalc(1.0f);
		GameData::GetInstance()->SetItemInUseFlag(false);
	}
}
void HpRecovery::EndUse()
{
	//終わり。
}
