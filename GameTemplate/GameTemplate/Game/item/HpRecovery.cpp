#include "stdafx.h"
#include "item/HpRecovery.h"
#include "player/Player.h"
#include "data/GameData.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const float HPRECOVERY_USE_ADD_HP = 1.0f;		//回復薬使用時のHP上昇値。

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
	GameData* gamedata = GameData::GetInstance();

	if (gamedata->GetItemInUseFlag() != false) {
		//HPを+１加算する。
		gamedata->HPCalc(HPRECOVERY_USE_ADD_HP);
		gamedata->SetItemInUseFlag(false);
	}
}
void HpRecovery::EndUse()
{
	//終わり。
	//諸々削除させる。
	g_goMgr->DeleteGameObject(this);
}
