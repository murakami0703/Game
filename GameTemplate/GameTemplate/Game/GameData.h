#pragma once
class GameData : public IGameObject
{
	/// <summary>
	/// データ。
	/// </summary>
public:
	GameData();
	~GameData();

	bool Start() override;
	void Update() override;

	//体力取得
	float GetHitPoint() {
		return HP;
	}
	//魔力取得
	float GetMagicPoint() {
		return MP;
	}
	//攻撃力取得
	float GetATK() {
		return ATK;
	}
	//最大体力取得
	float GetMAXHitPoint() {
		return MAXHP;
	}
	//最大魔力取得
	float GetMAXMagicPoint() {
		return MAXMP;
	}

	//引数に設定した値を体力に加算する　負の数を設定したら減少する
	void  HPCalc(float x) {
		HP += x;
		if (HP < 0) {
			HP = 0;
		}
		if (MAXHP < HP) {
			HP = MAXHP;
		}
	}

	//////////////敵///////////////////
	//敵の数を取得
	int GetEnemyCount() {
		return EnemyCount;
	}
	//敵の数を減少
	void EnemyReduce() 
	{
			EnemyCount--;
	}

	bool GetBossMoveFlag()
	{
		return m_bossMoveFlag;
	}

	//引数をエネミーカウントに代入
	void SetEnemyCount(int x)
	{
		EnemyCount = x;
	}
	//////////////アイテム///////////////////
	//回復薬
	int GetItemHpRecovery() {
		return m_hpRecovery;
	}
	//爆弾
	int GetItemBum() {
		return m_bum;
	}
	//攻撃力up
	int GetItemAttackUp() {
		return m_attackUp;
	}
	//移動速度up
	int GetItemSpeedUp() {
		return m_speedUp;
	}

	void  HPRecoveryCalc(int x) {
		m_hpRecovery += x;
		if (m_hpRecovery < 0) {
			m_hpRecovery = 0;
		}
		if (MAXItem < m_hpRecovery) {
			m_hpRecovery = MAXItem;
		}
	}
	void  BumCalc(int x) {
		m_bum += x;
		if (m_bum < 0) {
			m_bum = 0;
		}
		if (MAXItem < m_bum) {
			m_bum = MAXItem;
		}
	}
	void  AttackUpCalc(int x) {
		m_attackUp += x;
		if (m_attackUp < 0) {
			m_attackUp = 0;
		}
		if (MAXItem < m_attackUp) {
			m_attackUp = MAXItem;
		}
	}
	void  SpeedUpCalc(int x) {
		m_speedUp += x;
		if (m_speedUp < 0) {
			m_speedUp = 0;
		}
		if (MAXItem < m_speedUp) {
			m_speedUp = MAXItem;
		}
	}


	//////////////魂///////////////////
	void  AnimaCalc(int x) {
		Anima += x;
		if (Anima < 0) {
			Anima = 0;
		}
		if (MAXAnima < Anima) {
			Anima = MAXAnima;
		}
	}

	void  SetResultFlag(bool flag)
	{
		resultflag = flag;
	}

	bool  ResultFlag()
	{
		return resultflag;
	}
	void  SetGameOverFlag(bool flag)
	{
		resultflag = flag;
	}

	bool  GameOverFlag()
	{
		return resultflag;
	}

	int GetAnima() {
		return Anima;
	}

	/////////////////////////////////// 
	/// <summary>
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static GameData* GetInstance()
	{
		return m_instance;
	}

	static GameData* m_instance;
private:

	float HP = 5.0f;	//デフォルトHP
	const float MAXHP = 12.0f;	//最大HP
	float MP = 50.0f;	//デフォルトMP
	const float MAXMP = 400.0f;	//最大MP

	float ATK = 30.0f;	//基礎攻撃力

	//敵
	int EnemyCount = 0;				//敵の数
	bool m_bossMoveFlag = false;	//true ボスが動く。
	//たましい
	int Anima = 0;	//雑魚から貰える魂
	const int MAXAnima = 999;	//最大Anima
	int BigAnima = 0;	//ボスから貰える魂

	bool resultflag = false;		//リザルトです。
	bool gameOverflag = false;	//true ゲームオーバです。

	//アイテム
	int m_hpRecovery = 0;	//回復薬
	int m_bum = 0;			//爆弾
	int m_attackUp = 0;		//攻撃力UP
	int m_speedUp = 0;		//移動速度UP

	const int MAXItem = 99;	//最大所持アイテム数

};

