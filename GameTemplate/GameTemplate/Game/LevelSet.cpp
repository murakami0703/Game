#include "stdafx.h"
#include "LevelSet.h"

#include "Map.h"
//�G�l�~�[
#include "enemy/Enemy.h"

LevelSet* LevelSet::m_instance = nullptr;
LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort();//���łɏo�Ă��邽�߃N���b�V��
	}
	m_instance = this;

	//���x���Z�b�g
	LevelSetting();
}


LevelSet::~LevelSet()
{
	m_instance = nullptr;
}

void LevelSet::LevelSetting()
{
	//level�Œu���܂����B
	m_level.Init(L"Assets/level/stage_02.tkl", [&](LevelObjectData& objData) {
		//�X�e�[�W
		if (objData.EqualObjectName(L"Floor")) {
			Map* m_map = g_goMgr->NewGameObject<Map>();
			m_map->SetPosition(objData.position);
			m_map->SetRotation(objData.rotation);
			m_map->SetScale(objData.scale);
			return true;
		}
		//�X���C��
		if (objData.EqualObjectName(L"ghosts")) {
			Enemy* m_enemy = g_goMgr->NewGameObject<Enemy>();
			m_enemy->SetPosition(objData.position);
			m_enemy->SetRotation(objData.rotation);
			m_enemy->SetScale(objData.scale);
			return true;
		}

		return false;
	});

}
void LevelSet::Update()
{

}
void LevelSet::Render()
{
	m_level.Draw();
}
void LevelSet::PostRender(){}
