#pragma once
#include "character/CharacterController.h"

class Player  : public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	/// <summary>
	/// プレイヤーのポジションを返す関数。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
	/// <summary>
	/// 攻撃判定
	/// </summary>
	/// <returns>true		攻撃中</returns>
	bool Player::GetAttackflag() {
		return attackflag;
	}

	//インスタンスの取得
	static Player* GetInstance() {
		return m_instance;
	}
private:

	enum EState {
		Player_Idle,
		Player_Walk,
		Player_Attack,
		Player_Dead,
		Player_Damage
	};

	enum PAnimation {
		Animation_Idel,
		Animation_Walk,
		Animation_Attack1,
		Animation_Attack2,
		Animation_Dead,
		AnimationClip_Num
	};
private:
	static Player* m_instance;
	void Idel();
	void Move();						//移動。
	void Attack();
	void Dead();

	void Damage();				//ダメージ受けました。

private:
	SkinModelRender* m_skinModelRender = nullptr;				//スキンモデルレンダー。
	CVector3 m_position = CVector3().Zero();			//座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。

	CVector3 m_move = CVector3().Zero();				//移動量。
	EState m_state = Player_Idle;					//状態。

	CharacterController m_characon;		//キャラコン
	AnimationClip m_animClips[AnimationClip_Num];	//アニメーションクリップ

	//移動関連
	float m_movespeed = 800.0f;			//移動速度
	const float m_rotationLR = 80.0f;		//左右の回転角度
	const float m_rotationD = 110.0f;		//下の回転角度
	float m_caraTime = (1.0f / 60.0f);		//キャラコンの経過時間
	const float m_jumpPos = 50.0f;			//ジャンプの高さ

	//Animation関連
	int Atcount = 0;								//攻撃回数判定用。

	//攻撃関連
	bool attackflag = false;	//攻撃判定用。
	//サウンド関係
	CSoundSource m_se;						//se。

	//HP
	float m_nowHP = 0;
	int m_damageTimer = 0;
	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
	ID3D11ShaderResourceView* g_specularMapSRV = nullptr;
	ID3D11ShaderResourceView* g_ambientMapSRV = nullptr;
};

