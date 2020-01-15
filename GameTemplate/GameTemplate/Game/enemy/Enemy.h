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
	/// ���W����ݒ�B
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
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
	void Return();
	void Dead(Player* player);

	SkinModel m_enemy;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W
	CVector3 m_oldPos = CVector3().Zero();			//���W
	CVector3 m_scale= CVector3().One();					//�g�嗦
	EState m_state = eState_Haikai;						//�G�̏�ԁB
	CVector3 p_pos = CVector3().Zero();
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���C���[�܂ŐL�тĂ���x�N�g���B
	AnimationClip  m_animClips[num];

	//�ړ��֘A
	int m_moveCount = 0;
	float m_moveSpeed = 0.6f;			//�G�l�~�̈ړ����x�B
	const float m_plFollow = 100.0f;	//�ǔ����鋗���B
	const float m_follSpeed = 0.7f;		//�ǔ����̈ړ����x�B
	const float m_tuisekiLength = 300.0f;		//�ǔ����鋗���B
	const float m_ReturnLength = 400.0f;		//�p�j�ʒu�ɖ߂鋗���B
};

