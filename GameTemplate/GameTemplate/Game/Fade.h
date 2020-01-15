#pragma once
class Fade
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
	void SetSprite(Sprite sprite) {
		m_sptite = &sprite;
	}
	/// <summary>
	/// ステートの設定
	/// </summary>
	void SetState(State state) {
		m_state = state;
	}
private:
	Sprite* m_sptite;		//スプライト。
	State m_state = None;
};

