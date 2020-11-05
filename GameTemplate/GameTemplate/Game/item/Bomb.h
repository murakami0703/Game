#pragma once
#include "item/ItemBase.h"

/// <summary>
/// 爆弾。
/// </summary>
class Bomb : public ItemBase
{
public:
	Bomb();
	~Bomb();
	bool Start() override;

	void InUse() override;		//使用中。
	void EndUse() override;		//終わり。

private:
	void Parabolic();			//配置先の処理。
	void MoveBomb();			//移動の処理。

private:
	CVector3 disPosition = CVector3::Zero();	//配置場所の格納。

	bool m_bombMoveFlag = false;		//爆弾移動中か判定用フラグ。

};

