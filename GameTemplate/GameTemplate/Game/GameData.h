#pragma once
class GameData : public IGameObject
{
	/// <summary>
	/// �f�[�^�B
	/// </summary>
public:
	GameData();
	~GameData();

	bool Start();
	void Update();

	//�̗͎擾
	float GameData::GetHitPoint() {
		return HP;
	}
	//���͎擾
	float GameData::GetMagicPoint() {
		return MP;
	}
	//�U���͎擾
	float GameData::GetATK() {
		return ATK;
	}
	//�ő�̗͎擾
	float GameData::GetMAXHitPoint() {
		return MAXHP;
	}
	//�ő喂�͎擾
	float GameData::GetMAXMagicPoint() {
		return MAXMP;
	}

	//�����ɐݒ肵���l��̗͂ɉ��Z����@���̐���ݒ肵���猸������
	void  GameData::HPCalc(float x) {
		HP += x;
		if (HP < 0) {
			HP = 0;
		}
		if (MAXHP < HP) {
			HP = MAXHP;
		}
	}

	//////////////�G///////////////////
	//�G�̐����擾
	int GameData::GetEnemyCount() {
		return EnemyCount;
	}
	//�G�̐�������
	void GameData::EnemyReduce() 
	{
			EnemyCount--;
	}

	//�������G�l�~�[�J�E���g�ɑ��
	void GameData::SetEnemyCount(int x)
	{
		EnemyCount = x;
	}
	//////////////�A�C�e��///////////////////
	//�񕜖�
	int GameData::GetItemHpRecovery() {
		return m_hpRecovery;
	}
	//���e
	int GameData::GetItemBum() {
		return m_bum;
	}
	//�U����up
	int GameData::GetItemAttackUp() {
		return m_attackUp;
	}
	//�ړ����xup
	int GameData::GetItemSpeedUp() {
		return m_speedUp;
	}

	void GameData::ItemHpRecovery()
	{
		m_hpRecovery++;
	}

	//////////////��///////////////////
	void  GameData::AnimaCalc(int x) {
		Anima += x;
		if (Anima < 0) {
			Anima = 0;
		}
		if (MAXAnima < Anima) {
			Anima = MAXAnima;
		}
		Anima;
	}

	void  GameData::SetResultFlag(bool flag)
	{
		resultflag = flag;
	}

	bool  GameData::ResultFlag()
	{
		return resultflag;
	}
	//�̗͎擾
	float GameData::GetAnima() {
		return Anima;
	}

	/////////////////////////////////// 
	/// <summary>
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static GameData* GetInstance()
	{
		return m_instance;
	}

	static GameData* m_instance;
private:

	float HP = 3.0f;	//�f�t�H���gHP
	const float MAXHP = 12.0f;	//�ő�HP
	float MP = 50.0f;	//�f�t�H���gMP
	const float MAXMP = 400.0f;	//�ő�MP

	float ATK = 30.0f;	//��b�U����

	//�G
	int EnemyCount = 0;	//�G�̐�

	//���܂���
	int Anima = 50;	//�G������Ⴆ�鍰
	const int MAXAnima = 999;	//�ő�Anima
	int BigAnima = 0;	//�{�X����Ⴆ�鍰

	bool resultflag = true;

	//�A�C�e��
	int m_hpRecovery = 0;	//�񕜖�
	int m_bum = 0;			//���e
	int m_attackUp = 0;		//�U����UP
	int m_speedUp = 0;		//�ړ����xUP
};

