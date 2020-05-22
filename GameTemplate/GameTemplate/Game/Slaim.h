#pragma once
class Slaim : public IGameObject
{
public:
	Slaim();
	~Slaim();
	/// <summary>
	/// ジャンプ攻撃
	/// </summary>
	void Update();
	void Render();
	void PostRender();

private:
	// 状態
	enum EState {
		eState_Loitering,	//徘徊。
		eState_Follow,		//プレイヤーを追跡。
		eState_Premove,		//予備動作。
		eState_Attack,		//攻撃。
		eState_Return,	//徘徊位置に戻る。
		eState_Dead	//死。
	};

private:

	void Loitering();
	void Follow();
	void Premove();
	void Attack();
	void Return();
	void Dead();

private:

	SkinModelRender* m_enemyModelRender;				//スキンモデルレンダー。
	CVector3 m_position = CVector3().Zero();			//座標。
	CVector3 m_oldPos = CVector3().Zero();				//初期座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。

	EState m_state = eState_Loitering;					//状態。

};

