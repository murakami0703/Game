#pragma once

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();

	bool Start();
	/// <summary>
	/// XVB
	/// </summary>
	void Update();

	/// <summary>
	/// CX^XÌæ¾B
	/// </summary>
	/// <returns>CX^X</returns>
	static GameUI* GetInstance()
	{
		return m_instance;
	}
private:
	void HPCalc();
	void SoulCalc();

private:

	static GameUI* m_instance;
	
	void ScalingSelectCase();					//IðgÌgåk¬
	std::vector<SpriteRender*> m_spriteRender;	//XvCgÌ®Izñ
	SpriteRender* r;
	FontRender* m_soulFont;
	wchar_t soulText[256];

	//ACeÖA
	CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };		//g1ÌÀW
	CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//g2ÌÀW
	CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//g3ÌÀW
	CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };		//g4ÌÀW

	CVector3 m_itemC1Scale = { 0.8f,0.8f,0.8f };		//g1gå¦
	CVector3 m_itemC24Scale = { 0.7f,0.7f,0.7f };		//g2`4gå¦

	CVector3 m_itemSCPos = { 460.0f,-240.0f,0.0f };		//IðgÌÀW
	CVector3 m_itemHPos = { 505.0f,14.0f,0.0f };		//[ÌÀW
	CVector3 m_itemLPos = { 585.0f,-250.0f,0.0f };		//LÌÀW
	CVector3 m_itemZLPos = { 605.0f,20.0f,0.0f };		//ZLÌÀW

	CVector3 m_itemLScale = { 0.8f,0.8f,0.8f };			//Lgå¦
	CVector3 m_itemZSCScale = { 0.7f,0.7f,0.7f };		//ZL,Iðggå¦
	CVector3 m_itemHScale = { 0.6f,0.6f,0.6f };			//[gå¦

	int m_scalingCount = 0;								//Iðggåk¬pJEg
	const int m_bigCountValue = 30;
	const int m_smallCountValue = 60;
	CVector3 m_scalingValue = { 0.002f,0.002f,0.002f };			//Iðggål

	//HPÖA
	CVector3 m_hpPos = { -600.0f,330.0f,0.0f };		//HPÌÅèÀW
	CVector3 m_hpScale = { 0.15f,0.15f,0.15f };		//HPÌgå¦
	const float m_hpvAddXPos = 50.0f;					//HP2ÈãÌXÀWÌÏ»l
	float m_setHP = 0.0f;		//ÅÌHPÊ
	float m_nowHp = 0.0f;			//»ÝÌHPði[
	int m_spriteNum = 7;			//Q[JnÌspriteÌði[B

	//°l¾
	CVector3 m_soulPos = { -575.0f,200.0f,0.0f };		//°l¾ÌÀW
	CVector3 m_soulFramePos = { -500.0f,200.0f,0.0f };		//°l¾gÌÀW
	CVector3 m_soulScale = { 0.35f,0.35f,0.35f };		//°l¾gå¦
	int m_soulNowNum = 0;			//»ÝÌHPði[
	int m_soulSpNum = 0;			//»ÝÌHPði[
};

