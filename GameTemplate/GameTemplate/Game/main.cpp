#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "sprite/Sprite.h"
#include "Map.h"
#include "enemy/Enemy.h"
#include "GameCamera.h"
#include "gameObject/GameObjectManager.h"
#include "ShadowMap.h"
#include "RenderTarget.h"
#include "enemy/EnemyManeger.h"

/// <summary>
/// グローバル変数
/// </summary>


Camera2D g_camera2D;	//2Dカメラ

Sprite g_sprite;		//スプライト。
CVector3 g_spritePos = CVector3::Zero();	//スプライトの座標。



/// ///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

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

	ShadowMap m_shadowMap;	//シャドウマップ。

	//プレイヤー
	Player* player = new Player;
	//マップ
	Map* map = new Map;
	//ゲームカメラ
	GameCamera Gcamera;
	EnemyManager m_eneMane;
	Enemy* enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,200.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ -300.0f,30.0f,20.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,-150.0f });
	m_eneMane.RegistEnemy(enemy);
	
	/*Enemy enemy;
	enemy.SetPosition({ 150.0f,30.0f,200.0f });
	Enemy* enemy1 = new Enemy;
	enemy1->SetPosition({ -300.0f,30.0f,20.0f });
	Enemy enemy2;
	enemy2.SetPosition({ 150.0f,30.0f,-150.0f });
	*/
	Sprite g_Main;		//スプライト。

	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。


	//メインレンダリングターゲットの初期化。
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);
	//メインテクスチャの初期化。
	g_Main.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

	//sprite
	g_sprite.Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f);
	g_spritePos = { -200.0f,50.0f,0.0f };
	//フレームバッファのレンダリングターゲット。
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	//フレームバッファののビューポート
	D3D11_VIEWPORT oldViewports;

	//深度ステンシルステート。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc = D3D11_COMPARISON_GREATER;
	desc.StencilEnable = false;
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//D3Dデバイスを取得。
	auto d3ddevice = g_graphicsEngine->GetD3DDevice();

	//デプスステンシルステートを作成。
	ID3D11DepthStencilState* depthStencilState;
	d3ddevice->CreateDepthStencilState(&desc, &depthStencilState);

	

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{

		//更新処理
		{
			//ゲームパッドの更新。	
			for (auto& pad : g_pad) {
				pad.Update();
			}
			//物理エンジンの更新。
			g_physics.Update();

			//プレイヤーの更新。
			player->Update();
			//マップの描画。
			map->Update();
			//敵の描画と更新。
			m_eneMane.Update(player);

			//ゲームカメラの更新
			Gcamera.Update(player);

			//SpriteのUpdate関数を呼び出す。
			g_sprite.Update(g_spritePos, CQuaternion::Identity(), CVector3::One());
			g_Main.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
			g_camera2D.Update();

			//シャドウキャスターを登録。
			m_shadowMap.RegistShadowCaster(player->GetPlayerSkinModel());
			m_shadowMap.RegistShadowCaster(map->GetMapSkinModel());
			//シャドウマップを更新。
			m_shadowMap.Update(
				{ 0.0f, 1000.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f }
			);

		}
		//描画処理のブロック。
		{
			//描画開始。
			g_graphicsEngine->BegineRender();
			{
				// プリレンダリング
				{
					//シャドウマップへの描画
					auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
					//現在のレンダリングターゲットをバックアップしておく。
					d3dDeviceContext->OMGetRenderTargets(
						1,
						&oldRenderTargetView,
						&oldDepthStencilView
					);
					//ビューポートもバックアップを取っておく。
					unsigned int numViewport = 1;
					d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

					//シャドウマップにレンダリング
					m_shadowMap.RenderToShadowMap();
				}
				// フォワードレンダリング 
				{
					//メインのレンダリングターゲットに切り替える。
					auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
					ID3D11RenderTargetView* rtTbl[] = {
					m_mainRenderTarget.GetRenderTargetView()
					};
					//レンダリングターゲットの切り替え。
					d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_mainRenderTarget.GetDepthStensilView());
					if (&oldViewports != nullptr) {
						//ビューポートが指定されていたら、ビューポートも変更する。
						d3dDeviceContext->RSSetViewports(1, &oldViewports);
					}
					//メインレンダリングターゲットをクリアする。
					float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
					m_mainRenderTarget.ClearRenderTarget(clearColor);

					//手前に描画を行うデプスステンシルステートを設定する。
					g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(depthStencilState, 0);

					map->Draw(enRenderMode_Normal);
					m_eneMane.Draw(enRenderMode_Normal);
					//シルエット描画
					player->Draw(enRenderMode_silhouette);
					//通常描画
					player->Draw(enRenderMode_Normal);
				}
				// ポストレンダリング
				{
					//レンダリングターゲットをフレームバッファに戻す。
					auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
					//レンダリングターゲットの切り替え。
					ID3D11RenderTargetView* rtTbl[] = {
					oldRenderTargetView
					};
					d3dDeviceContext->OMSetRenderTargets(1, rtTbl, oldDepthStencilView);
					if (&oldViewports != nullptr) {
						//ビューポートが指定されていたら、ビューポートも変更する。
						d3dDeviceContext->RSSetViewports(1, &oldViewports);
					}

					g_Main.Draw();

					//SpriteのDraw関数を呼び出す。
					g_sprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					
					g_sprite.Draw();
					//カメラの更新。
					//g_camera3D.Update();

					//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
					oldRenderTargetView->Release();
					oldDepthStencilView->Release();
				}
				//描画終了。
				g_graphicsEngine->EndRender();
			}
		}
	}
};
