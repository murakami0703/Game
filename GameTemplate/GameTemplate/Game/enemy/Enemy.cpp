#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManeger.h"

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
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > m_follSpeed){
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * m_follSpeed;
	}
}

void Enemy::move()
{
	//�p�j��
	m_moveCount++;
	m_position.z += m_moveSpeed;
	//�㉺�p�j
	if (m_moveCount == 100) {
		m_moveSpeed = -m_moveSpeed;
	}
	if (m_moveCount == 200) {
		m_moveSpeed = m_moveSpeed;
		m_moveCount = 0;
	}
}
void Enemy::Return()
{
	//�p�j�ʒu�ɖ߂�B
	CVector3 diff = m_position - m_oldPos;
	diff.y = 0.0f;
	diff.Normalize();
	m_position += diff * m_moveSpeed;
	if (diff.Length() < 1.0f) {
		m_state = eState_Haikai;
	}
}
void Enemy::Dead(Player* player)
{
	//���S
	if (player->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 60.0f) {
			EnemyManager::GetInstance()->DeleteEnemy(this);
		}
	}
}

void Enemy::Update(Player* player)
{
	
	p_pos = player->GetPosition();
	m_toPlayerVec = p_pos - m_position;

	switch (m_state) {
	case eState_Haikai:
		//�p�j��
		move();
		if (m_toPlayerVec.Length() < m_tuisekiLength ) {
			m_battlePoint = EnemyManager::GetInstance()->TryGetBattlePoint(m_position);
			if(m_battlePoint!= nullptr){
				m_state = eState_TuisekiPlayer;
			}
		}
		break;
	case eState_TuisekiPlayer:
		//�v���C���[��ǐ�
		Follow(player);
		//�����Ȃ����̂Ŝp�j�ʒu�ɖ߂�
		if (m_toPlayerVec.Length() > m_ReturnLength) {
			m_state = eState_Haikai;
		}
		break;
	case eState_Return:
		//�p�j�ʒu�ɖ߂�
		Return();
	}
	Dead(player);
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