#pragma once
#include "character/CharacterController.h"

class Player  : public IGameObject
{
public:
	Player();
	~Player();

	enum PAnimation {
		Animation_Idel,
		Animation_Walk,
		Animation_Attack1,
		Animation_Attack2,
		Animation_Dead,
		AnimationClip_Num
	};

	enum EState {
		Player_Idle,
		Player_Walk,
		Player_Attack,
		Player_Dead
	};

	void Update();
	void Render();
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
	/*SkinModel* GetPlayerSkinModel() {
		return &m_model;
	}*/
	/// <summary>
	/// 攻撃判定
	/// </summary>
	/// <returns>trueなら攻撃中</returns>
	bool Player::GetAttackflag() {
		return attackflag;
	}
	//インスタンスの取得
	static Player* GetInstance() {
		return m_instance;
	}

private:
	static Player* m_instance;
	void Idel();
	void Move();						//移動。
	void Attack();
	void Dead();

	SkinModelRender* m_model;		//スキンモデル
	CVector3 m_position = CVector3().Zero();			//座標
	CQuaternion m_rotation = CQuaternion().Identity();	//回転
	CVector3 m_scale = CVector3().One();			//拡大率
	CVector3 m_move;	//移動
	CharacterController m_characon;		//キャラコン
	EState m_state = Player_Idle;
	//移動関連
	float m_movespeed = 500.0f;			//移動速度
	const float m_rotationLR = 80.0f;	//左右の回転角度
	const float m_rotationD = 110.0f;	//下の回転角度
	float m_caraTime = (1.0f / 60.0f);	//キャラコンの経過時間
	const float m_jumpPos = 50.0f;		//ジャンプの高さ
	//Animation関連
	int Atcount = 0;	//攻撃回数判定用。
	PAnimation m_anime = Animation_Idel;		//アニメーション状態
	Animation	m_animation;					//アニメーション
	AnimationClip m_animClips[AnimationClip_Num];	//アニメーションクリップ

	//攻撃関連
	bool attackflag = false;	//攻撃判定用。
};

