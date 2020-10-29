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
	CVector3 m_StartPoint = CVector3::Zero();			//始点。
	CVector3 m_middlePoint1 = CVector3::Zero();			//中間地点1。
	CVector3 m_middlePoint2 = CVector3::Zero();			//中間地点2。
	CVector3 m_endPoint = CVector3::Zero();			//終点。

	//CVector3 m_correction = CVector3::Zero();			//補正。
	float m_catmull_U;			//補正。

};

