#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{

	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemy.Init(L"Assets/modelData/enemy.cmo");
	m_position = { 0.0f,30.0f,0.0f };
	m_scale = { 5.0f,5.0f,5.0f };

}


Enemy::~Enemy()
{
}
void Enemy::Follow(Player* player)
{
	CVector3 p_pos = player->GetPosition();
	CVector3 diff = p_pos - m_position;
	if (diff.Length() >100.0f){
		diff.y = 0.0f;
		diff.Normalize();
		m_position += diff * 0.5f;
	}
}
void Enemy::Update(Player* player)
{
	CVector3 p_pos = player->GetPosition();
	CVector3 diff = p_pos - m_position;
	switch (m_state) {
	case eState_Haikai:
		//�p�j��
		if (diff.Length() < 300.0f) {
			m_state = eState_TuisekiPlayer;
		}
		break;
	case eState_TuisekiPlayer:
		//�v���C���[��ǐ�
		Follow(player);
		//�����Ȃ����̂Ŝp�j�ʒu�ɖ߂�
		if (diff.Length() > 400.0f) {
			m_state = eState_Return;
		}
		break;
	case eState_Return:
		//�p�j�ʒu�ɖ߂�
		m_state = eState_Haikai;
	}
	//���[���h�s��̍X�V�B
	m_enemy.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
	m_enemy.Update();

}
void Enemy::Draw(int renderMode)
{
	m_enemy.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}