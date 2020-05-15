#pragma once
class Ghosts : public IGameObject
{
public:
	Ghosts();
	~Ghosts();

	void Update();
	void Render();
	void PostRender();

	/// <summary>
	/// ���W����ݒ�B
	/// </summary>
	void Ghosts::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void Ghosts::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void Ghosts::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// �G�l�~�̃|�W�V������Ԃ��֐��B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 Ghosts::GetPosition() {
		return m_position;
	}
	/// <summary>
	/// �U������
	/// </summary>
	/// <returns>true�Ȃ�U����</returns>
	bool Ghosts::GetAttackflag() {
		return EneAttackflag;
	}

	/// <summary>
	/// ���
	/// </summary>
	enum EState {
		eState_Haikai,			//�p�j��
		eState_TuisekiPlayer,	//�v���C���[��ǐՒ��B
		eState_Attack,		//�U�����܂��B
		eState_Return,	//�p�j�ʒu�ɖ߂�B
		eState_Dead	//��

	};

	enum enAnimationClip {
		Ghosts_walk,
		Ghosts_Attack,
		Ghosts_Dead,
		num
	};


	void Follow();	//�Ǐ]
	void move();	//�p�j
	void Attack();
	void Return();
	void Dead();

	SkinModelRender* m_enemy;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W
	CVector3 m_oldPos = CVector3().Zero();			//�������W
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_scale = CVector3().One();					//�g�嗦
	EState m_state = eState_Haikai;						//�G�̏�ԁB

	AnimationClip  m_animClips[num];			//�A�j���[�V�����N���b�v
	Animation	m_animation;					//�A�j���[�V����


	CVector3 p_pos = CVector3().Zero();
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B


		//�ړ��֘A
	int m_moveCount = 0;				//����p�J�E���g
	float m_moveSpeed = 0.6f;			//�G�l�~�̈ړ����x�B
	const float m_follSpeed = 1.9f;		//�ǔ����̈ړ����x�B
	const float m_tuisekiLength = 300.0f;		//�ǔ����鋗���B
	const float m_ReturnLength = 400.0f;		//�p�j�ʒu�ɖ߂鋗���B
	bool m_battlePosflag = false;				//������BP�ɂ��܂����H

	//BattlePoint* m_battlePoint = nullptr;		//�G�l�~�̃o�g���|�C���g��

	//�U���֘A
	bool EneAttackflag = false;						//�U������


};

