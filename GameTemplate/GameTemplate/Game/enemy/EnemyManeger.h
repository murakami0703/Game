#pragma once
#include "Enemy.h"

struct BattlePoint
{
	CVector3 position = CVector3::Zero();
	int enemyCount = 0;

};
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Update(Player* player);
	void Draw(EnRenderMode renderMode);
	/// <summary>
	/// 一番近いバトルポイントを取得できるかどうか検索します。
	/// </summary>
	/// <param name="result">バトルポイントの位置</param>
	/// <param name="position">エネミーの座標</param>
	BattlePoint* TryGetBattlePoint(CVector3 position);
	void RegistEnemy(Enemy* en)
	{
		m_enemys.push_back(en);
	}
	void DeleteEnemy(Enemy* en)
	{
		auto it = std::find(m_enemys.begin(), m_enemys.end(), en);
		if (it != m_enemys.end()) {
			m_enemys.erase(it);
			delete en;
		}
	}
	/// <summary>
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static EnemyManager* GetInstance()
	{
		return m_instance;
	}
private:
	static EnemyManager* m_instance ;
	std::vector<Enemy*> m_enemys;	//エネミ用の動的配列
	static const int NUM_POINT = 8;	//最大バトルポイント
	BattlePoint m_battlepoint[NUM_POINT];

	//バトルポイント関連
	const float m_pointdistance = 100.0f;	//ポイントまでの距離
	float m_toBPLeng[NUM_POINT];
	float m_BPMinLeng = 0;		//一番近いバトルポイントの長さ

};

