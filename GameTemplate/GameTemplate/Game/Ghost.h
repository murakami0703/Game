#pragma once
#include "character/CharacterController.h"

class BattlePoint;
class Ghost : public IGameObject
{
public:
	Ghost();
	~Ghost();
	bool Start();
	void Update();

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void Ghost::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	void Ghost::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void Ghost::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

	/// <summary>
	/// エネミのポジションを返す関数。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 Ghost::GetPosition() {
		return m_position;
	}

	/// <summary>
	/// 攻撃判定
	/// </summary>
	/// <returns>trueなら攻撃中</returns>
	bool Ghost::GetAttackflag() {
		return EneAttackflag;
	}

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

	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Death,
		eAnimation_Num
	};

private:
	void Horizon();		//視野角判定

	void Idle();	//待機。
	void Loitering();	//徘徊。
	void Follow();		//プレイヤーを追跡。
	void Premove();		//予備動作。
	void Attack();		//攻撃。
	void Dead();		//死。

private:
	SkinModelRender* m_enemyModelRender;				//スキンモデルレンダー。
	CVector3 m_position = CVector3().Zero();			//座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。
	EState m_state = eState_Loitering;					//状態。

	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。
	bool m_battlePosflag = false;				//ちゃんとBPにいますか？
	BattlePoint* m_battlePoint = nullptr;		//エネミのバトルポイント先

	//共用
	CVector3 m_playerPos = CVector3().Zero();			//プレイヤーの座標。
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	CVector3 m_enemyForward = { 0.0f, 0.0f, -1.0f };			//ゴーストの前ベクトル。

	float m_timer = 0;
	const float m_followLength = 500.0f;	//追跡を始める距離。

	//視野角関連
	const float horilong = 500.0f;	//視野角判定の距離
	const float horiAngle = 90.0f;	//視野角判定の角度

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

