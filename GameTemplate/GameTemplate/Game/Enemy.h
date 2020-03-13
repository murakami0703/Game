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
	/// エネミーの座標を設定。
	/// </summary>
	/// <returns>座標</returns>
	void Enemy::SetPosition(CVector3 pos) {
		m_position = pos;
	}
	/// <summary>
/// 回転を設定。
/// </summary>
	void Enemy::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void Enemy::SetScale(CVector3 sca)
	{
		m_scale = sca;
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


	SkinModel m_enemy;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();			//座標
	CQuaternion m_rotation = CQuaternion().Identity();		//回転
	CVector3 m_scale= CVector3().One();					//拡大率
	EState m_state = eState_Haikai;						//敵の状態。
	AnimationClip  m_animClips[num];
};

