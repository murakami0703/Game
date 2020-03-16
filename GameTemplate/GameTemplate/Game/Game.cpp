#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "GameData.h"
#include "LevelSet.h"
#include "GameUI.h"

Camera2D g_camera2D;	//2DƒJƒƒ‰

Game::Game()
{
	g_goMgr->NewGameObject<GameCamera>();

	g_goMgr->NewGameObject<Player>();
	g_goMgr->NewGameObject<GameData>();
	g_goMgr->NewGameObject<LevelSet>();
	g_goMgr->NewGameObject<GameUI>();

}


Game::~Game()
{
}

void Game::Update() {

}
void Game::Render(){}
void Game::PostRender(){}

