#pragma once
class GameData : public IGameObject
{
	/// <summary>
	/// データ。
	/// </summary>
public:
	GameData();
	~GameData();

	bool Start();
	void Update();

	//体力取得
	float GameData::GetHitPoint() {
		return HP;
	}
	//魔力取得
	float GameData::GetMagicPoint() {
		return MP;
	}
	//攻撃力取得
	float GameData::GetATK() {
		return ATK;
	}
	//移動力取得
	float GameData::GetSPD() {
		return SPD;
	}
	//最大体力取得
	float GameData::GetMAXHitPoint() {
		return MAXHP;
	}
	//最大魔力取得
	float GameData::GetMAXMagicPoint() {
		return MAXMP;
	}

	//引数に設定した値を体力に加算する　負の数を設定したら減少する
	void  GameData::HPCalc(float x) {
		HP += x;
		if (HP < 0) {
			HP = 0;
		}
		if (MAXHP < HP) {
			HP = MAXHP;
		}
	}

	//引数に設定した値を攻撃力に加算する　負の数を設定したら減少する
	void  GameData::ATKCalc(float x) {
		ATK += x;
		if (ATK < 0) {
			ATK = 0;
		}
		if (MAXATK < ATK) {
			ATK = MAXATK;
		}
	}
	//引数に設定した値を移動力に加算する　負の数を設定したら減少する
	void  GameData::SPDCalc(float x) {
		SPD += x;
		if (SPD < 0) {
			SPD = 0;
		}
		if (MAXSPD < SPD) {
			SPD = MAXSPD;
		}
	}

	//////////////敵///////////////////
	//敵の数を取得
	int GameData::GetEnemyCount() {
		return EnemyCount;
	}
	//敵の数を減少
	void GameData::EnemyReduce() 
	{
			EnemyCount--;
	}

	bool GameData::GetBossMoveFlag()
	{
		return m_bossMoveFlag;
	}

	//引数をエネミーカウントに代入
	void GameData::SetEnemyCount(int x)
	{
		EnemyCount = x;
	}
	//////////////アイテム///////////////////
	//回復薬
	int GameData::GetItemHpRecovery() {
		return m_hpRecovery;
	}
	//爆弾
	int GameData::GetItemBum() {
		return m_bum;
	}
	//攻撃力up
	int GameData::GetItemAttackUp() {
		return m_attackUp;
	}
	//移動速度up
	int GameData::GetItemSpeedUp() {
		return m_speedUp;
	}

	void  GameData::HPRecoveryCalc(int x) {
		m_hpRecovery += x;
		if (m_hpRecovery < 0) {
			m_hpRecovery = 0;
		}
		if (MAXItem < m_hpRecovery) {
			m_hpRecovery = MAXItem;
		}
	}
	void  GameData::BumCalc(int x) {
		m_bum += x;
		if (m_bum < 0) {
			m_bum = 0;
		}
		if (MAXItem < m_bum) {
			m_bum = MAXItem;
		}
	}
	void  GameData::AttackUpCalc(int x) {
		m_attackUp += x;
		if (m_attackUp < 0) {
			m_attackUp = 0;
		}
		if (MAXItem < m_attackUp) {
			m_attackUp = MAXItem;
		}
	}
	void  GameData::SpeedUpCalc(int x) {
		m_speedUp += x;
		if (m_speedUp < 0) {
			m_speedUp = 0;
		}
		if (MAXItem < m_speedUp) {
			m_speedUp = MAXItem;
		}
	}


	//////////////魂///////////////////
	void  GameData::AnimaCalc(int x) {
		Anima += x;
		if (Anima < 0) {
			Anima = 0;
		}
		if (MAXAnima < Anima) {
			Anima = MAXAnima;
		}
	}

	void  GameData::SetResultFlag(bool flag)
	{
		resultflag = flag;
	}

	bool  GameData::ResultFlag()
	{
		return resultflag;
	}
	void  GameData::SetGameOverFlag(bool flag)
	{
		resultflag = flag;
	}

	bool  GameData::GameOverFlag()
	{
		return resultflag;
	}

	int GameData::GetAnima() {
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

	float ATK = 10.0f;	//基礎攻撃力
	float SPD = 0.5f;	//基礎移動速度

	const float MAXATK = 50.0f;	//最大攻撃力
	const float MAXSPD = 2.0f;	//最大移動速度

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

