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
	enum AniAnimation {
		eAnimation_Move,
		eAnimation_Num
	};

	enum EState {
		Anima_Appear,
		Anima_Get,
		Anima_Destroy
	};

	bool Start();
	void Update();

	/// <summary>
	/// 座標をを設定。
	/// </summary>
	void Anima::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

private:
	void Appear();		//出現中。
	void Get();			//取得したよ！！
	void Destroy();		//時間経過のため消滅。

	SkinModelRender* m_animaModelRender;		//スキンモデル
	CVector3 m_position = CVector3().Zero();			//座標
	CQuaternion m_rotation = CQuaternion().Identity();	//回転
	CVector3 m_scale = CVector3().One();			//拡大率

	EState m_state = Anima_Appear;//状態
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。


	const CVector3 m_soulScale = { 3.0f,3.0f,3.0f };			//魂の大きさ
	int m_timer = 0;		//タイマー
	const float m_destroyTimer = 600.0f;	//消滅するまでの時間



};

