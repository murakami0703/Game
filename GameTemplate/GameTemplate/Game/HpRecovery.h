#pragma once
#include "ItemBase.h"
/// <summary>
/// 回復薬。
/// </summary>
class HpRecovery : public ItemBase
{
public:
	HpRecovery();
	~HpRecovery();


	bool Start() override;

	void InUse() override;		//使用中。
	void Flashing() override;	//点滅。
	void EndUse() override;		//終わり。
private:
};

