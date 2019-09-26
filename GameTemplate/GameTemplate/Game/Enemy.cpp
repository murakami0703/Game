#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	/*m_animClips[enewalk].Load(L"animData/Crowwalk.tka"); 
	m_animClips[enewalk].SetLoopFlag(true);*/
	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemy.Init(L"Assets/modelData/enemy.cmo");
	m_position = { 0.0f,30.0f,0.0f };
	m_scale = { 5.0f,5.0f,5.0f };


}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//���[���h�s��̍X�V�B
	m_enemy.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
}
void Enemy::Draw()
{
	m_enemy.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}