#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "Sprite.h"
#include "Map.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "GameObjectManager.h"
#include "ShadowMap.h"

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
	float aspect = 1280.0f / 720.0f;
	g_camera2D.SetViewVolumeHeight(300.0f);
	g_camera2D.SetViewVolumeWidth(300.0f * aspect);

	ShadowMap m_shadowMap;	//シャドウマップ。

	//プレイヤー
	Player* player = new Player;
	//マップ
	Map* map = new Map;
	//ゲームカメラ
	GameCamera Gcamera;
	Enemy enemy;
	//sprite
	g_sprite.Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f);
	g_spritePos = { -200.0f,50.0f,0.0f };

	EnRenderMode renderMode = enRenderMode_Normal;
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
			//マップの描画。
			map->Update();
			//敵の描画と更新。
			enemy.Update(player);
			//プレイヤーの更新。
			player->Update();
			//ゲームカメラの更新
			Gcamera.Update(player);

			//SpriteのUpdate関数を呼び出す。
			g_sprite.Update(g_spritePos, CQuaternion::Identity(), CVector3::One());
			g_camera2D.Update();

			//シャドウキャスターを登録。
			m_shadowMap.RegistShadowCaster(player->GetPlayerSkinModel());
			m_shadowMap.RegistShadowCaster(map->GetMapSkinModel());
			//シャドウマップを更新。
			m_shadowMap.UpdateFromLightTarget(
				{ 1000.0f, 1000.0f, 1000.0f },
				{ 0.0f, 0.0f, 0.0f }
			);

		}
		//描画処理のブロック。
		{
			//描画開始。
			g_graphicsEngine->BegineRender();
			
			//シャドウマップへの描画
			auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
			//現在のレンダリングターゲットをバックアップしておく。
			ID3D11RenderTargetView* oldRenderTargetView;
			ID3D11DepthStencilView* oldDepthStencilView;
			d3dDeviceContext->OMGetRenderTargets(
				1,
				&oldRenderTargetView,
				&oldDepthStencilView
			);
			//ビューポートもバックアップを取っておく。
			unsigned int numViewport = 1;
			D3D11_VIEWPORT oldViewports;
			d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

			//シャドウマップにレンダリング
			m_shadowMap.RenderToShadowMap();

			//元に戻す。
			d3dDeviceContext->OMSetRenderTargets(
				1,
				&oldRenderTargetView,
				oldDepthStencilView
			);
			d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
			//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
			oldRenderTargetView->Release();
			oldDepthStencilView->Release();

			//手前に描画を行うデプスステンシルステートを設定する。
			g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(depthStencilState, 0);

			renderMode = enRenderMode_Normal;

			map->Draw(renderMode);
			enemy.Draw(renderMode);
			//シルエット描画
			renderMode = enRenderMode_silhouette;
			player->Draw(renderMode);
			//通常描画
			renderMode = enRenderMode_Normal;
			player->Draw(renderMode);
			//SpriteのDraw関数を呼び出す。
			g_sprite.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
			g_sprite.Draw();
			//カメラの更新。
			//g_camera3D.Update();

			//描画終了。
			g_graphicsEngine->EndRender();
		}
	}
};