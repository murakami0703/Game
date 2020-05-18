#pragma once

struct BattlePoint
{
	CVector3 position = CVector3::Zero();
	int enemyCount = 0;

};

class SiegePoint : public IGameObject
{
public:
	SiegePoint();
	~SiegePoint();

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
	static SiegePoint* GetInstance()
	{
		return m_instance;
	}
	/// <returns>座標</returns>
	CVector3 SiegePoint::GetPosition() {
		return m_position;
	}


private:
	static SiegePoint* m_instance;
	static const int NUM_POINT = 8;	//最大バトルポイント
	BattlePoint m_battlepoint[NUM_POINT];

	//バトルポイント関連
	const float m_pointdistance = 100.0f;	//ポイントまでの距離
	float m_toBPLeng[NUM_POINT];
	float m_BPMinLeng = 0;		//一番近いバトルポイントの長さ

	CVector3 m_position = CVector3().Zero();			//座標


};

