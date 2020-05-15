#pragma once
#include "Enemy.h"

struct BattlePoint
{
	CVector3 position = CVector3::Zero();
	int enemyCount = 0;

};
class EnemyManager : public IGameObject
{
public:
	EnemyManager();
	~EnemyManager();
	void Update();
	void Render();
	void PostRender();

	/// <summary>
	/// 一番近いバトルポイントを取得できるかどうか検索します。
	/// </summary>
	/// <param name="result">バトルポイントの位置</param>
	/// <param name="position">エネミーの座標</param>
	BattlePoint* TryGetBattlePoint(CVector3 position);
	/// <summary>
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static EnemyManager* GetInstance()
	{
		return m_instance;
	}
	/// <returns>座標</returns>
	CVector3 EnemyManager::GetPosition() {
		return m_position;
	}
private:
	static EnemyManager* m_instance;
	std::vector<Enemy*> m_enemys;	//エネミ用の動的配列
	static const int NUM_POINT = 8;	//最大バトルポイント
	BattlePoint m_battlepoint[NUM_POINT];

	bool m_deadFlag = false;	//だれか死にました
	//バトルポイント関連
	const float m_pointdistance = 250.0f;	//ポイントまでの距離
	float m_toBPLeng[NUM_POINT];
	float m_BPMinLeng = 0;		//一番近いバトルポイントの長さ

	CVector3 m_position = CVector3().Zero();			//座標


};

