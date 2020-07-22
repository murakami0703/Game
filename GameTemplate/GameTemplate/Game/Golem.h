#pragma once
class Golem : public IGameObject
{
public:
	Golem();
	~Golem();

	bool Start();
	void Update();

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void Golem::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	void Golem::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void Golem::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

private:
	//状態。
	enum EState {
		eState_Idle,		//待機。
		eState_Follow,		//プレイヤーを追跡。
		eState_Attack,		//攻撃。
		eState_Back,		//拳を戻す。
		eState_Damage,		//ダメージ受。
		eState_Dead			//死。
	};
	//アニメーション。
	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Attack,
		eAnimation_Back,
		eAnimation_Damage,
		eAnimation_Death,
		eAnimation_Num
	};

private:
	void Idle();		//待機。
	void Follow();		//プレイヤーを追跡。
	void Attack();		//攻撃。
	void Back();		//拳を戻す。
	void Damage();		//ダメージ受。
	void Dead();		//死。

	void MoveHPGage();	//HPゲージの移動。
	void HPBarSaid();	//HPバーの表示処理。
private:
	SkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダー。
	CVector3 m_position = CVector3().Zero();			//座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。
	EState m_state = eState_Idle;						//状態。
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。

	std::vector<SpriteRender*> m_spriteRender;			//スプライトの動的配列。
	SpriteRender* m_hpbarSprite;						////スプライトレンダー。

	//共通使用
	CVector3 m_playerPos = CVector3().Zero();			//プレイヤーの座標。
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレイヤーまで伸びているベクトル。
	int m_timer = 0;	//タイマー
	//待機関係
	const float m_idleTime = 120.0f;	//休憩時間。
	//追従関係
	CVector3 m_move = CVector3().Zero();		//移動
	//攻撃関係
	const float m_damageLen = 300.0f;	//ダメージ判定の距離
	bool m_isDamageFlag = false;		//攻撃中にプレイヤーにダメージ与えましたか？
	int m_attacktimer = 0;				//攻撃時用タイマー
	const int m_attackEndTime = 60;	//攻撃状態終了タイム

	//ダメージ関係
	const float m_damageLength = 250.0f;	//ダメージを受ける距離。
	const int SUB_HP = 40;		//減少させるHPの値。

	//HPPP
	int HP = 120;				//現在HP
	const int MAX_HP = 120;		//最大HP
	float m_lifeY = 0.0f;
	bool m_moveGageEndflag = false;	//ゲージの移動終わりましたか？

	CVector3 screenPos = CVector3().Zero();
	CVector3 hoge = CVector3().Zero();
	CVector3 cameraPos = CVector3().Zero();
	CVector3 Pos = CVector3().Zero();
	CVector3 atamaNoPos = CVector3().Zero();
	CVector3 LifeScale = CVector3().Zero();
	const CVector2 LifePivot = { 1.0f,0.5f };//HPの基本
	bool m_damegeFlag = false;
	int count = 0;
};

