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

	//////////////プレイヤー///////////////////
	
	//体力取得
	float GetHitPoint() {
		return HP;
	}
	//最大体力取得
	float GetMAXHitPoint() {
		return MAXHP;
	}
	//HPの加減計算。
	void  HPCalc(float x) {
		HP += x;
		if (HP < 0) {
			HP = 0;
		}
		if (MAXHP < HP) {
			HP = MAXHP;
		}
	}
	//Playerに攻撃が当たった時の呼ばれる(HP減少)
	void  HPDecrease() {
		HP -= 1.0f;
	}


	//魔力取得
	float GetMagicPoint() {
		return MP;
	}
	//最大魔力取得
	float GetMAXMagicPoint() {
		return MAXMP;
	}

	//攻撃力取得
	float GetATK() {
		return ATK;
	}
	//攻撃力Up薬使用時の攻撃力上昇値の加算。
	void  ATKIncrease() {
		ATK += ATK_INCREASE_VALUE;
	}
	//攻撃力Up薬使用切れ(攻撃力の減算)。
	void  ATKRevert() {
		ATK -= ATK_INCREASE_VALUE;
	}

	//移動速度取得
	float GetSPD() {
		return SPD;
	}
	//移動速度Up薬使用時の移動速度上昇値の加算。
	void  SPDIncrease() {
		SPD += SPD_INCREASE_VALUE;
	}
	//移動速度Up薬使用切れ(移動速度の減算)。
	void  SPDRevert() {
		SPD -= SPD_INCREASE_VALUE;
	}



public:
	//////////////敵///////////////////
	
	//敵の数を取得.。
	int GetEnemyCount() {
		return EnemyCount;
	}
	//敵の数を減少。
	void EnemyReduce()
	{
			EnemyCount--;
	}
	//BOSSを動かすためのフラグ。
	bool GetBossMoveFlag()
	{
		return m_bossMoveFlag;
	}
	//引数をエネミーカウントに代入
	void SetEnemyCount(int x)
	{
		EnemyCount = x;
	}



public:
	//////////////アイテム///////////////////
	
	//回復薬の数を取得。
	int GetItemHpRecovery() {
		return m_hpRecovery;
	}
	//回復薬の加減計算。
	void  HPRecoveryCalc(int x) {
		m_hpRecovery += x;
		if (m_hpRecovery < 0) {
			m_hpRecovery = 0;
		}
		if (MAXItem < m_hpRecovery) {
			m_hpRecovery = MAXItem;
		}
	}

	//爆弾の数を取得。
	int GetItemBum() {
		return m_bum;
	}
	//爆弾の加減計算。
	void  BumCalc(int x) {
		m_bum += x;
		if (m_bum < 0) {
			m_bum = 0;
		}
		if (MAXItem < m_bum) {
			m_bum = MAXItem;
		}
	}

	//攻撃力up薬の数を取得。
	int GetItemAttackUp() {
		return m_attackUp;
	}
	//攻撃力up薬の加減計算。
	void  AttackUpCalc(int x) {
		m_attackUp += x;
		if (m_attackUp < 0) {
			m_attackUp = 0;
		}
		if (MAXItem < m_attackUp) {
			m_attackUp = MAXItem;
		}
	}

	//移動速度up薬の数を取得。
	int GetItemSpeedUp() {
		return m_speedUp;
	}
	//移動速度up薬の加減計算。
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
	//////////////魂///////////////////
	
	//魂の数を取得。
	int GetSoul() {
		return soul;
	}
	//魂の加減計算。
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

	//リザルト開始フラグの設定。
	void  SetResultFlag(const bool& flag)
	{
		resultflag = flag;
	}
	//リザルト開始フラグの取得。
	bool  ResultFlag() const
	{
		return resultflag;
	}

	//ゲームオーバーフラグの設定。
	void  SetGameOverFlag(const bool flag)
	{
		resultflag = flag;
	}
	//ゲームオーバーフラグの取得。
	bool  GameOverFlag() const
	{
		return resultflag;
	}


	// アイテム使用中かどうか判定用のフラグを取得。
	/// <returns>ture		使用中。</returns>
	/// <returns>false		未使用。</returns>
	bool  GetItemInUseFlag() const
	{
		return m_itemInUseFlag;
	}

	// アイテム使用中かどうかのフラグを設定。
	/// <returns>ture		使用中。</returns>
	/// <returns>false		未使用。</returns>
	void  SetItemInUseFlag(const bool flag)
	{
		m_itemInUseFlag = flag;
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

	//各数値。
	float ATK = 30.0f;							//基礎攻撃力
	const float ATK_INCREASE_VALUE = 15.0f;		//攻撃力Up薬使用時の攻撃力の加算値。

	float SPD = 300.0f;							//基礎移動速度
	const float SPD_INCREASE_VALUE = 200.0f;		//移動速度Up薬使用時の移動速度の加算値。


	//敵
	int EnemyCount = 0;				//敵の数
	bool m_bossMoveFlag = false;	//true ボスが動く。
	//たましい
	int soul = 0;	//雑魚から貰える魂
	const int MAXSoul = 999;	//最大Anima
	int BigSoul = 0;	//ボスから貰える魂

	bool resultflag = false;		//リザルトです。
	bool gameOverflag = false;		//true ゲームオーバです。

	//アイテム
	int m_hpRecovery = 2;	//回復薬
	int m_bum = 2;			//爆弾
	int m_attackUp = 2;		//攻撃力UP
	int m_speedUp = 2;		//移動速度UP

	const int MAXItem = 99;	//最大所持アイテム数

	bool m_itemInUseFlag = false;		//アイテム使用中フラグ。
};

