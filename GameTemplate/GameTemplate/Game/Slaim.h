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
	
	bool Start();
	void Update();

	/// <summary>
/// ���W��ݒ�B
/// </summary>
	void Slaim::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void Slaim::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void Slaim::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

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
		eAnimation_Num
	};
	enum EAnimationClip2 {
		eAnimation2_Death,
		eAnimation2_Num
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

	SkinModelRender* m_enemyModelRender;				//�G�l�~�[�X�L�����f�������_�[�B
	SkinModelRender* m_enemyDeadModelRender;				//�G�l�~�[�X�L�����f�������_�[�B
	CVector3 m_position = CVector3().Zero();			//���W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B
	EState m_state = eState_Idle;					//��ԁB

	CharacterController m_characon;		//�L�����R��
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B
	AnimationClip  m_animClips2[eAnimation2_Num];
private:

	//���p
	CVector3 moveVec = CVector3().Zero();			//���W�B
	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	CVector3 m_enemyForward = { 0.0f, 0.0f, 1.0f };			//�X���C���̑O�x�N�g���B

	float m_timer = 0;
	//�ҋ@�֘A
	float m_idleTime = 30.0f;				//�ҋ@���ԁB

	//�p�j�֘A
	bool m_changeflag = true;				//�����]���B
	const int m_randTimer = 120;			//�����]�����鎞�ԁB
	int m_randRot = 0;						//�����̗����i�[�B
	const float m_followLength = 300.0f;	//�ǐՂ��n�߂鋗���B
	const float m_loiteringSpeed = 120.0f;	//�p�j���x�B

	//�ǔ��֘A
	const float m_toBPPos = 100.0f;			//�\������J�n�����B
	const float m_followSpeed = 250.0f;		//�p�j���x�B
	const float m_loiteringLength = 500.0f;	//�p�j�ɖ߂鋗���B

	bool m_modelflag = false;				//�����]���B




	int m_moveCount = 0;						//����p�J�E���g
	float m_moveSpeed = 0.6f;					//�G�l�~�̈ړ����x�B
	const float m_follSpeed = 1000.0f;				//�ǔ����̈ړ����x�B
	const float m_tuisekiLength = 300.0f;		//�ǔ����鋗���B
	const float m_ReturnLength = 1000.0f;		//�p�j�ʒu�ɖ߂鋗���B

	bool m_battlePosflag = false;				//������BP�ɂ��܂����H
	BattlePoint* m_battlePoint = nullptr;		//�G�l�~�̃o�g���|�C���g��
	float a = 60.0f;
	float timer = 0;


	float m_caraTime = (1.0f / 60.0f);		//�L�����R���̌o�ߎ���

	int count = 0;							//�ړ��p�J�E���g
	int wrandom = 0;						//�ړ��̕�������
	const int randomCount = 120;			//�����_���ňړ������؂�ւ��^�C�}�[
	const float randomSpeed = 300.0f;			//�ړ����x
	bool flag = true;
	bool flag1 = true;
	int timer1 = 0;
	int timer2 = 0;
	float ko = 0;

	CVector3 dddd= CVector3().Zero();
	CVector3 walk1move = CVector3().Zero();		// ���W�B

	bool EneAttackflag = false;					//�U�����ł����H

};

