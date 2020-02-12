#pragma once
class GameUI
{
public:
	GameUI();
	~GameUI();
	/// <summary>
	/// 更新処理。
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理。
	/// </summary>
	void Draw();

	/// <summary>
	/// アイテム選択処理
	/// </summary>
	void ItemSelect();
	/// <summary>
	/// HP増減処理
	/// </summary>
	void HPAdd();

	/// <summary>
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static GameUI* GetInstance()
	{
		return m_instance;
	}

private:

	static GameUI* m_instance;

	enum SelectItemState
	{
		Fire,
		Nuts,
		Lanp,
		SPtime,
		Num,
	};

	enum HPState {
		HP_1,
		HP_2,
		HP_3,
		HP_4,
		HP_5,
	};

	//HP関連
	Sprite m_hpHartFrame;		//HPの枠
	Sprite m_hpHart1;		//HP1
	Sprite m_hpHart2;		//HP2
	Sprite m_hpHart3;		//HP3
	Sprite m_hpHart4;		//HP4
	Sprite m_hpHart5;		//HP5

	CVector3 m_hpHFPos = CVector3().Zero();			//HPの枠の座標
	CVector3 m_hpHPos = CVector3().Zero();			//HPの座標

	CVector3 m_hpHFScale = CVector3().Zero();			//HPの枠の座標
	CVector3 m_hpScale = CVector3().Zero();			//HPの座標

	//アイテム関連
	Sprite m_itemSetLog;		//枠
	Sprite m_itemSelect;		//アイテム選択
	Sprite m_itemFire;		//(炎)
	Sprite m_itemKinomi;		//(木の実)
	Sprite m_itemLight;		//(ランプ)
	Sprite m_itemTimeSP;		//(時間停止)

	CVector3 m_itemSLPos = CVector3().Zero();			//枠の座標
	CVector3 m_itemSPos = CVector3().Zero();			//アイテム選択の座標
	CVector3 m_itemFPos = CVector3().Zero();			//(炎)の座標
	CVector3 m_itemKPos = CVector3().Zero();			//(木の実)の座標
	CVector3 m_itemLPos = CVector3().Zero();			//(ランプ)の座標
	CVector3 m_itemTSPos = CVector3().Zero();			//(時間停止)の座標

	CVector3					m_itemSLScale = CVector3::One();				//拡大率
	CVector3					m_itemSScale = CVector3::One();				//拡大率
	CVector3					itemFScale = CVector3::One();				//拡大率
	CVector3					m_itemKScale = CVector3::One();				//拡大率
	CVector3					m_itemLScale = CVector3::One();				//拡大率
	CVector3					m_itemTSScale = CVector3::One();				//拡大率

	//アイテム選択関連
	CVector3					m_nowSelect = { 0.75f,0.75f,0.75f };				//選択中の大きさ
	CVector3					m_NoSelect = { 0.4f,0.4f,0.4f };				//選択中の大きさ

	SelectItemState m_SIstate = Fire;	//選択中のアイテム
	//HP増減関連
	HPState m_HPstate;
	float HP = 0.0f;		//現在のHPをもらう。
	float m_hpCount = 0.0f;		//現在のHPをもらう。

};

