#pragma once
#include "IActor.h"

class Golem final : public IActor
{
public:
	Golem();
	~Golem();

	bool Start() override;
	void Update() override;

private:
	//状態。
	enum EState {
		eState_Idle,		//待機。
		eState_Follow,		//プレイヤーを追跡。
		eState_Attack,		//攻撃。
		eState_Back,		//拳を戻す。
		eState_Damage,		//ダメージ受。
		eState_Dead			//死。
	};
	//アニメーション。
	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Attack,
		eAnimation_Back,
		eAnimation_Damage,
		eAnimation_Death,
		eAnimation_Num
	};

private:
	void Idle();		//待機。
	void Follow();		//プレイヤーを追跡。
	void Attack();		//攻撃。
	void Back();		//拳を戻す。
	void Damage();		//ダメージ受。
	void Dead();		//死。

	void MoveHPGage();	//HPゲージの移動。
	void HPBarSaid();	//HPバーの表示処理。
private:
	
	EState m_state = eState_Idle;						//状態。
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。

	std::vector<SpriteRender*> m_spriteRender;			//スプライトの動的配列。
	SpriteRender* m_hpbarSprite;						////スプライトレンダー。

	//共通使用
	CVector3 m_playerPos = CVector3().Zero();			//プレイヤーの座標。
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	int m_timer = 0;	//タイマー

	//追従関係
	CVector3 m_move = CVector3().Zero();		//移動

	//攻撃関係
	bool m_isDamageFlag = false;		//攻撃中にプレイヤーにダメージ与えましたか？
	int m_attacktimer = 0;				//攻撃時用タイマー

	//HP処理関係
	int HP = 120;				//現在HP
	float m_lifeY = 0.0f;
	bool m_moveGageEndflag = false;	//ゲージの移動終わりましたか？

	//HPの表示関係
	CVector3 m_screenPos = CVector3().Zero();
	CVector3 m_hpBarSetPos = CVector3().Zero();
	CVector3 m_cameraPos = CVector3().Zero();
	CVector3 m_hpSpritePos = CVector3().Zero();
	CVector3 m_headPos = CVector3().Zero();
	CVector3 m_lifeScale = CVector3().Zero();
	const CVector2 LifePivot = { 1.0f,0.5f };//HPの基本
	bool m_damegeFlag = false;
	int m_damageCount = 0;
};

