#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "Bat.h"
#include "GameData.h"
#include "LevelSet.h"
#include "GameUI.h"
#include "Result.h"

#include "SiegePoint.h"


Game::Game()
{

	g_goMgr->NewGameObject<GameCamera>();
	g_goMgr->NewGameObject<Player>();
	g_goMgr->NewGameObject<GameData>();
	g_goMgr->NewGameObject<LevelSet>();
	g_goMgr->NewGameObject<GameUI>();
	g_goMgr->NewGameObject<Bat>();


	g_goMgr->NewGameObject<SiegePoint>();
	
}


Game::~Game()
{
}

void Game::Update() {

	GameData* m_gamedate = GameData::GetInstance();
	if (m_gamedate->GetEnemyCount() <= 0 && m_gamedate->ResultFlag() == true) {
			g_goMgr->NewGameObject<Result>();
			m_gamedate->SetResultFlag(false);
	}
}

