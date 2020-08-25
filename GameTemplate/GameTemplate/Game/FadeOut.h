#pragma once
class FadeOut : public IGameObject
{
public:
	FadeOut();
	~FadeOut();

	bool Start();
	void Update();

	/// <summary>
	/// スプライトの設定。
	/// </summary>
	/// <param name="sprite">スプライト</param>
	void SetSprite(SpriteRender* sprite) {
		m_sptiteRender = sprite;
	}

private:
	SpriteRender* m_sptiteRender;				//スプライト。
	CVector4 m_mulColor = CVector4().White();	//乗算カラー。

};

