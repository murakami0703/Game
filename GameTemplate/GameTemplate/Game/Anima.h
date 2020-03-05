#pragma once
#include "Player.h"

class Anima
{
	/// <summary>
	/// 魂。
	/// エネミが死んだときに生成。
	/// </summary>
public:
	Anima();
	~Anima();
	enum AniAnimation {
		Anima_Move,
		Anima_Num
	};

	enum EState {
		Anima_Appear,
		Anima_Get,
		Anima_Destroy
	};

	void Update(Player* player);
	void Draw(EnRenderMode renderMode);

	/// <summary>
	/// 座標をを設定。
	/// </summary>
	void Anima::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

private:
	void Appear(Player* player);		//出現中。
	void Get();			//取得したよ！！
	void Destroy();		//時間経過のため消滅。

	SkinModel m_animaModel;		//スキンモデル
	CVector3 m_position = CVector3().Zero();			//座標
	CQuaternion m_rotation = CQuaternion().Identity();	//回転
	CVector3 m_scale = CVector3().One();			//拡大率

	EState m_state = Anima_Appear;//状態

	int m_timer = 0;		//タイマー
	const float m_destroyTimer = 600.0f;	//消滅するまでの時間

	//Animation関連
	AniAnimation m_anime = Anima_Move;		//アニメーション状態
	Animation	m_animation;					//アニメーション
	AnimationClip m_animClips[Anima_Num];	//アニメーションクリップ


};

