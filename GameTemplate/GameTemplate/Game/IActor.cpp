#include "stdafx.h"
#include "IActor.h"


IActor::IActor()
{
}


IActor::~IActor()
{
}
void IActor::CalcAngleAndLength(float& angle, float& distance, const CVector3& actorForward, const CVector3& toObject)
{
	//視野角判定
	//オブジェクトに向かって伸びるベクトルを求める。
	CVector3 toObjectDir = toObject;

	//正規化を行う前に、オブジェクトまでの距離を求めておく。
	distance = toObjectDir.Length();
	//正規化
	toObjectDir.Normalize();

	//toObjectDirとactorForwardとの内積を計算する。
	float d = actorForward.Dot(toObjectDir);

	//内積の結果をacos関数に渡して、toObjectDirとactorForwardのなす角を求める。
	angle = acos(d);

}