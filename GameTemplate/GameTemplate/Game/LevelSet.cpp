#include "stdafx.h"
#include "LevelSet.h"

#include "Map.h"

LevelSet* LevelSet::m_instance = nullptr;
LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort();//すでに出ているためクラッシュ
	}
	m_instance = this;

	LevelSetting();
}


LevelSet::~LevelSet()
{
	m_instance = nullptr;
}

void LevelSet::LevelSetting()
{
	//levelで置きますわよ。
	m_level.Init(L"level/stage_00.tkl", [&](LevelObjectData& objData) {
		//ステージ
		if (objData.EqualObjectName(L"Floor")) {
			Map* m_map = g_goMgr.NewGameObject<Map>();
			m_map->SetPosition(objData.position);
			m_map->SetRotation(objData.rotation);
			m_map->SetScale(objData.scale);
			return true;
		}

		//エネミー

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
