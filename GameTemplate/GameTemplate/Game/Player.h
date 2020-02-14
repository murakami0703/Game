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
		Animation_Dead,
		AnimationClip_Num
	};

	enum EState {
		Player_Idle,
		Player_Walk,
		Player_Attack,
		Player_Dead
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
	/// <summary>
	/// �U������
	/// </summary>
	/// <returns>true�Ȃ�U����</returns>
	bool Player::GetAttackflag() {
		return attackflag;
	}
private:
	void Idel();
	void Move();						//�ړ��B
	void Attack();
	void Dead();

	SkinModel m_model;		//�X�L�����f��
	CVector3 m_position = CVector3().Zero();			//���W
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_scale = CVector3().One();			//�g�嗦
	CVector3 m_move;	//�ړ�
	CharacterController m_characon;		//�L�����R��
	EState m_state = Player_Idle;
	//�ړ��֘A
	float m_movespeed = 200.0f;			//�ړ����x
	const float m_rotationLR = 80.0f;	//���E�̉�]�p�x
	const float m_rotationD = 110.0f;	//���̉�]�p�x
	float m_caraTime = (1.0f / 60.0f);	//�L�����R���̌o�ߎ���
	const float m_jumpPos = 50.0f;		//�W�����v�̍���
	//Animation�֘A
	int Atcount = 0;	//�U���񐔔���p�B
	PAnimation m_anime = Animation_Idel;		//�A�j���[�V�������
	Animation	m_animation;					//�A�j���[�V����
	AnimationClip m_animClips[AnimationClip_Num];	//�A�j���[�V�����N���b�v

	//�U���֘A
	bool attackflag = false;	//�U������p�B
};

