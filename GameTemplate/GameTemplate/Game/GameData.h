#pragma once
class GameData : public IGameObject
{
	/// <summary>
	/// �f�[�^�B
	/// </summary>
public:
	GameData();
	~GameData();

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
	//////////////��///////////////////
	void  GameData::AnimaCalc(float x) {
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
	float Anima = 0.0f;	//�G������Ⴆ�鍰
	const float MAXAnima = 999.0f;	//�ő�Anima
	int BigAnima = 0;	//�{�X����Ⴆ�鍰

	bool resultflag = true;
};

