#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

	enum enAnimationClip {
		enewalk,
		num
	};
	void Update();
	void Draw();
private:
	SkinModel m_enemy;									//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W
	CVector3 m_scale= CVector3().One();					//�g�嗦

	//CAnimationClip  m_animClips[enewalk];
};

