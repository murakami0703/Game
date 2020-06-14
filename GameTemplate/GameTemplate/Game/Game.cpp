#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "Ghost.h"
#include "GameData.h"
#include "LevelSet.h"
#include "GameUI.h"
#include "Result.h"
#include "EffectManager.h"

#include "SiegePoint.h"


Game::Game()
{

	g_goMgr->NewGameObject<GameCamera>();
	g_goMgr->NewGameObject<EffectManager>();

	g_goMgr->NewGameObject<Player>();
	g_goMgr->NewGameObject<GameData>();
	g_goMgr->NewGameObject<LevelSet>();
	g_goMgr->NewGameObject<GameUI>();
	g_goMgr->NewGameObject<Ghost>();


	g_goMgr->NewGameObject<SiegePoint>();
	
}


Game::~Game()
{
}

void Game::Update() {


	GameData* m_gamedate = GameData::GetInstance();
	if (m_gamedate->GetEnemyCount() >= 12 && m_gamedate->ResultFlag() == true) {
		g_goMgr->SetMainSpriteMulColor({ 0.3f,0.3f, 0.3f, 1.0f });
		g_goMgr->NewGameObject<Result>();
		m_gamedate->SetResultFlag(false);
	}
}

