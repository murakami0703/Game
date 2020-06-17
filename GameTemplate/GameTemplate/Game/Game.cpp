#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"
#include "LevelSet.h"
#include "GameUI.h"
#include "Result.h"
#include "EffectManager.h"

#include "SiegePoint.h"


Game::Game()
{
	m_bgm.Init(L"Assets/sound/stage1_BGM.wav");
	m_bgm.Play(true);
}


Game::~Game()
{
}

bool Game::Start()
{
	
	g_goMgr->NewGameObject<EffectManager>();

	g_goMgr->NewGameObject<Player>();
	g_goMgr->NewGameObject<GameCamera>();
	g_goMgr->NewGameObject<GameData>();
	g_goMgr->NewGameObject<LevelSet>();
	g_goMgr->NewGameObject<GameUI>();


	g_goMgr->NewGameObject<SiegePoint>();

	return true;
}

void Game::Update() {


	GameData* m_gamedate = GameData::GetInstance();
	if (m_gamedate->GetEnemyCount() <= 0 && m_gamedate->ResultFlag() == true) {
		g_goMgr->SetMainSpriteMulColor({ 0.3f,0.3f, 0.3f, 1.0f });
		g_goMgr->NewGameObject<Result>();
		m_gamedate->SetResultFlag(false);
	}
}

