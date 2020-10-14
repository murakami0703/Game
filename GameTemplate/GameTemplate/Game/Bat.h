#pragma once

class Bat : public IActor
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
	// ���
	enum EState {
		eState_Loitering,	//�p�j�B
		eState_Follow,		//�v���C���[��ǐՁB
		eState_Premove,		//�\������B
		eState_Attack,		//�U���B
		eState_Dead	//���B
	};

	enum EAnimationClip {
		eAnimation_Walk,
		eAnimation_Premove,
		eAnimation_Attack,
		eAnimation_Death,
		eAnimation_Num
	};

private:

	void Loitering();	//�p�j�B
	void Follow();		//�v���C���[��ǐՁB
	void Premove();		//�\������B
	void Attack();		//�U���B
	void Dead();		//���B

private:

	CVector3 m_position = CVector3().Zero();			//���W�B

	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B

	EState m_state = eState_Loitering;					//��ԁB
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B
	
	//�ړ��֘A
	const float m_toPlyaerLength = 250.0f;	//�Ǐ]����
	const float m_returnLength = 800.0f;	//�Ǐ]��Ԃ���p�j��Ԃɖ߂鋗��

	//�U������
	bool EneAttackflag = false;					//�U�����ł����H

	CVector3 moveVec = CVector3().Zero();			//���W�B
	float m_caraTime = (1.0f / 60.0f);		//�L�����R���̌o�ߎ���

	int m_timer = 0;
};

