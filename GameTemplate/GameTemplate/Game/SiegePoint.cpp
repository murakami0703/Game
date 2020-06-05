#include "stdafx.h"
#include "SiegePoint.h"
#include "Ghost.h"
#include "Player.h"

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
		//�e�o�g���|�C���g�ƃG�l�~�̋����̒����������ׁB
		CVector3 m_toBPVec = m_battlepoint[t].position - position;
		m_toBPLeng[t] = m_toBPVec.Length();
	}
	//��ԋ߂������𒲂ׂ�B
	m_BPMinLeng = 100000.0f;
	int NUM_BPMin = -1;
	for (int i = 0; i < NUM_POINT; i++) {
		//�o�g���|�C���g��T���ċ󂢂Ă���
		//��ԋ߂��ꏊ��T��
		if (m_BPMinLeng > m_toBPLeng[i] && m_battlepoint[i].enemyCount < 1) {
			m_BPMinLeng = m_toBPLeng[i];
			//�󂢂Ă�
			NUM_BPMin = i;
		}
	}

	//BP�ɃG�l�~�͂��Ȃ������̂�
	//�w�肳�ꂽ�ԍ���BP�ɍs����
	if (NUM_BPMin != -1) {
		m_battlepoint[NUM_BPMin].enemyCount++;
		return &m_battlepoint[NUM_BPMin];
	}

	return nullptr;		//�g�p��

}
void SiegePoint::Update()
{
	//�o�g���t�B�[���h�̍��W���v�Z
	{
		CVector3 PlayerPos = Player::GetInstance()->GetPosition();

		for (int t = 0; t < NUM_POINT; t++) {
			m_battlepoint[t].position = PlayerPos;
		}
		//��
		m_battlepoint[0].position.z = m_battlepoint[0].position.z + m_pointdistance;
		//�E��
		m_battlepoint[1].position.z = m_battlepoint[1].position.z + m_pointdistance;
		m_battlepoint[1].position.x = m_battlepoint[1].position.x + m_pointdistance;
		//�E
		m_battlepoint[2].position.x = m_battlepoint[2].position.x + m_pointdistance;
		//�E��
		m_battlepoint[3].position.z = m_battlepoint[3].position.z - m_pointdistance;
		m_battlepoint[3].position.x = m_battlepoint[3].position.x + m_pointdistance;
		//��
		m_battlepoint[4].position.z = m_battlepoint[4].position.z - m_pointdistance;
		//����
		m_battlepoint[5].position.z = m_battlepoint[5].position.z - m_pointdistance;
		m_battlepoint[5].position.x = m_battlepoint[5].position.x - m_pointdistance;
		//��
		m_battlepoint[6].position.x = m_battlepoint[6].position.x - m_pointdistance;
		//����
		m_battlepoint[7].position.z = m_battlepoint[7].position.z + m_pointdistance;
		m_battlepoint[7].position.x = m_battlepoint[7].position.x - m_pointdistance;
	}
}


