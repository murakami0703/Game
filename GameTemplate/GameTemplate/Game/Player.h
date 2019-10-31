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
	/// �v���C���[�̃|�W�V������Ԃ��֐��B
	/// </summary>
	/// <returns></returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
private:
	void Move();						//�ړ��B
	SkinModel m_model;		//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3().Zero();			//���W
	Animation m_anime = Animation_Idel;
	CharacterController m_characon;		//�L�����R��
};

