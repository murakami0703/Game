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
	void Follow(Player* player);
	void move();
	void Return();

private:
	/// <summary>
	/// ���
	/// </summary>
	enum EState {
		eState_Haikai,			//�p�j��
		eState_TuisekiPlayer,	//�v���C���[��ǐՒ��B
		eState_Return	//�p�j�ʒu�ɖ߂�B
	};
	SkinModel m_enemy;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W
	CVector3 m_oldPos = CVector3().Zero();			//���W
	CVector3 m_scale= CVector3().One();					//�g�嗦
	EState m_state = eState_Haikai;						//�G�̏�ԁB

	int m_moveCount = 0;
	float m_move = 0.6f;

	AnimationClip  m_animClips[num];
};

