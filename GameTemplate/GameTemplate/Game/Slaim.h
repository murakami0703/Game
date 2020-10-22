#pragma once
#include "character/CharacterController.h"

struct BattlePoint;
class Slaim final : public IActor
{
public:
	Slaim();
	~Slaim();
	/// <summary>
	/// �W�����v�U��
	/// </summary>
	
	bool Start();
	void Update();

	

private:

	// ���
	enum EState {
		eState_Idle,		//�ҋ@�B
		eState_Loitering,	//�p�j�B
		eState_Follow,		//�v���C���[��ǐՁB
		eState_Premove,		//�\������B
		eState_Premove2,	//�\������B
		eState_Attack,		//�U���B
		eState_Vertigo,		//῝�B
		eState_Dead			//���B
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

	void Idle();		//�ҋ@�B
	void Loitering();	//�p�j�B
	void Follow();		//�v���C���[��ǐՁB
	void Premove();		//�\������B
	void Premove2();	//�\������B
	void Attack();		//�U���B
	void Vertigo();		//῝�B
	void Dead();		//���B

private:

	SkinModelRender* m_enemyModelRender;				//�G�l�~�[�X�L�����f�������_�[�B
	SkinModelRender* m_enemyDeadModelRender;				//�G�l�~�[�X�L�����f�������_�[�B
	EState m_state = eState_Idle;					//��ԁB

	CharacterController m_characon;		//�L�����R��
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B
	AnimationClip  m_animClips2[eAnimation2_Num];
private:

	//���p
	CVector3 m_moveVec = CVector3().Zero();			//���W�B
	CVector3 m_setMoveVec = CVector3().Zero();
	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	CVector3 m_enemyForward = { 0.0f, 0.0f, 1.0f };			//�X���C���̑O�x�N�g���B

	float m_timer = 0;
	float timer1 = 0;
	//�ҋ@���
	float m_idleTime = 30.0f;				//�ҋ@���ԁB

	//�p�j���
	bool m_changeflag = true;				//�����]���B
	int m_randRot = 0;						//�����̗����i�[�B

	//�ǔ����

	bool m_modelChangeFlag = false;				//�����]���B
	//῝���
	int m_vertigoTimer = 0;



	bool EneAttackflag = false;					//�U�����ł����H
	bool m_battlePosflag = false;				//������BP�ɂ��܂����H
	BattlePoint* m_battlePoint = nullptr;		//�G�l�~�̃o�g���|�C���g��

};

