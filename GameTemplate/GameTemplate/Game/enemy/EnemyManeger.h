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
	/// ��ԋ߂��o�g���|�C���g���擾�ł��邩�ǂ����������܂��B
	/// </summary>
	/// <param name="result">�o�g���|�C���g�̈ʒu</param>
	/// <param name="position">�G�l�~�[�̍��W</param>
	BattlePoint* TryGetBattlePoint(CVector3 position);
	/// <summary>
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static EnemyManager* GetInstance()
	{
		return m_instance;
	}
	/// <returns>���W</returns>
	CVector3 EnemyManager::GetPosition() {
		return m_position;
	}
private:
	static EnemyManager* m_instance;
	std::vector<Enemy*> m_enemys;	//�G�l�~�p�̓��I�z��
	static const int NUM_POINT = 8;	//�ő�o�g���|�C���g
	BattlePoint m_battlepoint[NUM_POINT];

	bool m_deadFlag = false;	//���ꂩ���ɂ܂���
	//�o�g���|�C���g�֘A
	const float m_pointdistance = 250.0f;	//�|�C���g�܂ł̋���
	float m_toBPLeng[NUM_POINT];
	float m_BPMinLeng = 0;		//��ԋ߂��o�g���|�C���g�̒���

	CVector3 m_position = CVector3().Zero();			//���W


};

