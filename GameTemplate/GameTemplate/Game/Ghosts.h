#pragma once
class Ghosts : public IGameObject
{
public:
	Ghosts();
	~Ghosts();

	void Update();
	void Render();
	void PostRender();

	/// <summary>
	/// 座標をを設定。
	/// </summary>
	void Ghosts::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	void Ghosts::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void Ghosts::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// エネミのポジションを返す関数。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 Ghosts::GetPosition() {
		return m_position;
	}
	/// <summary>
	/// 攻撃判定
	/// </summary>
	/// <returns>trueなら攻撃中</returns>
	bool Ghosts::GetAttackflag() {
		return EneAttackflag;
	}

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

	enum enAnimationClip {
		Ghosts_walk,
		Ghosts_Attack,
		Ghosts_Dead,
		num
	};


	void Follow();	//追従
	void move();	//徘徊
	void Attack();
	void Return();
	void Dead();

	SkinModelRender* m_enemy;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();			//座標
	CVector3 m_oldPos = CVector3().Zero();			//初期座標
	CQuaternion m_rotation = CQuaternion().Identity();	//回転
	CVector3 m_scale = CVector3().One();					//拡大率
	EState m_state = eState_Haikai;						//敵の状態。

	AnimationClip  m_animClips[num];			//アニメーションクリップ
	Animation	m_animation;					//アニメーション


	CVector3 p_pos = CVector3().Zero();
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。


		//移動関連
	int m_moveCount = 0;				//巡回用カウント
	float m_moveSpeed = 0.6f;			//エネミの移動速度。
	const float m_follSpeed = 1.9f;		//追尾中の移動速度。
	const float m_tuisekiLength = 300.0f;		//追尾する距離。
	const float m_ReturnLength = 400.0f;		//徘徊位置に戻る距離。
	bool m_battlePosflag = false;				//ちゃんとBPにいますか？

	//BattlePoint* m_battlePoint = nullptr;		//エネミのバトルポイント先

	//攻撃関連
	bool EneAttackflag = false;						//攻撃判定


};

