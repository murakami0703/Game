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
	void SpriteBound(SpriteRender* m_sprite);

	void Bound();
	void TopLeft();
	void Soul();
	void Total();
	void Jewelry();

private:
	enum eState {
		Result_Bound,		//ResultspriteをBound表示。
		Result_TopLeft,		//Resultspriteを縮小、左上に。
		Result_Soul,		//stageでゲットした魂の数カウント
		Result_Total,		//合計魂のカウント
		Result_Jewelry,		//ボスが排出した宝石処理

	};
private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_itemSprite;

	FontRender* m_font;
	
	//リザルトsprite関連
	const float m_startYPos = 760.0f;
	const float m_startXPos1 = 100.0f;
	const float m_startXPos2 = 300.0f;
	const float m_startXPos3 = 500.0f;
	float m_a = (760.0f / 60.0f);

	eState m_state = Result_Bound;

};

