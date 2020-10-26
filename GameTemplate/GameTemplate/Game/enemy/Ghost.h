#pragma once

struct BattlePoint;
class Ghost final : public IActor
{
public:
	Ghost();
	~Ghost();
	bool Start() override;
	void Update() override;
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

	//�A�j���V�����B
	enum EAnimationClip {
		eAnimation_Idle,
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Death,
		eAnimation_Num
	};

private:
	void Horizon();		//����p����

	void Idle();		//�ҋ@�B
	void Loitering();	//�p�j�B
	void Follow();		//�v���C���[��ǐՁB
	void Premove();		//�\������B
	void Attack();		//�U���B
	void Dead();		//���B

private:

	//���p
	EState m_state = eState_Loitering;					//��ԁB
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B
	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	int m_timer = 0;									//�^�C�}�[�B

	//�o�g���|�C���g�֌W�B
	bool m_battlePosflag = false;				//������BP�ɂ��܂����H
	BattlePoint* m_battlePoint = nullptr;		//�G�l�~�̃o�g���|�C���g��



	//�ҋ@�֘A
	float m_idleTime = 30.0f;		//�ҋ@���ԁB

	//�p�j�֘A
	const int m_randTimer = 120;			//�����]�����鎞�ԁB
	int m_randRot = 0;						//�����̗����i�[�B
	CVector3 m_frontmove = CVector3().Zero();			//�����]�����̑O�x�N�g���i�[
	const float m_loiteringSpeed = 2.0f;	//�p�j���x�B

	//���S�֘A
	const float m_deadLength = 150.0f;						//���S����̋���
	const CVector3 m_smallValue = { 0.05f, 0.05f, 0.05f };	//���S��1�t���[�����ɏk��������l
	//Soul�֘A
	const float m_soulSetYPos = 430.0f;			//����������Y���W�̈ʒu
	//�G�t�F�N�g�֘A
	const float m_effectEneDeadYPos = 420.0f;						//���S���Đ������G�t�F�N�g��Y���W�̈ʒu
	const CVector3 m_effectEneDeadSca = { 20.0f, 20.0f, 20.0f };	//���S���Đ������G�t�F�N�g�̊g�嗦�B

	int timer1 = 0;
	CVector3 dff = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	bool baund = true;					//�U�����ł����H

	//�U������
	bool EneAttackflag = false;					//�U�����ł����H
};

