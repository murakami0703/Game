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
	SkinModel m_enemy;									//スキンモデル。
	CVector3 m_position = CVector3().Zero();			//座標
	CVector3 m_scale= CVector3().One();					//拡大率

	//CAnimationClip  m_animClips[enewalk];
};

