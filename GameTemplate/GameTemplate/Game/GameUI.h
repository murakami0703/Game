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
	void Render();

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

	Sprite m_hpHartFrame;		//HPの枠
	Sprite m_hpHart1;		//HP1
	Sprite m_hpHart2;		//HP2
	Sprite m_hpHart3;		//HP3
	Sprite m_hpHart4;		//HP4
	Sprite m_hpHart5;		//HP5

	Sprite m_itemSetLog;		//アイテム用の枠

	CVector3 m_hpHFPos = CVector3().Zero();			//HPの枠の座標
	CVector3 m_hpHPos = CVector3().Zero();			//HPの座標
	CVector3 m_itemSLPos = CVector3().Zero();			//アイテム用の枠の座標

};

