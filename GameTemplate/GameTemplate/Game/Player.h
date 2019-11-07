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
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_move;	//�ړ�

	//PAnimation m_anime = Animation_Idel;		//�A�j���[�V�������
	Animation	m_animation;
	AnimationClip m_animClips[AnimationClip_Num];	//�A�j���[�V�����N���b�v
	CharacterController m_characon;		//�L�����R��
};

