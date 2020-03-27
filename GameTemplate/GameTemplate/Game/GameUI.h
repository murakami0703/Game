#pragma once

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();
	/// <summary>
	/// XVB
	/// </summary>
	void Update();
	/// <summary>
	/// `ćB
	/// </summary>
	void Render();
	void PostRender();

	/// <summary>
	/// ACeIđ
	/// </summary>
	void ItemSelect();
	/// <summary>
	/// HP¸
	/// </summary>
	void HPAdd();


	/// <summary>
	/// CX^XĚćžB
	/// </summary>
	/// <returns>CX^X</returns>
	static GameUI* GetInstance()
	{
		return m_instance;
	}
private:

	static GameUI* m_instance;
	
	void ScalingSelectCase();	//IđgĚgĺkŹ
	std::vector<SpriteRender*> m_spriteRender;
	SpriteRender* r;
	FontRender* m_font;
	
	//ACeÖA
	CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };		//g1ĚŔW
	CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//g2ĚŔW
	CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//g3ĚŔW
	CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };		//g4ĚŔW

	CVector3 m_itemC1Scale = { 0.8f,0.8f,0.8f };		//g1gĺŚ
	CVector3 m_itemC24Scale = { 0.7f,0.7f,0.7f };		//g2`4gĺŚ

	CVector3 m_itemSCPos = { 460.0f,-240.0f,0.0f };		//IđgĚŔW
	CVector3 m_itemHPos = { 505.0f,14.0f,0.0f };		//[ĚŔW
	CVector3 m_itemLPos = { 585.0f,-250.0f,0.0f };		//LĚŔW
	CVector3 m_itemZLPos = { 605.0f,20.0f,0.0f };		//ZLĚŔW

	CVector3 m_itemLScale = { 0.8f,0.8f,0.8f };			//LgĺŚ
	CVector3 m_itemZSCScale = { 0.7f,0.7f,0.7f };		//ZL,IđggĺŚ
	CVector3 m_itemHScale = { 0.6f,0.6f,0.6f };			//[gĺŚ

	int m_scalingCount = 0;								//IđggĺkŹpJEg
	const int m_bigCountValue = 30;
	const int m_smallCountValue = 60;
	CVector3 m_scalingValue = { 0.002f,0.002f,0.002f };			//Iđggĺl

	//HPÖA
	CVector3 m_hpPos = { -600.0f,330.0f,0.0f };		//HPĚĹčŔW
	CVector3 m_hpScale = { 0.15f,0.15f,0.15f };		//HPĚgĺŚ
	const float m_hpvAddXPos = 50.0f;					//HP2ČăĚXŔWĚĎťl
	float m_setHP = 0.0f;		//ĹĚHPĘ
	float m_hp = 0.0f;			//ťÝĚHPđi[
};

