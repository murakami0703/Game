#pragma once
#include "character/CharacterController.h"

struct BattlePoint;
class Slaim final : public IActor
{
public:
	Slaim();
	~Slaim();
	/// <summary>
	/// ジャンプ攻撃
	/// </summary>
	
	bool Start();
	void Update();

	

private:

	// 状態
	enum EState {
		eState_Idle,		//待機。
		eState_Loitering,	//徘徊。
		eState_Follow,		//プレイヤーを追跡。
		eState_Premove,		//予備動作。
		eState_Premove2,	//予備動作。
		eState_Attack,		//攻撃。
		eState_Vertigo,		//眩暈。
		eState_Dead			//死。
	};

	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Premove2,
		eAnimation_Attack,
		eAnimation_Vertigo,
		eAnimation_Num
	};
	enum EAnimationClip2 {
		eAnimation2_Death,
		eAnimation2_Num
	};

private:

	void Idle();		//待機。
	void Loitering();	//徘徊。
	void Follow();		//プレイヤーを追跡。
	void Premove();		//予備動作。
	void Premove2();	//予備動作。
	void Attack();		//攻撃。
	void Vertigo();		//眩暈。
	void Dead();		//死。

private:

	SkinModelRender* m_enemyModelRender;				//エネミースキンモデルレンダー。
	SkinModelRender* m_enemyDeadModelRender;				//エネミースキンモデルレンダー。
	EState m_state = eState_Idle;					//状態。

	CharacterController m_characon;		//キャラコン
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。
	AnimationClip  m_animClips2[eAnimation2_Num];
private:

	//共用
	CVector3 m_moveVec = CVector3().Zero();			//座標。
	CVector3 m_setMoveVec = CVector3().Zero();
	CVector3 m_playerPos = CVector3().Zero();			//プレイヤーの座標。
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	CVector3 m_enemyForward = { 0.0f, 0.0f, 1.0f };			//スライムの前ベクトル。

	float m_timer = 0;
	float timer1 = 0;
	//待機状態
	float m_idleTime = 30.0f;				//待機時間。

	//徘徊状態
	bool m_changeflag = true;				//方向転換。
	int m_randRot = 0;						//方向の乱数格納。

	//追尾状態

	bool m_modelChangeFlag = false;				//方向転換。
	//眩暈状態
	int m_vertigoTimer = 0;



	bool EneAttackflag = false;					//攻撃中ですか？
	bool m_battlePosflag = false;				//ちゃんとBPにいますか？
	BattlePoint* m_battlePoint = nullptr;		//エネミのバトルポイント先

};

