#pragma once
#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Update(Player* player);
	void Draw(EnRenderMode renderMode);
	void AddEnemyTCount(int x) {
		//�����ɐݒ肵���l�����Z����@���̐���ݒ肵���猸������
		m_enemyTcount += x;
		if (m_enemyTcount < 0) {
			m_enemyTcount = 0;
		}

		if (m_enemycount < m_enemyTcount) {
			m_enemyTcount = m_enemycount;
		}
	}
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
	int EnemyManager::GetEnemyTcount()
	{
		return m_enemyTcount;
	}
private:
	static EnemyManager* m_instance ;
	std::vector<Enemy*> m_enemys;

	const int m_enemycount = 5;		//�G�l�~�̍ő�W����
	int m_enemyTcount = 0;	//�ǐՂ��Ă���G�l�~�̐�
};

