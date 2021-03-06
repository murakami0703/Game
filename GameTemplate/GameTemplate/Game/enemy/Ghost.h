#pragma once

struct BattlePoint;
class Ghost final : public IActor
{
public:
	Ghost();
	~Ghost();
	bool Start() override;
	void Update() override;
private:

	// 状態
	enum EState {
		eState_Idle,	//待機。
		eState_Loitering,	//徘徊。
		eState_Follow,		//プレイヤーを追跡。
		eState_Premove,		//攻撃。
		eState_Attack,		//攻撃。
		eState_Dead			//死。

	};

	//アニメション。
	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Death,
		eAnimation_Num
	};

private:
	void Horizon();		//視野角判定

	void Idle();		//待機。
	void Loitering();	//徘徊。
	void Follow();		//プレイヤーを追跡。
	void Premove();		//予備動作。
	void Attack();		//攻撃。
	void Dead();		//死。

private:

	//共用
	EState m_state = eState_Loitering;					//状態。
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。
	CVector3 m_playerPos = CVector3().Zero();			//プレイヤーの座標。
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	int m_timer = 0;									//タイマー。

	//バトルポイント関係。
	bool m_battlePosflag = false;				//ちゃんとBPにいますか？
	BattlePoint* m_battlePoint = nullptr;		//エネミのバトルポイント先



	//待機関連
	float m_idleTime = 30.0f;		//待機時間。

	//徘徊関連
	const int m_randTimer = 120;			//方向転換する時間。
	int m_randRot = 0;						//方向の乱数格納。
	CVector3 m_frontmove = CVector3().Zero();			//方向転換時の前ベクトル格納
	const float m_loiteringSpeed = 2.0f;	//徘徊速度。

	//死亡関連
	const float m_deadLength = 150.0f;						//死亡判定の距離
	const CVector3 m_smallValue = { 0.05f, 0.05f, 0.05f };	//死亡時1フレーム毎に縮小させる値
	//Soul関連
	const float m_soulSetYPos = 430.0f;			//魂生成時のY座標の位置
	//エフェクト関連
	const float m_effectEneDeadYPos = 420.0f;						//死亡時再生されるエフェクトのY座標の位置
	const CVector3 m_effectEneDeadSca = { 20.0f, 20.0f, 20.0f };	//死亡時再生されるエフェクトの拡大率。

	int timer1 = 0;
	CVector3 dff = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	bool baund = true;					//攻撃中ですか？

	//攻撃判定
	bool EneAttackflag = false;					//攻撃中ですか？
};

