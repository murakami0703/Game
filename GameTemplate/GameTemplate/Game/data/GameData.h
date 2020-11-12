#pragma once
class GameData : public IGameObject
{
	/// <summary>
	/// �f�[�^�B
	/// </summary>
public:
	GameData();
	~GameData();

	bool Start() override;
	void Update() override;

	//////////////�v���C���[///////////////////
	
	//�̗͎擾
	float GetHitPoint() {
		return HP;
	}
	//�ő�̗͎擾
	float GetMAXHitPoint() {
		return MAXHP;
	}
	//HP�̉����v�Z�B
	void  HPCalc(float x) {
		HP += x;
		if (HP < 0) {
			HP = 0;
		}
		if (MAXHP < HP) {
			HP = MAXHP;
		}
	}
	//Player�ɍU���������������̌Ă΂��(HP����)
	void  HPDecrease() {
		HP -= 1.0f;
	}


	//���͎擾
	float GetMagicPoint() {
		return MP;
	}
	//�ő喂�͎擾
	float GetMAXMagicPoint() {
		return MAXMP;
	}

	//�U���͎擾
	float GetATK() {
		return ATK;
	}
	//�U����Up��g�p���̍U���͏㏸�l�̉��Z�B
	void  ATKIncrease() {
		ATK += ATK_INCREASE_VALUE;
	}
	//�U����Up��g�p�؂�(�U���͂̌��Z)�B
	void  ATKRevert() {
		ATK -= ATK_INCREASE_VALUE;
	}

	//�ړ����x�擾
	float GetSPD() {
		return SPD;
	}
	//�ړ����xUp��g�p���̈ړ����x�㏸�l�̉��Z�B
	void  SPDIncrease() {
		SPD += SPD_INCREASE_VALUE;
	}
	//�ړ����xUp��g�p�؂�(�ړ����x�̌��Z)�B
	void  SPDRevert() {
		SPD -= SPD_INCREASE_VALUE;
	}



public:
	//////////////�G///////////////////
	
	//�G�̐����擾.�B
	int GetEnemyCount() {
		return EnemyCount;
	}
	//�G�̐��������B
	void EnemyReduce()
	{
			EnemyCount--;
	}
	//BOSS�𓮂������߂̃t���O�B
	bool GetBossMoveFlag()
	{
		return m_bossMoveFlag;
	}
	//�������G�l�~�[�J�E���g�ɑ��
	void SetEnemyCount(int x)
	{
		EnemyCount = x;
	}



public:
	//////////////�A�C�e��///////////////////
	
	//�񕜖�̐����擾�B
	int GetItemHpRecovery() {
		return m_hpRecovery;
	}
	//�񕜖�̉����v�Z�B
	void  HPRecoveryCalc(int x) {
		m_hpRecovery += x;
		if (m_hpRecovery < 0) {
			m_hpRecovery = 0;
		}
		if (MAXItem < m_hpRecovery) {
			m_hpRecovery = MAXItem;
		}
	}

	//���e�̐����擾�B
	int GetItemBum() {
		return m_bum;
	}
	//���e�̉����v�Z�B
	void  BumCalc(int x) {
		m_bum += x;
		if (m_bum < 0) {
			m_bum = 0;
		}
		if (MAXItem < m_bum) {
			m_bum = MAXItem;
		}
	}

	//�U����up��̐����擾�B
	int GetItemAttackUp() {
		return m_attackUp;
	}
	//�U����up��̉����v�Z�B
	void  AttackUpCalc(int x) {
		m_attackUp += x;
		if (m_attackUp < 0) {
			m_attackUp = 0;
		}
		if (MAXItem < m_attackUp) {
			m_attackUp = MAXItem;
		}
	}

	//�ړ����xup��̐����擾�B
	int GetItemSpeedUp() {
		return m_speedUp;
	}
	//�ړ����xup��̉����v�Z�B
	void  SpeedUpCalc(int x) {
		m_speedUp += x;
		if (m_speedUp < 0) {
			m_speedUp = 0;
		}
		if (MAXItem < m_speedUp) {
			m_speedUp = MAXItem;
		}
	}


public:
	//////////////��///////////////////
	
	//���̐����擾�B
	int GetSoul() {
		return soul;
	}
	//���̉����v�Z�B
	void  SoulCalc(int x) {
		soul += x;
		if (soul < 0) {
			soul = 0;
		}
		if (MAXSoul < soul) {
			soul = MAXSoul;
		}
	}


public:

	//���U���g�J�n�t���O�̐ݒ�B
	void  SetResultFlag(const bool& flag)
	{
		resultflag = flag;
	}
	//���U���g�J�n�t���O�̎擾�B
	bool  ResultFlag() const
	{
		return resultflag;
	}

	//�Q�[���I�[�o�[�t���O�̐ݒ�B
	void  SetGameOverFlag(const bool flag)
	{
		resultflag = flag;
	}
	//�Q�[���I�[�o�[�t���O�̎擾�B
	bool  GameOverFlag() const
	{
		return resultflag;
	}


	// �A�C�e���g�p�����ǂ�������p�̃t���O���擾�B
	/// <returns>ture		�g�p���B</returns>
	/// <returns>false		���g�p�B</returns>
	bool  GetItemInUseFlag() const
	{
		return m_itemInUseFlag;
	}

	// �A�C�e���g�p�����ǂ����̃t���O��ݒ�B
	/// <returns>ture		�g�p���B</returns>
	/// <returns>false		���g�p�B</returns>
	void  SetItemInUseFlag(const bool flag)
	{
		m_itemInUseFlag = flag;
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

	float HP = 5.0f;	//�f�t�H���gHP
	const float MAXHP = 12.0f;	//�ő�HP
	float MP = 50.0f;	//�f�t�H���gMP
	const float MAXMP = 400.0f;	//�ő�MP

	//�e���l�B
	float ATK = 30.0f;							//��b�U����
	const float ATK_INCREASE_VALUE = 15.0f;		//�U����Up��g�p���̍U���͂̉��Z�l�B

	float SPD = 300.0f;							//��b�ړ����x
	const float SPD_INCREASE_VALUE = 200.0f;		//�ړ����xUp��g�p���̈ړ����x�̉��Z�l�B


	//�G
	int EnemyCount = 0;				//�G�̐�
	bool m_bossMoveFlag = false;	//true �{�X�������B
	//���܂���
	int soul = 0;	//�G������Ⴆ�鍰
	const int MAXSoul = 999;	//�ő�Anima
	int BigSoul = 0;	//�{�X����Ⴆ�鍰

	bool resultflag = false;		//���U���g�ł��B
	bool gameOverflag = false;		//true �Q�[���I�[�o�ł��B

	//�A�C�e��
	int m_hpRecovery = 2;	//�񕜖�
	int m_bum = 2;			//���e
	int m_attackUp = 2;		//�U����UP
	int m_speedUp = 2;		//�ړ����xUP

	const int MAXItem = 99;	//�ő及���A�C�e����

	bool m_itemInUseFlag = false;		//�A�C�e���g�p���t���O�B
};

