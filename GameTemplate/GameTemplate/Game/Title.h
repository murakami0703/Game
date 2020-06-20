#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();

	static Title* GetInstance()
	{
		return m_instance;
	}
private:
	void SelectButtun(FontRender* m_font);	//選択中のボタン
	void LightFlashing();		//ライトの点滅

	enum ETitleMove {
		Title_Fadein,
		Title_Gametitle,
		Title_Backgraund,
	};

	enum ESelectButtun {
		Title_Set,
		Game_Start,
		Game_Load
	};

private:
	static Title* m_instance;

	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_titleSprite;

	FontRender* m_startFont;
	FontRender* m_loadFont;

	ESelectButtun m_select = Game_Start;	//選択状態

	//ライトの点滅
	float m_flashingTimer = 0;		//ライト用タイマー。
	const float m_lightsUpTime = 45.0f;
	const float m_lightsOffTime = 90.0f;
	const float m_lightAlpha = 0.7f / 45.0f;

	//星屑の動き


	//フォント位置
	const CVector2 m_startFontPos = { -550.0f,-270.0f };	//「はじめる」の座標
	const CVector2 m_loadFontPos = { 400.0f,-270.0f };		//「つづける」の座標

	CSoundSource m_titleBgm;						//タイトルBGM。

};

