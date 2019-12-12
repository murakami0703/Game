#pragma once
#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Update(Player* player);
	void Draw(EnRenderMode renderMode);
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
	static EnemyManager* GetInstance()
	{
		return m_instance;
	}
private:
	static EnemyManager* m_instance ;
	std::vector<Enemy*> m_enemys;

};

