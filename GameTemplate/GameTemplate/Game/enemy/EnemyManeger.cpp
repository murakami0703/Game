#include "stdafx.h"
#include "EnemyManeger.h"
#include "Enemy.h"

EnemyManager* EnemyManager::m_instance = nullptr;

EnemyManager::EnemyManager()
{
	m_instance = this;
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update(Player* player)
{
	for (auto& en : m_enemys) {
		en->Update(player);
	}
	
}
void EnemyManager::Draw(EnRenderMode renderMode)
{
	for (auto& en : m_enemys) {
		en->Draw(renderMode);
	}
}