#include "stdafx.h"
#include "siegepoint/SiegePoint.h"
#include "enemy/Ghost.h"
#include "player/Player.h"

SiegePoint* SiegePoint::m_instance = nullptr;

SiegePoint::SiegePoint()
{
	m_instance = this;
}
SiegePoint::~SiegePoint()
{
}

BattlePoint* SiegePoint::TryGetBattlePoint(CVector3 position)
{

	for (int t = 0; t < NUM_POINT; t++) {
		//各バトルポイントとエネミの距離の長さをお調べ。
		CVector3 m_toBPVec = m_battlepoint[t].position - position;
		m_toBPLeng[t] = m_toBPVec.Length();
	}
	//一番近い距離を調べる。
	m_BPMinLeng = 100000.0f;
	int NUM_BPMin = -1;
	for (int i = 0; i < NUM_POINT; i++) {
		//バトルポイントを探して空いている
		//一番近い場所を探す
		if (m_BPMinLeng > m_toBPLeng[i] && m_battlepoint[i].enemyCount < 1) {
			m_BPMinLeng = m_toBPLeng[i];
			//空いてた
			NUM_BPMin = i;
		}
	}

	//BPにエネミはいなかったので
	//指定された番号のBPに行くぅ
	if (NUM_BPMin != -1) {
		m_battlepoint[NUM_BPMin].enemyCount++;
		return &m_battlepoint[NUM_BPMin];
	}

	return nullptr;		//使用中

}
void SiegePoint::Update()
{
	//バトルフィールドの座標を計算
	{
		CVector3 PlayerPos = Player::GetInstance()->GetPosition();

		for (int t = 0; t < NUM_POINT; t++) {
			m_battlepoint[t].position = PlayerPos;
		}
		//上
		m_battlepoint[0].position.z = m_battlepoint[0].position.z + m_pointdistance;
		//右上
		m_battlepoint[1].position.z = m_battlepoint[1].position.z + m_pointdistance;
		m_battlepoint[1].position.x = m_battlepoint[1].position.x + m_pointdistance;
		//右
		m_battlepoint[2].position.x = m_battlepoint[2].position.x + m_pointdistance;
		//右下
		m_battlepoint[3].position.z = m_battlepoint[3].position.z - m_pointdistance;
		m_battlepoint[3].position.x = m_battlepoint[3].position.x + m_pointdistance;
		//下
		m_battlepoint[4].position.z = m_battlepoint[4].position.z - m_pointdistance;
		//左下
		m_battlepoint[5].position.z = m_battlepoint[5].position.z - m_pointdistance;
		m_battlepoint[5].position.x = m_battlepoint[5].position.x - m_pointdistance;
		//左
		m_battlepoint[6].position.x = m_battlepoint[6].position.x - m_pointdistance;
		//左上
		m_battlepoint[7].position.z = m_battlepoint[7].position.z + m_pointdistance;
		m_battlepoint[7].position.x = m_battlepoint[7].position.x - m_pointdistance;
	}
}



