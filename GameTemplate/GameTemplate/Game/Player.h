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

	bool Start();
	void Update();
	void Render(int renderMode);
	/// <summary>
	/// プレイヤーのポジションを返す関数。
	/// </summary>
	/// <returns></returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
private:
	void Move();						//移動。
	SkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position = CVector3().Zero();			//座標
	CharacterController m_characon;		//キャラコン
};

