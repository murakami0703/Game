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
	void Update();

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
		eAnimation_Death,
		eAnimation_Num
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

	SkinModelRender* m_enemyModelRender;				//スキンモデルレンダー。
	CVector3 m_position = CVector3().Zero();			//座標。
	CVector3 m_oldPos = CVector3().Zero();				//初期座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。
	CharacterController m_characon;		//キャラコン

	EState m_state = eState_Idle;					//状態。
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。

private:
	CVector3 m_playerPos = CVector3().Zero();			//プレイヤーの座標。
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。

	//移動関連
	int m_moveCount = 0;						//巡回用カウント
	float m_moveSpeed = 0.6f;					//エネミの移動速度。
	const float m_follSpeed = 3.0f;				//追尾中の移動速度。
	const float m_tuisekiLength = 300.0f;		//追尾する距離。
	const float m_ReturnLength = 1000.0f;		//徘徊位置に戻る距離。

	bool m_battlePosflag = false;				//ちゃんとBPにいますか？
	BattlePoint* m_battlePoint = nullptr;		//エネミのバトルポイント先
	float a = 60.0f;
	float timer = 0;


	CVector3 moveVec = CVector3().Zero();			//座標。
	float m_caraTime = (1.0f / 60.0f);		//キャラコンの経過時間

	CVector3 walkmove = CVector3().Zero();		// 座標。
	int count = 0;							//移動用カウント
	int wrandom = 0;						//移動の方向乱数
	const int randomCount = 120;			//ランダムで移動方向切り替えタイマー
	const float randomSpeed = 120.0f;			//移動速度
	bool flag = true;
	bool flag1 = true;
	int timer1 = 0;
	int timer2 = 0;

	CVector3 dddd= CVector3().Zero();
	CVector3 walk1move = CVector3().Zero();		// 座標。

	bool EneAttackflag = false;					//攻撃中ですか？

};

