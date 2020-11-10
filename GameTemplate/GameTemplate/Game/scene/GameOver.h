#pragma once
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();

	bool Start();
	void Update();

private:
	enum eState {
		BackGD_Dark,		//ゲームシーンを灰色に。
		Sprite_Set,			//GAMEOVERの文字出す。
		Font_Set
	};

	void BackGDDark();
	void GameOverSet();
	void NextSet();

private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_gameOverSprite;
	eState m_state = BackGD_Dark;

	const float m_startYPos = 400.0f;	//GameOverの初期Ｙ位置。
	const float m_moveYPos = 150.0f;	//GameOverの下降位置。
	const float m_setYPos = 170.0f;		//GameOverの位置。

	const float m_overSpeed = 10.0f;	//GameOverの移動速度。
	bool m_bound = false;

	float m_mulColor = 1.0f;			//BGの乗算カラー
	const float m_SetMulColor = 0.2f;	//BGの最終乗算値

};

