#pragma once

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
private:

	static GameUI* m_instance;
	
	std::vector<SpriteRender*> m_spriteRender;
	SpriteRender* r;

	FontRender* m_font;
	//アイテム関連
	CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };		//枠1の座標
	CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//枠2の座標
	CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//枠3の座標
	CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };		//枠4の座標

	CVector3 m_itemC1Scale = { 0.8f,0.8f,0.8f };		//枠1拡大率
	CVector3 m_itemC24Scale = { 0.7f,0.7f,0.7f };		//枠4拡大率

	//HP関連
	CVector3 m_hpPos = { -600.0f,330.0f,0.0f };		//HPの固定座標
	CVector3 m_hpScale = { 0.15f,0.15f,0.15f };		//HPの拡大率
	const float m_hpvAddXPos = 50.0f;					//HP2以上のX座標の変化値
	float m_setHP = 0.0f;		//最初のHP量
	float m_hp = 0.0f;			//現在のHPを格納
};

