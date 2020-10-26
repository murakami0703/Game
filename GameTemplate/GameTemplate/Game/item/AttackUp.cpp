#include "stdafx.h"
#include "item/AttackUp.h"
#include "player/Player.h"
#include "manager/EffectManager.h"


AttackUp::AttackUp()
{
}


AttackUp::~AttackUp()
{
}

bool AttackUp::Start()
{
	return true;
}

void AttackUp::InUse()
{
	//使用中。
}
void AttackUp::EndUse()
{
	//終わり。
}
