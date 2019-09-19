#pragma once
#include "character/CharacterController.h"

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
	/// <summary>
	/// プレイヤーのポジションを返す関数。
	/// </summary>
	/// <returns></returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
private:
	void Move();						//移動。
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();			//座標
};

