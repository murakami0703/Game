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
		Animation_Attack1,
		Animation_Attack2,
		AnimationClip_Num
	};

	void Update();
	void Draw(EnRenderMode renderMode);
	/// <summary>
	/// �v���C���[�̃|�W�V������Ԃ��֐��B
	/// </summary>
	/// <returns></returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
	SkinModel* GetPlayerSkinModel() {
		return &m_model;
	}
private:
	void Move();						//�ړ��B
	void PlAnimation();//�A�j���[�V����
	SkinModel m_model;		//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3().Zero();			//���W
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_scale = CVector3().One();			//�g�嗦
	CVector3 m_move;	//�ړ�
	int Atcount = 0;
	PAnimation m_anime = Animation_Idel;		//�A�j���[�V�������
	Animation	m_animation;
	AnimationClip m_animClips[AnimationClip_Num];	//�A�j���[�V�����N���b�v
	CharacterController m_characon;		//�L�����R��
};

