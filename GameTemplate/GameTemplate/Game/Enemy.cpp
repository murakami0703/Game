#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	/*m_animClips[enewalk].Load(L"animData/Crowwalk.tka"); 
	m_animClips[enewalk].SetLoopFlag(true);*/
	//cmoファイルの読み込み。
	m_enemy.Init(L"Assets/modelData/enemy.cmo");
	m_position = { 0.0f,30.0f,0.0f };
	m_scale = { 5.0f,5.0f,5.0f };


}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//ワールド行列の更新。
	m_enemy.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
}
void Enemy::Draw()
{
	m_enemy.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}