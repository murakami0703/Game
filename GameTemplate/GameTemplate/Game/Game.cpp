#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "GameData.h"
#include "LevelSet.h"
#include "GameUI.h"

#include "Map.h"

Camera2D g_camera2D;	//2Dカメラ

Game::Game()
{
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	//2Dカメラを初期化。
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	//ビューボリュームの幅と高さを指定する。
	g_camera2D.SetViewVolumeHeight(FRAME_BUFFER_H);
	g_camera2D.SetViewVolumeWidth(FRAME_BUFFER_W);

	g_goMgr->NewGameObject<GameCamera>();

	g_goMgr->NewGameObject<Player>();
	g_goMgr->NewGameObject<GameData>();
	g_goMgr->NewGameObject<Map>();
	g_goMgr->NewGameObject<GameUI>();

}


Game::~Game()
{
}

void Game::Update() {

}
void Game::Render(){}
void Game::PostRender(){}

