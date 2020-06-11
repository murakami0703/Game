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
	void SpriteMove(SpriteRender* m_sprite);

	void Bound();
	void TopLeft();
	void Soul();
	void Total();
	void Jewelry();

private:
	enum eState {
		Result_Background,		//Backgraundを表示。
		Result_SpriteMove,		//Resultspriteを上に表示。
		Result_Soul,		//stageでゲットした魂の数カウント
		Result_Total,		//合計魂のカウント
		Result_Jewelry,		//ボスが排出した宝石処理

	};
private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_itemSprite;

	FontRender* m_font;
	
	//background
	const CVector3 m_bgStartPos = {720.0f,0.0f,0.0f };

	//リザルトsprite関連
	const float m_resultSetYPos = 350.0f;

	const CVector3 m_resultPos1 = { 100.0f,500.0f,0.0f };
	const CVector3 m_resultPos2 = { 150.0f,500.0f,0.0f };
	const CVector3 m_resultPos3 = { 200.0f,500.0f,0.0f };
	const CVector3 m_resultPos4 = { 250.0f,500.0f,0.0f };
	const CVector3 m_resultPos5 = { 300.0f,500.0f,0.0f };
	const CVector3 m_resultPos6 = { 350.0f,500.0f,0.0f };

	const CVector3 m_resultScale = { 0.3f,0.3f,0.3f };
	eState m_state = Result_Background;

};

