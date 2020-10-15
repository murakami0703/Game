#pragma once

/// <summary>
/// �G�l�~�[�@�F�@�������U��
/// </summary>

class Bat final : public IActor
{
public:
	Bat();
	~Bat();
	/// <summary>
	/// �������U��
	/// </summary>
	bool Start() override;
	void Update() override;

private:

	// ��ԁB
	enum EState {
		eState_Loitering,	//�p�j�B
		eState_Follow,		//�v���C���[��ǐՁB
		eState_Premove,		//�\������B
		eState_Attack,		//�U���B
		eState_Dead			//���B
	};

	//�A�j���[�V�����B
	enum EAnimationClip {
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Attack,
		eAnimation_Death,
		eAnimation_Num
	};

private:

	void Horizon();		//����p����

	void Loitering();	//�p�j�B
	void Follow();		//�v���C���[��ǐՁB
	void Premove();		//�\������B
	void Attack();		//�U���B
	void Dead();		//���B

private:

	//���ʎg�p�B
	EState m_state = eState_Loitering;					//��ԁB
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B
	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	int m_timer = 0;									//�^�C�}�[�B

	//�p�j�֌W�B
	int m_randRot = 0;									//�����̗����i�[�B
	CVector3 m_frontmove = CVector3().Zero();			//�����]�����̑O�x�N�g���i�[

	//�ǔ��֌W�B
	CVector3 m_toFollowEPVec = CVector3().Zero();		//�ǔ����̃v���C���[�Ƃ̋����x�N�g���̊i�[��

	//�U������B
	bool EneAttackflag = false;							//�U�����ł����H
};

