#include "stdafx.h"
#include "LevelSet.h"

#include "Map.h"
//エネミー
#include "Ghost.h"
#include "Bat.h"
#include "Slaim.h"


#include "TreasureBox.h"

#include "GameData.h"
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
		//ゴースト
		if (objData.EqualObjectName(L"ghosts")) {
			Ghost* m_ghost = g_goMgr->NewGameObject<Ghost>();
			m_ghost->SetPosition(objData.position);
			m_ghost->SetRotation(objData.rotation);
			m_ghost->SetScale(objData.scale);
			
			m_enemyCount++;

			return true;
		}
		//バット
		if (objData.EqualObjectName(L"bat")) {
			Bat* m_bat = g_goMgr->NewGameObject<Bat>();
			m_bat->SetPosition(objData.position);
			m_bat->SetRotation(objData.rotation);
			m_bat->SetScale(objData.scale);

			m_enemyCount++;

			return true;
		}
		if (objData.EqualObjectName(L"slaim")) {
			Slaim* m_slaim = g_goMgr->NewGameObject<Slaim>();
			m_slaim->SetPosition(objData.position);
			m_slaim->SetRotation(objData.rotation);
			m_slaim->SetScale(objData.scale);

			m_enemyCount++;

			return true;
		}
		if (objData.EqualObjectName(L"Treasure_Box")) {
		TreasureBox* m_treasurebox = g_goMgr->NewGameObject<TreasureBox>();
		m_treasurebox->SetPosition(objData.position);
		m_treasurebox->SetRotation(objData.rotation);
		m_treasurebox->SetScale(objData.scale);
		return true;
	}

		return false;
	});
	//敵の数をGameDataに教える
	GameData* m_gamedate = GameData::GetInstance();
	m_gamedate->SetEnemyCount(m_enemyCount);

}
void LevelSet::Update()
{

}
void LevelSet::Render()
{
	m_level.Draw();
}
