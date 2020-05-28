#pragma once
class GameData : public IGameObject
{
	/// <summary>
	/// データ。
	/// </summary>
public:
	GameData();
	~GameData();

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

	//引数をエネミーカウントに代入
	void GameData::SetEnemyCount(int x)
	{
		EnemyCount = x;
	}
	//////////////魂///////////////////
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
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static GameData* GetInstance()
	{
		return m_instance;
	}

	static GameData* m_instance;
private:

	float HP = 3.0f;	//デフォルトHP
	const float MAXHP = 12.0f;	//最大HP
	float MP = 50.0f;	//デフォルトMP
	const float MAXMP = 400.0f;	//最大MP

	float ATK = 30.0f;	//基礎攻撃力

	//敵
	int EnemyCount = 0;	//敵の数

	//たましい
	float Anima = 0.0f;	//雑魚から貰える魂
	const float MAXAnima = 999.0f;	//最大Anima
	int BigAnima = 0;	//ボスから貰える魂

	bool resultflag = true;
};

