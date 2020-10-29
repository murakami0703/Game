#include "stdafx.h"
#include "manager/SoulManager.h"
#include "soul/Soul.h"

SoulManager* SoulManager::m_instance = nullptr;

SoulManager::SoulManager()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
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
	//Soul����
	Soul* m_soul = g_goMgr->NewGameObject<Soul>();
	m_soul->SetPosition(position);
}

