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
	void Dead(Player* player);

	SkinModel m_enemy;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();			//座標
	CVector3 m_oldPos = CVector3().Zero();			//座標
	CVector3 m_scale= CVector3().One();					//拡大率
	EState m_state = eState_Haikai;						//敵の状態。
	CVector3 p_pos = CVector3().Zero();
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	AnimationClip  m_animClips[num];

	//移動関連
	int m_moveCount = 0;
	float m_moveSpeed = 0.6f;			//エネミの移動速度。
	const float m_plFollow = 100.0f;	//追尾する距離。
	const float m_follSpeed = 0.7f;		//追尾中の移動速度。
	const float m_tuisekiLength = 300.0f;		//追尾する距離。
	const float m_ReturnLength = 400.0f;		//徘徊位置に戻る距離。
};

