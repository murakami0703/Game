#pragma once
#include "character/CharacterController.h"

class Player 
{
public:
	Player();
	~Player();

	enum PAnimation {
		Animation_Idel,
		Animation_Walk,
		AnimationClip_Num
	};

	void Update();
	void Draw(int renderMode);
	void PlAnimation();
	/// <summary>
	/// プレイヤーのポジションを返す関数。
	/// </summary>
	/// <returns></returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
private:
	void Move();						//移動。
	SkinModel m_model;		//スキンモデルレンダラー。
	CVector3 m_position = CVector3().Zero();			//座標
	CQuaternion m_rotation = CQuaternion().Identity();	//回転
	CVector3 m_move;	//移動

	//PAnimation m_anime = Animation_Idel;		//アニメーション状態
	Animation	m_animation;
	AnimationClip m_animClips[AnimationClip_Num];	//アニメーションクリップ
	CharacterController m_characon;		//キャラコン
};

