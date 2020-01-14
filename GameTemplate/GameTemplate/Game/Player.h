#pragma once
#include "character/CharacterController.h"
#include "ShadowMap.h"

class Player 
{
public:
	Player();
	~Player();

	enum PAnimation {
		Animation_Idel,
		Animation_Walk,
		Animation_Attack1,
		Animation_Attack2,
		AnimationClip_Num
	};

	void Update();
	void Draw(EnRenderMode renderMode);
	/// <summary>
	/// プレイヤーのポジションを返す関数。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
	/// <summary>
	/// プレイヤーのモデルを取得。
	/// </summary>
	/// <returns>プレイヤーのスキンモデル</returns>
	SkinModel* GetPlayerSkinModel() {
		return &m_model;
	}
	/// <summary>
	/// 攻撃判定
	/// </summary>
	/// <returns>trueなら攻撃中</returns>
	bool Player::GetAttackflag() {
		return attackflag;
	}
private:
	void Move();						//移動。
	void PlAnimation();//アニメーション

	SkinModel m_model;		//スキンモデル
	CVector3 m_position = CVector3().Zero();			//座標
	CQuaternion m_rotation = CQuaternion().Identity();	//回転
	CVector3 m_scale = CVector3().One();			//拡大率
	CVector3 m_move;	//移動
	CharacterController m_characon;		//キャラコン

	//移動関連
	float m_movespeed = 200.0f;
	const float m_rotationLR = 80.0f;
	const float m_rotationD = 110.0f;
	float m_caraTime = (1.0f / 60.0f);
	//Animation関連
	int Atcount = 0;	//攻撃回数判定用。
	PAnimation m_anime = Animation_Idel;		//アニメーション状態
	Animation	m_animation;					//アニメーション
	AnimationClip m_animClips[AnimationClip_Num];	//アニメーションクリップ

	//攻撃関連
	bool attackflag = false;	//攻撃判定用。
};

