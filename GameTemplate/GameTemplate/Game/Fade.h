#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();

	enum State {
		None,
		Fadein,		//フェードイン
		FadeOut		//フェードアウト
	};
	void Update();

	/// <summary>
	/// スプライトの設定。
	/// </summary>
	/// <param name="sprite"></param>
	void SetSprite(SpriteRender sprite) {
		m_sptiteRender = &sprite;
	}
private:
	SpriteRender* m_sptiteRender;		//スプライト。
	State m_state = None;
	CVector4 mulColorin;
	CVector4 mulColorout;

};

