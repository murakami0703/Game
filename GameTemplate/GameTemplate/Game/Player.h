#pragma once
#include "character/CharacterController.h"
#include "IActor.h"

class Player  : public IActor
{
public:
	Player();
	~Player();

	bool Start() override;
	void Update() override;

	/// <summary>
	/// 攻撃判定
	/// </summary>
	/// <returns>true		攻撃中</returns>
	const bool Player::GetAttackflag() {
		return attackflag;
	}

	//インスタンスの取得
	static Player* GetInstance() {
		return m_instance;
	}
private:

	//状態。
	enum EState {
		Player_Idle,		//待機
		Player_Walk,		//歩き
		Player_Attack,		//攻撃
		Player_Damage,		//ダメージ
		Player_Dead			//死
	};

	//アニメーション。
	enum PAnimation {
		Animation_Idel,
		Animation_Walk,
		Animation_Run,
		Animation_Drink,
		Animation_Attack,
		Animation_Damage,
		AnimationClip_Num
	};
private:
	static Player* m_instance;

	void Idel();		//待機。
	void Move();		//移動。
	void Attack();		//攻撃。
	void ItemUse();		//アイテム使用。
	void Damage();		//ダメージ受けました。
	void Dead();		//死亡。

private:
	CVector3 m_move = CVector3().Zero();				//移動量。
	EState m_state = Player_Idle;						//状態。
	CharacterController m_characon;					//キャラコン
	AnimationClip m_animClips[AnimationClip_Num];	//アニメーションクリップ

	//Animation関連
	int m_Atcount = 0;			//攻撃回数判定用。

	//攻撃関連
	bool attackflag = false;	//攻撃判定用。

	//HP
	float m_nowHP = 0;			//現在のHP格納庫。
	int m_damageTimer = 0;		//ダメージ時に光らせるときに使うタイマー。

};

