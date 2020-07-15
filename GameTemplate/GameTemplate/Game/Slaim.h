#pragma once
#include "character/CharacterController.h"

class BattlePoint;
class Slaim : public IGameObject
{
public:
	Slaim();
	~Slaim();
	/// <summary>
	/// ジャンプ攻撃
	/// </summary>
	
	bool Start();
	void Update();

	/// <summary>
/// 座標を設定。
/// </summary>
	void Slaim::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	void Slaim::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void Slaim::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

private:

	// 状態
	enum EState {
		eState_Idle,	//待機。
		eState_Loitering,	//徘徊。
		eState_Follow,		//プレイヤーを追跡。
		eState_Premove,		//予備動作。
		eState_Premove2,		//予備動作。
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
		eAnimation_Num
	};
	enum EAnimationClip2 {
		eAnimation2_Death,
		eAnimation2_Num
	};

private:

	void Idle();	//待機。
	void Loitering();	//徘徊。
	void Follow();		//プレイヤーを追跡。
	void Premove();		//予備動作。
	void Premove2();		//予備動作。
	void Attack();		//攻撃。
	void Vertigo();	//眩暈。
	void Return();		//徘徊位置に戻る。
	void Dead();		//死。

private:

	SkinModelRender* m_enemyModelRender;				//エネミースキンモデルレンダー。
	SkinModelRender* m_enemyDeadModelRender;				//エネミースキンモデルレンダー。
	CVector3 m_position = CVector3().Zero();			//座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。
	EState m_state = eState_Idle;					//状態。

	CharacterController m_characon;		//キャラコン
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。
	AnimationClip  m_animClips2[eAnimation2_Num];
private:

	//共用
	CVector3 moveVec = CVector3().Zero();			//座標。
	CVector3 m_playerPos = CVector3().Zero();			//プレイヤーの座標。
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	CVector3 m_enemyForward = { 0.0f, 0.0f, 1.0f };			//スライムの前ベクトル。

	float m_timer = 0;
	//待機関連
	float m_idleTime = 30.0f;				//待機時間。

	//徘徊関連
	bool m_changeflag = true;				//方向転換。
	const int m_randTimer = 120;			//方向転換する時間。
	int m_randRot = 0;						//方向の乱数格納。
	const float m_followLength = 300.0f;	//追跡を始める距離。
	const float m_loiteringSpeed = 120.0f;	//徘徊速度。

	//追尾関連
	const float m_toBPPos = 100.0f;			//予備動作開始距離。
	const float m_followSpeed = 250.0f;		//徘徊速度。
	const float m_loiteringLength = 500.0f;	//徘徊に戻る距離。

	bool m_modelflag = false;				//方向転換。




	int m_moveCount = 0;						//巡回用カウント
	float m_moveSpeed = 0.6f;					//エネミの移動速度。
	const float m_follSpeed = 1000.0f;				//追尾中の移動速度。
	const float m_tuisekiLength = 300.0f;		//追尾する距離。
	const float m_ReturnLength = 1000.0f;		//徘徊位置に戻る距離。

	bool m_battlePosflag = false;				//ちゃんとBPにいますか？
	BattlePoint* m_battlePoint = nullptr;		//エネミのバトルポイント先
	float a = 60.0f;
	float timer = 0;


	float m_caraTime = (1.0f / 60.0f);		//キャラコンの経過時間

	int count = 0;							//移動用カウント
	int wrandom = 0;						//移動の方向乱数
	const int randomCount = 120;			//ランダムで移動方向切り替えタイマー
	const float randomSpeed = 300.0f;			//移動速度
	bool flag = true;
	bool flag1 = true;
	int timer1 = 0;
	int timer2 = 0;
	float ko = 0;

	CVector3 dddd= CVector3().Zero();
	CVector3 walk1move = CVector3().Zero();		// 座標。

	bool EneAttackflag = false;					//攻撃中ですか？

};

