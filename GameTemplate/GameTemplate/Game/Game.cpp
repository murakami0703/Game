#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "player/Player.h"
#include "data/GameData.h"
#include "stage/LevelSet.h"
#include "ui/GameUI.h"
#include "scene/Result.h"
#include "manager/EffectManager.h"
#include "manager/SoulManager.h"

#include "siegepoint/SiegePoint.h"
#include "scene/GameOver.h"


Game::Game()
{
}


Game::~Game()
{
}

bool Game::Start()
{

	m_titleBgm = g_goMgr->NewGameObject<CSoundSource>();
	m_titleBgm->Init(L"Assets/sound/stage1BGM.wav");
	m_titleBgm->SetVolume(0.3f);
	m_titleBgm->Play(true);

	g_goMgr->NewGameObject<EffectManager>();
	g_goMgr->NewGameObject<SoulManager>();

	g_goMgr->NewGameObject<Player>();
	g_goMgr->NewGameObject<GameCamera>();
	g_goMgr->NewGameObject<GameData>();
	g_goMgr->NewGameObject<LevelSet>();
	g_goMgr->NewGameObject<GameUI>();


	g_goMgr->NewGameObject<SiegePoint>();
	g_goMgr->SetGameFlag(true);
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

