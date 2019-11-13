#include "stdafx.h"
#include "Game.h"

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
	float aspect = 1280.0f / 720.0f;
	g_camera2D.SetViewVolumeHeight(300.0f);
	g_camera2D.SetViewVolumeWidth(300.0f * aspect);


	//sprite
	g_sprite.Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f);
	g_spritePos = { -200.0f,50.0f,0.0f };

}


Game::~Game()
{

}
void Game::Update()
{
	//ゲームパッドの更新。	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	player->Update();
	//シャドウキャスターを登録。
	m_shadowMap.RegistShadowCaster(player->GetPlayerSkinModel());
	m_shadowMap.RegistShadowCaster(map->GetMapSkinModel());
	//シャドウマップを更新。
	m_shadowMap.UpdateFromLightTarget(
		{ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
}


void Game::Render()
{

	//物理エンジンの更新。
	//g_physics.Update();
	g_graphicsEngine->BegineRender();
	//現在のレンダリングターゲットをバックアップしておく。
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	g_graphicsEngine->GetD3DDeviceContext()->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	g_graphicsEngine->GetD3DDeviceContext()->RSGetViewports(&numViewport, &oldViewports);

	//シャドウマップにレンダリング
	m_shadowMap.RenderToShadowMap();

	//元に戻す。
	g_graphicsEngine->GetD3DDeviceContext()->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	g_graphicsEngine->GetD3DDeviceContext()->RSSetViewports(numViewport, &oldViewports);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
	
	///////////////////////////////////////////////
	//ここから通常レンダリング。
	///////////////////////////////////////////////

	renderMode = enRenderMode_Normal;
	//マップの描画。
	map->Update();
	map->Draw(renderMode);
	//敵の描画と更新。
	enemy.Update(player);
	enemy.Draw(renderMode);

	//シルエット描画
	renderMode = enRenderMode_Silhouette;
	//プレイヤーの更新。
	player->Update();
	player->Draw(renderMode);

	//通常描画
	renderMode = enRenderMode_Normal;
	player->Draw(renderMode);


	//ゲームカメラの更新
	Gcamera.Update(player);

	//SpriteのUpdate関数を呼び出す。
	g_sprite.Update(g_spritePos, CQuaternion::Identity(), CVector3::One());
	//SpriteのDraw関数を呼び出す。
	g_sprite.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
	g_sprite.Draw();
	//カメラの更新。
	//g_camera3D.Update();
	g_camera2D.Update();


	//描画終了。
	g_graphicsEngine->EndRender();

}
