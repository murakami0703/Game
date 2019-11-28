#pragma once
#include "character/CharacterController.h"
#include "ShadowMap.h"

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
	/// <returns>���W</returns>
	CVector3 Player::GetPosition() {
		return m_position;
	}
	/// <summary>
	/// �v���C���[�̃��f�����擾�B
	/// </summary>
	/// <returns>�v���C���[�̃X�L�����f��</returns>
	SkinModel* GetPlayerSkinModel() {
		return &m_model;
	}

private:
	void Move();						//�ړ��B
	void PlAnimation();//�A�j���[�V����

	SkinModel m_model;		//�X�L�����f��
	CVector3 m_position = CVector3().Zero();			//���W
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_scale = CVector3().One();			//�g�嗦
	CVector3 m_move;	//�ړ�
	CharacterController m_characon;		//�L�����R��

	//Animation�֘A
	int Atcount = 0;	//�U���񐔔���p�B
	PAnimation m_anime = Animation_Idel;		//�A�j���[�V�������
	Animation	m_animation;					//�A�j���[�V����
	AnimationClip m_animClips[AnimationClip_Num];	//�A�j���[�V�����N���b�v
};

