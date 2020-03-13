#pragma once
#include "Player.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	enum enAnimationClip {
		enewalk,
		num
	};
	void Update(Player* player);
	void Draw(EnRenderMode renderMode);
	/// <summary>
	/// �G�l�~�[�̍��W��ݒ�B
	/// </summary>
	/// <returns>���W</returns>
	void Enemy::SetPosition(CVector3 pos) {
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

private:
	/// <summary>
	/// ���
	/// </summary>
	enum EState {
		eState_Haikai,			//�p�j��
		eState_TuisekiPlayer,	//�v���C���[��ǐՒ��B
		eState_Return	//�p�j�ʒu�ɖ߂�B
	};
	void Follow(Player* player);
	void move();


	SkinModel m_enemy;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W
	CQuaternion m_rotation = CQuaternion().Identity();		//��]
	CVector3 m_scale= CVector3().One();					//�g�嗦
	EState m_state = eState_Haikai;						//�G�̏�ԁB
	AnimationClip  m_animClips[num];
};

