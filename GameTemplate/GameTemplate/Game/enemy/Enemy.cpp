#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManeger.h"
Enemy::Enemy()
{

	//cmoファイルの読み込み。
	m_enemy.Init(L"Assets/modelData/enemy.cmo");
	m_oldPos = m_position;
	m_scale = { 5.0f,5.0f,5.0f };

}


Enemy::~Enemy()
{
}
void Enemy::Follow(Player* player)
{
	//追尾ちゅ
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > m_follSpeed){
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * m_follSpeed;
	}
}

void Enemy::move()
{
	//徘徊中
	m_moveCount++;
	m_position.z += m_moveSpeed;
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
	//徘徊位置に戻る。
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
		//徘徊中
		move();
		if (m_toPlayerVec.Length() < m_tuisekiLength ) {
			m_battlePoint = EnemyManager::GetInstance()->TryGetBattlePoint(m_position);
			if(m_battlePoint!= nullptr){
				m_state = eState_TuisekiPlayer;
			}
		}
		break;
	case eState_TuisekiPlayer:
		//プレイヤーを追跡
		Follow(player);
		//遠くなったので徘徊位置に戻る
		if (m_toPlayerVec.Length() > m_ReturnLength) {
			m_state = eState_Haikai;
		}
		break;
	case eState_Return:
		//徘徊位置に戻る
		Return();
	}
	Dead(player);
	//ワールド行列の更新。
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