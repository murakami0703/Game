#pragma once
#include "character/CharacterController.h"

class BattlePoint;
class Slaim : public IGameObject
{
public:
	Slaim();
	~Slaim();
	/// <summary>
	/// �W�����v�U��
	/// </summary>
	void Update();

private:

	// ���
	enum EState {
		eState_Idle,	//�ҋ@�B
		eState_Loitering,	//�p�j�B
		eState_Follow,		//�v���C���[��ǐՁB
		eState_Premove,		//�\������B
		eState_Premove2,		//�\������B
		eState_Attack,		//�U���B
		eState_Vertigo,		//῝�B
		eState_Return,	//�p�j�ʒu�ɖ߂�B
		eState_Dead	//���B
	};

	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Premove2,
		eAnimation_Attack,
		eAnimation_Vertigo,
		eAnimation_Death,
		eAnimation_Num
	};

private:

	void Idle();	//�ҋ@�B
	void Loitering();	//�p�j�B
	void Follow();		//�v���C���[��ǐՁB
	void Premove();		//�\������B
	void Premove2();		//�\������B
	void Attack();		//�U���B
	void Vertigo();	//῝�B
	void Return();		//�p�j�ʒu�ɖ߂�B
	void Dead();		//���B

private:

	SkinModelRender* m_enemyModelRender;				//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3().Zero();			//���W�B
	CVector3 m_oldPos = CVector3().Zero();				//�������W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B
	CharacterController m_characon;		//�L�����R��

	EState m_state = eState_Idle;					//��ԁB
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B

private:
	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B

	//�ړ��֘A
	int m_moveCount = 0;						//����p�J�E���g
	float m_moveSpeed = 0.6f;					//�G�l�~�̈ړ����x�B
	const float m_follSpeed = 3.0f;				//�ǔ����̈ړ����x�B
	const float m_tuisekiLength = 300.0f;		//�ǔ����鋗���B
	const float m_ReturnLength = 1000.0f;		//�p�j�ʒu�ɖ߂鋗���B

	bool m_battlePosflag = false;				//������BP�ɂ��܂����H
	BattlePoint* m_battlePoint = nullptr;		//�G�l�~�̃o�g���|�C���g��
	float a = 60.0f;
	float timer = 0;


	CVector3 moveVec = CVector3().Zero();			//���W�B
	float m_caraTime = (1.0f / 60.0f);		//�L�����R���̌o�ߎ���

	CVector3 walkmove = CVector3().Zero();		// ���W�B
	int count = 0;							//�ړ��p�J�E���g
	int wrandom = 0;						//�ړ��̕�������
	const int randomCount = 120;			//�����_���ňړ������؂�ւ��^�C�}�[
	const float randomSpeed = 120.0f;			//�ړ����x
	bool flag = true;
	bool flag1 = true;
	int timer1 = 0;
	int timer2 = 0;

	CVector3 dddd= CVector3().Zero();
	CVector3 walk1move = CVector3().Zero();		// ���W�B

	bool EneAttackflag = false;					//�U�����ł����H

};

