#include "stdafx.h"
#include "HpRecovery.h"
#include "Player.h"
#include "EffectManager.h"


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
}
void HpRecovery::Flashing()
{
	//点滅。
}
void HpRecovery::EndUse()
{
	//終わり。
}
