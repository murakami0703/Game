#pragma once
#include "Player.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	enum enAnimationClip {
		enewalk,
		num
	};
	void Update(Player* player);
	void Draw(EnRenderMode renderMode);
	/// <summary>
	/// 座標をを設定。
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
private:
	/// <summary>
	/// 状態
	/// </summary>
	enum EState {
		eState_Haikai,			//徘徊中
		eState_TuisekiPlayer,	//プレイヤーを追跡中。
		eState_Return	//徘徊位置に戻る。
	};

	void Follow(Player* player);
	void move();
	void Return();
	void Dead();

	SkinModel m_enemy;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();			//座標
	CVector3 m_oldPos = CVector3().Zero();			//座標
	CVector3 m_scale= CVector3().One();					//拡大率
	EState m_state = eState_Haikai;						//敵の状態。

	int m_moveCount = 0;
	float m_move = 0.6f;

	AnimationClip  m_animClips[num];
};

