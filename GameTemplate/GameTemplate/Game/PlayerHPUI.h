#pragma once
class PlayerHPUI : public IGameObject
{
public:
	PlayerHPUI();
	~PlayerHPUI();

	bool Start() override;
	void Update() override;

private:
	void HPCalc(const float damegeValue);		//HPの増減計算処理。

private:
	std::vector<SpriteRender*> m_spriteRender;			//スプライトの動的配列。
	SpriteRender* m_hpRender;							//スプライトレンダー。

	float m_nowHP = 0;									//現在のHPの値。
	int m_hpSpriteNum = 0;								//HPスプライトの表示中の数。

	CVector3 m_hpPos = { -650.0f,330.0f,0.0f };			//HPの座標。

};

