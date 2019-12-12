#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{

	//cmo�t�@�C���̓ǂݍ��݁B
	m_enemy.Init(L"Assets/modelData/enemy.cmo");
	m_oldPos = m_position;
	m_scale = { 5.0f,5.0f,5.0f };

}


Enemy::~Enemy()
{
}
void Enemy::Follow(Player* player)
{
	//�ǔ�����
	CVector3 p_pos = player->GetPosition();
	CVector3 diff = p_pos - m_position;
	if (diff.Length() >100.0f){
		diff.y = 0.0f;
		diff.Normalize();
		m_position += diff * 0.5f;
	}
}

void Enemy::move()
{
	//�p�j��
	m_moveCount++;
	m_position.z += m_move;
	if (m_moveCount == 100) {
		m_move = -0.6f;
	}
	if (m_moveCount == 200) {
		m_move = 0.6f;
		m_moveCount = 0;
	}
}
void Enemy::Return()
{
	//�p�j�ʒu�ɖ߂�B
	/*CVector3 diff = m_position - m_oldPos;
	diff.y = 0.0f;
	diff.Normalize();
	m_position += diff * 0.7f;
	if (diff.Length() < 1.0f) {
		m_state = eState_Haikai;
	}*/
}
void Enemy::Dead()
{
}

void Enemy::Update(Player* player)
{
	CVector3 p_pos = player->GetPosition();
	CVector3 diff = p_pos - m_position;
	switch (m_state) {
	case eState_Haikai:
		//�p�j��
		move();
		if (diff.Length() < 300.0f) {
			m_state = eState_TuisekiPlayer;
		}
		break;
	case eState_TuisekiPlayer:
		//�v���C���[��ǐ�
		Follow(player);
		//�����Ȃ����̂Ŝp�j�ʒu�ɖ߂�
		if (diff.Length() > 400.0f) {
			m_state = eState_Haikai;
		}
		break;
	case eState_Return:
		//�p�j�ʒu�ɖ߂�
		Return();
	}
	Dead();
	//���[���h�s��̍X�V�B
	m_enemy.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
	m_enemy.Update();

}
void Enemy::Draw(EnRenderMode m_renderMode)
{
	m_enemy.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		m_renderMode
	);
}