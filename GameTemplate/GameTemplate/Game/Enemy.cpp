#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	//�A�j���[�V�����̍Đ��B
	m_animClips[enewalk].Load(L"Assets/animData/enemove.tka");
	m_animClips[enewalk].SetLoopFlag(true);

	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemy.Init(L"Assets/modelData/enemy.cmo");
	m_position = { 0.0f,30.0f,0.0f };
	m_scale = { 5.0f,5.0f,5.0f };

}


Enemy::~Enemy()
{
}
void Enemy::Move(Player* player)
{
	CVector3 p_pos = player->GetPosition();
	CVector3 diff = p_pos - m_position;
	if (diff.Length() >100.0f){
		diff.y = 0.0f;
		diff.Normalize();
		m_position += diff * 1.0f;
	}
}
void Enemy::Update(Player* player)
{
	Move(player);
	//���[���h�s��̍X�V�B
	m_enemy.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
	m_enemy.Update();

}
void Enemy::Draw()
{

	m_enemy.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}