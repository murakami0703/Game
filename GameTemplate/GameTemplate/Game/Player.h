#pragma once
#include "character/CharacterController.h"

class Player 
{
public:
	Player();
	~Player();

	enum Animation {
		Animation_Idel,
		Animation_Walk,
		Animation_Attack1,
		Animation_Attack2,
		Animation_Jump,
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
	Animation m_anime = Animation_Idel;
	CharacterController m_characon;		//キャラコン
};

