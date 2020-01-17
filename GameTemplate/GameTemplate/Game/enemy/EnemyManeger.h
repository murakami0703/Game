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
	/// ��ԋ߂��o�g���|�C���g���擾�ł��邩�ǂ����������܂��B
	/// </summary>
	/// <param name="result">�o�g���|�C���g�̈ʒu</param>
	/// <param name="position">�G�l�~�[�̍��W</param>
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
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static EnemyManager* GetInstance()
	{
		return m_instance;
	}
private:
	static EnemyManager* m_instance ;
	std::vector<Enemy*> m_enemys;	//�G�l�~�p�̓��I�z��
	static const int NUM_POINT = 8;	//�ő�o�g���|�C���g
	BattlePoint m_battlepoint[NUM_POINT];

	//�o�g���|�C���g�֘A
	const float m_pointdistance = 100.0f;	//�|�C���g�܂ł̋���
	float m_toBPLeng[NUM_POINT];
	float m_BPMinLeng = 0;		//��ԋ߂��o�g���|�C���g�̒���

};

