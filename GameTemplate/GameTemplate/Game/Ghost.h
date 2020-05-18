#pragma once

class BattlePoint;
class Ghost : public IGameObject
{
public:
	Ghost();
	~Ghost();

	void Update();
	void Render();
	void PostRender();

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void Ghost::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	void Ghost::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void Ghost::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

	/// <summary>
	/// エネミのポジションを返す関数。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 Ghost::GetPosition() {
		return m_position;
	}

	/// <summary>
	/// 攻撃判定
	/// </summary>
	/// <returns>trueなら攻撃中</returns>
	bool Ghost::GetAttackflag() {
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

	enum EAnimationClip {
		eAnimation_Walk,
		eAnimation_Attack,
		eAnimation_Death,
		eAnimation_Num
	};

	void Follow();
	void move();
	void Attack();
	void Return();
	void Dead();

	SkinModelRender* m_enemyModelRender;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();			//座標
	CVector3 m_oldPos = CVector3().Zero();			//座標
	CQuaternion m_rotation = CQuaternion().Identity();	//回転
	CVector3 m_scale = CVector3().One();					//拡大率

	EState m_state = eState_Haikai;						//状態。
	CVector3 p_pos = CVector3().Zero();
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	AnimationClip  m_animClips[eAnimation_Num];

	//移動関連
	int m_moveCount = 0;				//巡回用カウント
	float m_moveSpeed = 0.6f;			//エネミの移動速度。
	const float m_follSpeed = 3.0f;		//追尾中の移動速度。
	const float m_tuisekiLength = 300.0f;		//追尾する距離。
	const float m_ReturnLength = 1000.0f;		//徘徊位置に戻る距離。
	bool m_battlePosflag = false;				//ちゃんとBPにいますか？

	BattlePoint* m_battlePoint = nullptr;		//エネミのバトルポイント先
	//攻撃判定
	bool EneAttackflag = false;

};

