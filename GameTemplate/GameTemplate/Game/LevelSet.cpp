#include "stdafx.h"
#include "LevelSet.h"

#include "Map.h"
//エネミー
#include "enemy/Enemy.h"

LevelSet* LevelSet::m_instance = nullptr;
LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort();//すでに出ているためクラッシュ
	}
	m_instance = this;

	//レベルセット
	LevelSetting();
}


LevelSet::~LevelSet()
{
	m_instance = nullptr;
}

void LevelSet::LevelSetting()
{
	//levelで置きますわよ。
	m_level.Init(L"Assets/level/stage_02.tkl", [&](LevelObjectData& objData) {
		//ステージ
		if (objData.EqualObjectName(L"Floor")) {
			Map* m_map = g_goMgr->NewGameObject<Map>();
			m_map->SetPosition(objData.position);
			m_map->SetRotation(objData.rotation);
			m_map->SetScale(objData.scale);
			return true;
		}
		//スライム
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
