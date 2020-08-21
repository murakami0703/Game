#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();

	bool Start();		
	void Update();	

	static Title* GetInstance()
	{
		return m_instance;
	}
private:
	//状態
	enum EState {
		Title_FadeIn,		//フェードイン。
		Title_GameTitle,	//文字の表示。
		Title_Select,		//ボタン選択。
		Title_FadeOut,		//フェードアウト。
	};

	//小人の移動
	enum EVillainMove {
		Villain_SideWays1,	//横移動1。
		Villain_Forward,	//左上移動。
		Villain_Stay,		//留まる。
		Villain_Back,		//右下移動。
		Villain_SideWays2,	//横移動2。
		Villain_Stop,		//停止。
		Villain_SideWays3	//横移動3。
	};

	//選択ボタン
	enum EButton {
		Button_Start,
		Button_Load
	};
private:
	void TitleFadeIn();			//フェードイン。
	void TitleGameTitle();		//文字の表示。
	void TitleSelect();			//ボタン選択。
	void TitleFadeOut();		//フェードアウト。

	//小人
	void ChangeSprite(SpriteRender* m_sprite1, SpriteRender* m_sprite2, float moveX = 0.0f, float moveY = 0.0f);		//スプライトの切り替え。
	void SpriteSetAlpha(SpriteRender* m_nextSprite, SpriteRender* m_invisible1, SpriteRender* m_invisible2);

	void VillainSideWays1();	//横移動1。
	void VillainForward();		//左上移動。
	void VillainStay();			//留まる。
	void VillainBack();			//右下移動。
	void VillainSideWays2();	//横移動2。
	void VillainStop();			//停止。
	void VillainSideWays3();	//横移動3。

	void LightFlashing();		//ライトの点滅


private:

	static Title* m_instance;

	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列。
	SpriteRender* m_titleSprite;				//スプライトレンダー。

	FontRender* m_startFont;					//Startフォント。
	FontRender* m_loadFont;						//Loadフォント。

	EState m_state = Title_FadeIn;						//状態。
	EVillainMove m_villainState = Villain_SideWays1;	//小人の移動状態。
	EButton m_buttonState = Button_Start;				//選択中のボタン状態。

	//音関係
	CSoundSource* m_titleBgm;					//タイトルBGM。
	CSoundSource* m_se;					//タイトルBGM。

	//ライトの点滅
	float m_flashingTimer = 0;		//ライト用タイマー。
	int m_fontTimer = 0;			//文字用タイマー。
	int count = 0;
	int m_stopTimer = 0;			//停止時間用タイマー。
	bool movestart = false;
};

