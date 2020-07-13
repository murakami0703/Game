#pragma once

class Bat : public IGameObject
{
public:
	Bat();
	~Bat();
	/// <summary>
	/// �������U��
	/// </summary>
	bool Start();
	void Update();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void Bat::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void Bat::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void Bat::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

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

	SkinModelRender* m_enemyModelRender;				//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3().Zero();			//���W�B
	CVector3 m_oldPos = CVector3().Zero();				//�������W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B

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

