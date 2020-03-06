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
		//���悤�Ȃ�
		auto it = std::find(m_playerHPs.begin(), m_playerHPs.end(), pHP);
		if (it != m_playerHPs.end()) {
			m_playerHPs.erase(it);
			delete pHP;
		}
	}
	/// <summary>
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static HPManeger* GetInstance()
	{
		return m_instance;
	}

private:
	static HPManeger* m_instance;
	std::vector<PlayerHP*> m_playerHPs;	//�G�l�~�p�̓��I�z��

	static const int NUM_POINT = 12;	//�ő�HPset�|�C���g
	HPSetPoint m_hpPoint[NUM_POINT];

};

