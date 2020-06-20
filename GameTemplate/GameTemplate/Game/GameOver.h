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
		Font_Set,			//GAMEOVERの文字出す。

	};
	void SpriteMove(SpriteRender* m_sprite);		//スプライトの下降移動処理。

private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* r;

};

