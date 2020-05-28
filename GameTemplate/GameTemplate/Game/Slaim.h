#pragma once
class Slaim : public IGameObject
{
public:
	Slaim();
	~Slaim();
	/// <summary>
	/// ジャンプ攻撃
	/// </summary>
	void Update();

private:

	// 状態
	enum EState {
		eState_Idle,	//待機。
		eState_Loitering,	//徘徊。
		eState_Follow,		//プレイヤーを追跡。
		eState_Premove,		//予備動作。
		eState_Attack,		//攻撃。
		eState_Vertigo,		//眩暈。
		eState_Return,	//徘徊位置に戻る。
		eState_Dead	//死。
	};

	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Premove2,
		eAnimation_Attack,
		eAnimation_Vertigo,
		eAnimation_Death,
		eAnimation_Num
	};

private:

	void Idle();	//待機。
	void Loitering();	//徘徊。
	void Follow();		//プレイヤーを追跡。
	void Premove();		//予備動作。
	void Attack();		//攻撃。
	void Vertigo();	//眩暈。
	void Return();		//徘徊位置に戻る。
	void Dead();		//死。

private:

	SkinModelRender* m_enemyModelRender;				//スキンモデルレンダー。
	CVector3 m_position = CVector3().Zero();			//座標。
	CVector3 m_oldPos = CVector3().Zero();				//初期座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。

	EState m_state = eState_Idle;					//状態。
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。

};

