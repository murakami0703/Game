#pragma once

class BattlePoint;
class Ghost : public IGameObject
{
public:
	Ghost();
	~Ghost();

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
		eState_Loitering,	//�p�j�B
		eState_Follow,		//�v���C���[��ǐՁB
		eState_Attack,		//�U���B
		eState_Return,		//�p�j�ʒu�ɖ߂�B
		eState_Dead			//���B

	};

	enum EAnimationClip {
		eAnimation_Walk,
		eAnimation_Attack,
		eAnimation_Death,
		eAnimation_Num
	};

private:
	void Loitering();	//�p�j�B
	void Follow();		//�v���C���[��ǐՁB
	void Attack();		//�U���B
	void Return();		//�p�j�ʒu�ɖ߂�B
	void Dead();		//���B

private:
	SkinModelRender* m_enemyModelRender;				//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3().Zero();			//���W�B
	CVector3 m_oldPos = CVector3().Zero();				//�������W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B

	EState m_state = eState_Loitering;					//��ԁB
	CVector3 m_playerPos = CVector3().Zero();			//�v���C���[�̍��W�B
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B

	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B

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

};

