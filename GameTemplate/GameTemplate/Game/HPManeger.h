#pragma once
#include "PlayerHP.h"


struct HPSetPoint
{
	CVector3 position = CVector3::Zero();
};

class HPManeger
{
public:
	HPManeger();
	~HPManeger();
	void Update();
	void Draw();

	HPSetPoint* HpSetPoint(float count);

	void RegistAnima(PlayerHP* pHP)
	{
		m_playerHPs.push_back(pHP);
	}
	void DeleteAnima(PlayerHP* pHP)
	{
		//さようなら
		auto it = std::find(m_playerHPs.begin(), m_playerHPs.end(), pHP);
		if (it != m_playerHPs.end()) {
			m_playerHPs.erase(it);
			delete pHP;
		}
	}
	/// <summary>
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static HPManeger* GetInstance()
	{
		return m_instance;
	}

private:
	static HPManeger* m_instance;
	std::vector<PlayerHP*> m_playerHPs;	//エネミ用の動的配列

	static const int NUM_POINT = 12;	//最大HPsetポイント
	HPSetPoint m_hpPoint[NUM_POINT];

};

