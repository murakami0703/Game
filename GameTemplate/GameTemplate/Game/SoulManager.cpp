#include "stdafx.h"
#include "SoulManager.h"
#include "Anima.h"

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
	Anima* m_anima = g_goMgr->NewGameObject<Anima>();
	m_anima->SetPosition(position);
}

