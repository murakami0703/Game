#pragma once
#include "Player.h"
class BattlePoint;


class Enemy
{
public:
	Enemy();
	~Enemy();

	enum enAnimationClip {
		eneidle,
		enewalk,
		eneAttack_1,
		eneDead,
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
	/// <summary>
	/// エネミのポジションを返す関数。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 Enemy::GetPosition() {
		return m_position;
	}
	/// <summary>
	/// 攻撃判定
	/// </summary>
	/// <returns>trueなら攻撃中</returns>
	bool Enemy::GetAttackflag() {
		return EneAttackflag;
	}

private:
	/// <summary>
	/// 状態
	/// </summary>
	enum EState {
		eState_Haikai,			//徘徊中
		eState_TuisekiPlayer,	//プレイヤーを追跡中。
		eState_Attack,		//攻撃します。
		eState_Return,	//徘徊位置に戻る。
		eState_Dead	//死

	};

	void Follow(Player* player);
	void move();
	void Attack(Player* player);
	void Return();
	void Dead();

	SkinModel m_enemy;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();			//座標
	CVector3 m_oldPos = CVector3().Zero();			//座標
	CQuaternion m_rotation = CQuaternion().Identity();	//回転
	CVector3 m_scale= CVector3().One();					//拡大率
	EState m_state = eState_Haikai;						//敵の状態。
	CVector3 p_pos = CVector3().Zero();
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	AnimationClip  m_animClips[num];

	//移動関連
	int m_moveCount = 0;				//巡回用カウント
	float m_moveSpeed = 0.6f;			//エネミの移動速度。
	const float m_follSpeed = 1.9f;		//追尾中の移動速度。
	const float m_tuisekiLength = 300.0f;		//追尾する距離。
	const float m_ReturnLength = 400.0f;		//徘徊位置に戻る距離。
	Animation	m_animation;					//アニメーション
	bool m_battlePosflag = false;				//ちゃんとBPにいますか？

	BattlePoint* m_battlePoint = nullptr;		//エネミのバトルポイント先
	//攻撃判定
	bool EneAttackflag = false;

	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
	ID3D11ShaderResourceView* g_specularMapSRV = nullptr;
	ID3D11ShaderResourceView* g_ambientMapSRV = nullptr;
};

