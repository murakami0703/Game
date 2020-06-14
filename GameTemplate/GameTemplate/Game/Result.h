#pragma once
class Result : public IGameObject
{
	static Result* m_instance;

public:
	Result();
	~Result();

	//インスタンスの取得
	static Result* Result::GetInstance() {
		return m_instance;
	}
	//更新
	void Update();

private:
	void BackMove();								//背景スプライトの移動処理。
	void SpriteMove(SpriteRender* m_sprite);		//スプライトの下降移動処理。
	void SpriteIndicate(SpriteRender* m_sprite);	//スプライトの表示処理。
	void SpriteScaleUp(SpriteRender* m_sprite);		//スプライトの拡大表示処理。

	void BackTable();		//Backgraundを表示。
	void FallMove();		//Resultフォントを表示。
	void Frame();			//フレームの表示。
	void StageName();		//ゲームステージ名の表示。
	void GetSoul();			//獲得魂の表示。
	void SoulNumber();		//獲得魂の数。
	void GetItem();			//獲得アイテム周りの表示。
	void Next();			//Nextの表示。
	void Removal();			//一旦全部排除。
	void GetJewelry();		//宝石表示。
	void SelectNext();		//SelsctNextの表示。

private:
	enum eState {
		Result_BackTable,		//Backgraundを表示。
		Result_FallMove,		//Resultフォントを表示。
		Result_Frame,			//フレームの表示。
		Result_StageName,		//ゲームステージ名の表示。
		Result_GetSoul,			//獲得魂の表示。
		Result_SoulNumber,		//獲得魂の数。
		Result_GetItem,			//獲得アイテム周りの表示。
		Result_Next,			//Nextの表示。
		Result_Removal,			//一旦全部排除。
		Result_GetJewelry,		//宝石表示。
		Result_SelectNext,		//SelsctNextの表示。
	};
private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_itemSprite;

	FontRender* m_stageNameFont;
	FontRender* m_soulNumFont;

	//background関連
	const float m_backTexAlpha = 0.5f;					//背景の透明度。
	const float m_backTexXPos = 1280.0f;				//二枚目のX座標の位置。
	CVector3 m_backTexpos1 = CVector3().Zero();			//背景の座標1。
	CVector3 m_backTexpos2 = CVector3().Zero();			//背景の座標2。
	const float m_backMove = -2.0f;						//背景の移動速度。

	//リザルト台座関連
	const float m_tableSpeed = 30.0f;					///リザルト台座の移動速度。
	const float m_boundStopXPos = 40.0f;				///リザルト台座のバウンド停止X座標。
	const float m_boundSpeed = 10.0f;					///リザルト台座のバウンド速度。
	bool bound = false;									//バウンド用フラグ。

	//リザルト文字関連
	const CVector3 m_resultFontPos = { 310.0f,505.0f,0.0f };		//リザルト文字の初期座標。
	const float m_resultFontYPos = 310.0f;							//Y座標の停止位置。
	int m_timer = 0;												//時間差用タイマー
	const int m_timeLag[7] = { 0,5,10,15,20,25,40 };				//時間差の各タイム。

	//枠関連
	const CVector3 m_dotLinePos = { 320.0f,175.0f,0.0f };			//点線の座標。
	const CVector3 m_soulFramePos = { 320.0f,75.0f,0.0f };			//魂用枠の座標。
	const CVector3 m_itemFramePos = { 320.0f,-100.0f,0.0f };		//アイテム用枠の座標。

	//ステージ名関連
	const float m_nameStopXPos = 50.0f;					//X座標の停止位置。
	const float m_nameSpeed = 40.0f;					//文字の移動速度。

	//魂関連
	const CVector3 m_soulPos = { 215.0f,75.0f,0.0f };		//魂の座標。
	const CVector3 m_soulScale = { 0.32f,0.32f,0.32f };		//魂の拡大率。
	const CVector3 m_soulFontPos = { 290.0f,35.0f,0.0f };	//魂フォントの拡大率。

	int m_soulNumber = 0;									//獲得魂数を入れるもの。
	const CVector2 m_soulNumPos = { 340.0f,100.0f };		//獲得魂数の座標。
	const CVector3 m_soulNumColor = { 0.3f,0.27f,0.2f };	//獲得魂数のカラー。
	const float m_soulNumScale = 2.0f;					//獲得魂数の拡大率。

	const float m_soulNumStopYPos = 100.0f;					//魂数のY座標の停止位置。
	const float m_soulNumYPos = 120.0f;						//魂数のY座標の折り返し地点。
	const float m_soulNumSpeed = 5.0f;						//魂数の移動速度。

	//アイテム関連
	const CVector3 m_itemFontPos = { 320.0f,-50.0f,0.0f };			//アイテムGetフォントの座標。
	const CVector3 m_itemTablePos1 = { 100.0f,-200.0f,0.0f };		//アイテム台座の座標1。
	const CVector3 m_itemTablePos2 = { 250.0f,-150.0f,0.0f };		//アイテム台座の座標2。
	const CVector3 m_itemTablePos3 = { 400.0f,-150.0f,0.0f };		//アイテム台座の座標3。
	const CVector3 m_itemTablePos4 = { 550.0f,-200.0f,0.0f };		//アイテム台座の座標4。
	const int m_itemtimeLag[5] = { 10,15,20,25,35 };				//時間差の各タイム。

	//Next関連
	const CVector3 m_nextFontPos = { 500.0f,-325.0f,0.0f };			//Nextフォントの座標。
	const CVector3 m_trianglePos = { 600.0f,-325.0f,0.0f };			//三角の座標。
	const float m_triangleStopXPos = 600.0f;						//三角のX座標の停止位置。
	const float m_triangleXPos = 610.0f;							//三角のX座標の折り返し地点。
	const float m_triangleSpeed = 0.5f;								//三角の移動速度。

	//全体使用
	const float m_startAlpha = 0.0f;				//大体の初期透明度。
	const float m_fallMoveSpeed = -15.0f;			//下降速度。
	const float m_Indicate = 0.1f;				//表示させる値。

	//リザルトsprite関連
	const CVector3 m_bgStartPos = { 720.0f,0.0f,0.0f };


	eState m_state = Result_BackTable;		//フレームの表示。
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;				//!<スプライトフォント。

};

