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
	/// ��ԋ߂��o�g���|�C���g���擾�ł��邩�ǂ����������܂��B
	/// </summary>
	/// <param name="result">�o�g���|�C���g�̈ʒu</param>
	/// <param name="position">�G�l�~�[�̍��W</param>
	BattlePoint* TryGetBattlePoint(CVector3 position);
	/// <summary>
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static SiegePoint* GetInstance()
	{
		return m_instance;
	}
	/// <returns>���W</returns>
	CVector3 SiegePoint::GetPosition() {
		return m_position;
	}


private:
	static SiegePoint* m_instance;
	static const int NUM_POINT = 8;	//�ő�o�g���|�C���g
	BattlePoint m_battlepoint[NUM_POINT];

	//�o�g���|�C���g�֘A
	const float m_pointdistance = 100.0f;	//�|�C���g�܂ł̋���
	float m_toBPLeng[NUM_POINT];
	float m_BPMinLeng = 0;		//��ԋ߂��o�g���|�C���g�̒���

	CVector3 m_position = CVector3().Zero();			//���W


};

