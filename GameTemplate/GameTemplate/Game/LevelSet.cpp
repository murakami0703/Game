#include "stdafx.h"
#include "LevelSet.h"

#include "Map.h"

LevelSet::LevelSet()
{
}


LevelSet::~LevelSet()
{
}

void LevelSet::LevelSetting()
{
	//level�Œu���܂����B
	m_level.Init(L"level/level_00.tkl", [&](LevelObjectData& objData) {
		//�X�e�[�W
		if (objData.EqualObjectName(L"bunbo-gu0")) {
			Map* m_map = new Map;
			m_map->SetPosition(objData.position);
			m_map->SetRotation(objData.rotation);
			return true;
		}

		//�G�l�~�[

		return false;
	});

}
