#include "stdafx.h"
#include "manager/SoulManager.h"
#include "soul/Soul.h"

SoulManager* SoulManager::m_instance = nullptr;

SoulManager::SoulManager()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


SoulManager::~SoulManager()
{
}


bool SoulManager::Start()
{
	return true;
}
void SoulManager::Update() {}

void SoulManager::SoulGenerated(CVector3 position)
{
	//Soul生成
	Soul* m_soul = g_goMgr->NewGameObject<Soul>();
	m_soul->SetPosition(position);
}

