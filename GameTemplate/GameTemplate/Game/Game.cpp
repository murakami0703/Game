#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"
#include "LevelSet.h"
#include "GameUI.h"
#include "Result.h"
#include "EffectManager.h"
#include "SoulManager.h"

#include "SiegePoint.h"
#include "GameOver.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::Start()
{
	//ループSE
	//m_bgm.Init(L"Assets/sound/stage1_BGM.wav");
	//m_bgm.Play(true);
	

	g_goMgr->NewGameObject<EffectManager>();
	g_goMgr->NewGameObject<SoulManager>();

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

	//敵を全部倒したのでリザルトへ
	if ( m_gamedate->ResultFlag() == true) {
		g_goMgr->SetMainSpriteMulColor({ 0.2f,0.2f, 0.2f, 1.0f });
		g_goMgr->NewGameObject<Result>();
		m_gamedate->SetResultFlag(false);
	}
	//プレイヤーのHPがなくなったのでGAMEOVERです。
	if (m_gamedate->GetHitPoint() <= 0.0f && m_gamedate->GameOverFlag() == false) {
		g_goMgr->NewGameObject<GameOver>();
		m_gamedate->SetGameOverFlag(true);

	}
}

