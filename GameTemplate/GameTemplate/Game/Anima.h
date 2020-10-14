#pragma once

class Anima : public IGameObject
{
	/// <summary>
	/// 魂。
	/// エネミが死んだときに生成。
	/// </summary>
public:
	Anima();
	~Anima();

	bool Start();
	void Update();

	/// <summary>
	/// 座標をを設定。
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
private:
	//状態。
	enum EState {
		Anima_Appear,	//出現中。
		Anima_Get,		//獲得。
		Anima_Destroy	//消滅。
	};
	//アニメーション。
	enum EAnimationClip {
		eAnimation_Move,
		eAnimation_Num
	};

private:
	void Appear();		//出現中。
	void Get();			//獲得したよ！！
	void Destroy();		//消滅。


	SkinModelRender* m_animaModelRender;			//スキンモデル。
	CVector3 m_position = CVector3().Zero();		//座標。

	EState m_state = Anima_Appear;					//状態。
	AnimationClip  m_animClips[eAnimation_Num];		//アニメーションクリップ。

	int m_timer = 0;		//タイマー

};

