#pragma once
//class HPSetPoint;

class GameUI : public IGameObject
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
	void PostRender();

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
	float GameUI::GetCount()
	{
		return m_hpCount;		//表示HPカウント。

	}
private:
	// アイテム選択枠の設定
	void CaseSet();


private:

	//FontRender* m_font;
	static GameUI* m_instance;

	//アイテム関連
	Sprite m_itemCase1;		//枠1
	Sprite m_itemCase2;		//枠2
	Sprite m_itemCase3;		//枠3
	Sprite m_itemCase4;		//枠4

	CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };			//枠1の座標
	CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//枠2の座標
	CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//枠3の座標
	CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };	//枠4の座標

	CVector3					m_itemC1Scale = { 0.8f,0.8f,0.8f };				//枠1拡大率
	CVector3					m_itemC24Scale = { 0.7f,0.7f,0.7f };				//枠4拡大率

	//HPSetPoint* m_hpPoint = nullptr;		//ポイント先

	float HP = 0.0f;		//現在のHPをもらう。
	float m_hpCount = 0.0f;		//表示HPカウント。

};

