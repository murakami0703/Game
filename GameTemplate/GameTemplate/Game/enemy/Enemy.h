#pragma once
#include "Player.h"
//class BattlePoint;


class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	enum enAnimationClip {
		eneidle,
		enewalk,
		eneAttack_1,
		eneDead,
		num
	};
	void Update();
	void Render();
	/// <summary>
	/// ���W����ݒ�B
	/// </summary>
	void Enemy::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void Enemy::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]����ݒ�B
	/// </summary>
	void Enemy::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}

	/// <summary>
	/// �G�l�~�̃|�W�V������Ԃ��֐��B
	/// </summary>
	/// <returns>���W</returns>
	CVector3 Enemy::GetPosition() {
		return m_position;
	}
	/// <summary>
	/// �U������
	/// </summary>
	/// <returns>true�Ȃ�U����</returns>
	bool Enemy::GetAttackflag() {
		return EneAttackflag;
	}

private:
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

	void Follow();
	void move();
	void Attack();
	void Return();
	void Dead();

	SkinModelRender* m_enemy;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W
	CVector3 m_oldPos = CVector3().Zero();			//���W
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_scale= CVector3().One();					//�g�嗦
	EState m_state = eState_Haikai;						//�G�̏�ԁB
	CVector3 p_pos = CVector3().Zero();
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	AnimationClip  m_animClips[num];

	//�ړ��֘A
	int m_moveCount = 0;				//����p�J�E���g
	float m_moveSpeed = 0.6f;			//�G�l�~�̈ړ����x�B
	const float m_follSpeed = 1.9f;		//�ǔ����̈ړ����x�B
	const float m_tuisekiLength = 300.0f;		//�ǔ����鋗���B
	const float m_ReturnLength = 400.0f;		//�p�j�ʒu�ɖ߂鋗���B
	Animation	m_animation;					//�A�j���[�V����
	bool m_battlePosflag = false;				//������BP�ɂ��܂����H

	//BattlePoint* m_battlePoint = nullptr;		//�G�l�~�̃o�g���|�C���g��
	//�U������
	bool EneAttackflag = false;

	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
	ID3D11ShaderResourceView* g_specularMapSRV = nullptr;
	ID3D11ShaderResourceView* g_ambientMapSRV = nullptr;
};

