#pragma once
#include "character/CharacterController.h"

class BattlePoint;
class Ghost : public IGameObject
{
public:
	Ghost();
	~Ghost();
	bool Start();

	void Update();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void Ghost::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void Ghost::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void Ghost::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

	/// <summary>
	/// �G�l�~�̃|�W�V������Ԃ��֐��B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 Ghost::GetPosition() {
		return m_position;
	}

	/// <summary>
	/// �U������
	/// </summary>
	/// <returns>true�Ȃ�U����</returns>
	bool Ghost::GetAttackflag() {
		return EneAttackflag;
	}

private:

	// ���
	enum EState {
		eState_Idle,	//�ҋ@�B
		eState_Loitering,	//�p�j�B
		eState_Follow,		//�v���C���[��ǐՁB
		eState_Premove,		//�U���B
		eState_Attack,		//�U���B
		eState_Dead			//���B

	};

	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Death,
		eAnimation_Num
	};

private:
	void Horizon();		//����p����

	void Idle();	//�ҋ@�B
	void Loitering();	//�p�j�B
	void Follow();		//�v���C���[��ǐՁB
	void Premove();		//�\������B
	void Attack();		//�U���B
	void Dead();		//���B

private:
	SkinModelRender* m_enemyModelRender;				//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3().Zero();			//���W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B
	EState m_state = eState_Loitering;					//��ԁB

	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B

	//���p
	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	CVector3 m_enemyForward = { 0.0f, 0.0f, -1.0f };			//�S�[�X�g�̑O�x�N�g���B

	float m_timer = 0;
	const float m_followLength = 500.0f;	//�ǐՂ��n�߂鋗���B

	//����p�֘A
	const float horilong = 500.0f;	//����p����̋���
	const float horiAngle = 90.0f;	//����p����̊p�x

	//�ҋ@�֘A
	float m_idleTime = 30.0f;		//�ҋ@���ԁB

	//�p�j�֘A
	const int m_randTimer = 120;			//�����]�����鎞�ԁB
	int m_randRot = 0;						//�����̗����i�[�B
	const float m_loiteringSpeed = 120.0f;	//�p�j���x�B

	//�ǔ��֘A

	//�ړ��֘A
	int m_moveCount = 0;						//����p�J�E���g
	float m_moveSpeed = 0.6f;					//�G�l�~�̈ړ����x�B
	const float m_follSpeed = 3.0f;				//�ǔ����̈ړ����x�B
	const float m_tuisekiLength = 300.0f;		//�ǔ����鋗���B
	const float m_ReturnLength = 1000.0f;		//�p�j�ʒu�ɖ߂鋗���B

	bool m_battlePosflag = false;				//������BP�ɂ��܂����H
	BattlePoint* m_battlePoint = nullptr;		//�G�l�~�̃o�g���|�C���g��
	//�U������
	bool EneAttackflag = false;					//�U�����ł����H

	CVector3 walkmove = CVector3().Zero();		// ���W�B
	int count = 0;							//�ړ��p�J�E���g
	int wrandom = 0;						//�ړ��̕�������
	const int randomCount = 120;			//�����_���ňړ������؂�ւ��^�C�}�[
	const float randomSpeed = 2.0f;			//�ړ����x

	CVector3 moveVec = CVector3().Zero();			//���W�B
	float m_caraTime = (1.0f / 60.0f);		//�L�����R���̌o�ߎ���
	bool flag = true;
	float timer = 0;
	float timer1 = 0;	
	bool baund = true;

	CVector3 dff = CVector3().Zero();

};

