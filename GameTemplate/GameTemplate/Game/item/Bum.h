#pragma once
#include "item/ItemBase.h"
/// <summary>
/// 爆弾。
/// </summary>
class Bum : public ItemBase
{
public:
	Bum();
	~Bum();

	bool Start() override;

	void InUse() override;		//使用中。
	void EndUse() override;		//終わり。

private:
	void Parabolic();			//放物線の処理。
private:
	CVector3 diff = CVector3::Zero();	//移動方向。
};

