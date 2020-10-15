#pragma once

/// <summary>
/// エネミー　：　遠距離攻撃
/// </summary>

class Bat final : public IActor
{
public:
	Bat();
	~Bat();
	/// <summary>
	/// 遠距離攻撃
	/// </summary>
	bool Start() override;
	void Update() override;

private:

	// 状態。
	enum EState {
		eState_Loitering,	//徘徊。
		eState_Follow,		//プレイヤーを追跡。
		eState_Premove,		//予備動作。
		eState_Attack,		//攻撃。
		eState_Dead			//死。
	};

	//アニメーション。
	enum EAnimationClip {
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Attack,
		eAnimation_Death,
		eAnimation_Num
	};

private:

	void Horizon();		//視野角判定

	void Loitering();	//徘徊。
	void Follow();		//プレイヤーを追跡。
	void Premove();		//予備動作。
	void Attack();		//攻撃。
	void Dead();		//死。

private:

	//共通使用。
	EState m_state = eState_Loitering;					//状態。
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。
	CVector3 m_playerPos = CVector3().Zero();			//プレイヤーの座標。
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	int m_timer = 0;									//タイマー。

	//徘徊関係。
	int m_randRot = 0;									//方向の乱数格納。
	CVector3 m_frontmove = CVector3().Zero();			//方向転換時の前ベクトル格納

	//追尾関係。
	CVector3 m_toFollowEPVec = CVector3().Zero();		//追尾中のプレイヤーとの距離ベクトルの格納庫

	//攻撃判定。
	bool EneAttackflag = false;							//攻撃中ですか？
};

