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
	/// �v���C���[�̃|�W�V������Ԃ��֐��B
	/// </summary>
	/// <returns></returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
private:
	void Move();						//�ړ��B
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W
};

