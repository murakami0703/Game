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
	void Move(Player* player);

private:
	SkinModel m_enemy;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W
	CVector3 m_scale= CVector3().One();					//�g�嗦

	AnimationClip  m_animClips[num];
};

