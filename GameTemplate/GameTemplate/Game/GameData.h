#pragma once
class GameData
{
	/// <summary>
	/// データ。
	/// </summary>
public:
	GameData();
	~GameData();

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
	void  GameData::tiryokugennsyou(int x) {
		HP += x;
		if (HP < 0) {
			HP = 0;
		}
		if (MAXHP < HP) {
			HP = MAXHP;
		}
	}

	/// <summary>
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static GameData* GetInstance()
	{
		return m_instance;
	}

private:
	static GameData* m_instance;

	float HP = 3.0f;	//デフォルトHP
	const float MAXHP = 12.0f;	//最大HP
	float MP = 50.0f;	//デフォルトMP
	const float MAXMP = 400.0f;	//最大MP

	float ATK = 30.0f;	//基礎攻撃力

	//たましい
	float Soul = 0.0f;	//雑魚から貰える魂
	int BigSoul = 0;	//ボスから貰える魂

};

