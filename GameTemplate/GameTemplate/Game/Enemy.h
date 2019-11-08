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
	void Draw(int renderMode);
	void Follow(Player* player);
	void move();

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
	CVector3 m_scale= CVector3().One();					//�g�嗦
	EState m_state = eState_Haikai;						//�G�̏�ԁB
	AnimationClip  m_animClips[num];
};

