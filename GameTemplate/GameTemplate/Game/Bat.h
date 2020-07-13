#pragma once

class Bat : public IGameObject
{
public:
	Bat();
	~Bat();
	/// <summary>
	/// 遠距離攻撃
	/// </summary>
	bool Start();
	void Update();

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void Bat::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	void Bat::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void Bat::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

private:
	// 状態
	enum EState {
		eState_Loitering,	//徘徊。
		eState_Follow,		//プレイヤーを追跡。
		eState_Premove,		//予備動作。
		eState_Attack,		//攻撃。
		eState_Dead	//死。
	};

	enum EAnimationClip {
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Attack,
		eAnimation_Death,
		eAnimation_Num
	};

private:

	void Loitering();	//徘徊。
	void Follow();		//プレイヤーを追跡。
	void Premove();		//予備動作。
	void Attack();		//攻撃。
	void Dead();		//死。

private:

	SkinModelRender* m_enemyModelRender;				//スキンモデルレンダー。
	CVector3 m_position = CVector3().Zero();			//座標。
	CVector3 m_oldPos = CVector3().Zero();				//初期座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。

	CVector3 m_playerPos = CVector3().Zero();			//プレイヤーの座標。
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。

	EState m_state = eState_Loitering;					//状態。
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。
	
	//移動関連
	const float m_toPlyaerLength = 250.0f;	//追従距離
	const float m_returnLength = 800.0f;	//追従状態から徘徊状態に戻る距離

	//攻撃判定
	bool EneAttackflag = false;					//攻撃中ですか？

	CVector3 moveVec = CVector3().Zero();			//座標。
	float m_caraTime = (1.0f / 60.0f);		//キャラコンの経過時間

	int m_timer = 0;
};

