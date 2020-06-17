#pragma once

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();

	bool Start();
	/// <summary>
	/// 更新処理。
	/// </summary>
	void Update();

	/// <summary>
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static GameUI* GetInstance()
	{
		return m_instance;
	}
private:
	void HPCalc();
private:

	static GameUI* m_instance;
	
	void ScalingSelectCase();					//選択枠の拡大縮小
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* r;
	FontRender* m_font;
	
	//アイテム関連
	CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };		//枠1の座標
	CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//枠2の座標
	CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//枠3の座標
	CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };		//枠4の座標

	CVector3 m_itemC1Scale = { 0.8f,0.8f,0.8f };		//枠1拡大率
	CVector3 m_itemC24Scale = { 0.7f,0.7f,0.7f };		//枠2～4拡大率

	CVector3 m_itemSCPos = { 460.0f,-240.0f,0.0f };		//選択枠の座標
	CVector3 m_itemHPos = { 505.0f,14.0f,0.0f };		//端の座標
	CVector3 m_itemLPos = { 585.0f,-250.0f,0.0f };		//Lの座標
	CVector3 m_itemZLPos = { 605.0f,20.0f,0.0f };		//ZLの座標

	CVector3 m_itemLScale = { 0.8f,0.8f,0.8f };			//L拡大率
	CVector3 m_itemZSCScale = { 0.7f,0.7f,0.7f };		//ZL,選択枠拡大率
	CVector3 m_itemHScale = { 0.6f,0.6f,0.6f };			//端拡大率

	int m_scalingCount = 0;								//選択枠拡大縮小用カウント
	const int m_bigCountValue = 30;
	const int m_smallCountValue = 60;
	CVector3 m_scalingValue = { 0.002f,0.002f,0.002f };			//選択枠拡大値

	//HP関連
	CVector3 m_hpPos = { -600.0f,330.0f,0.0f };		//HPの固定座標
	CVector3 m_hpScale = { 0.15f,0.15f,0.15f };		//HPの拡大率
	const float m_hpvAddXPos = 50.0f;					//HP2以上のX座標の変化値
	float m_setHP = 0.0f;		//最初のHP量
	float m_nowHp = 0.0f;			//現在のHPを格納
	int m_spriteNum = 7;			//ゲーム開始時のspriteの数を格納。
};

