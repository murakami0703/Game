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
	const float m_loiteringSpeed = 120.0f;	//徘徊速度。

	//追尾関連

	//移動関連
	int m_moveCount = 0;						//巡回用カウント
	float m_moveSpeed = 0.6f;					//エネミの移動速度。
	const float m_follSpeed = 3.0f;				//追尾中の移動速度。
	const float m_tuisekiLength = 300.0f;		//追尾する距離。
	const float m_ReturnLength = 1000.0f;		//徘徊位置に戻る距離。

	bool m_battlePosflag = false;				//ちゃんとBPにいますか？
	BattlePoint* m_battlePoint = nullptr;		//エネミのバトルポイント先
	//攻撃判定
	bool EneAttackflag = false;					//攻撃中ですか？

	CVector3 walkmove = CVector3().Zero();		// 座標。
	int count = 0;							//移動用カウント
	int wrandom = 0;						//移動の方向乱数
	const int randomCount = 120;			//ランダムで移動方向切り替えタイマー
	const float randomSpeed = 2.0f;			//移動速度

	CVector3 moveVec = CVector3().Zero();			//座標。
	float m_caraTime = (1.0f / 60.0f);		//キャラコンの経過時間
	bool flag = true;
	float timer = 0;
	float timer1 = 0;	
	bool baund = true;

	CVector3 dff = CVector3().Zero();

};

