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
#include "ItemManeger.h"
#include "Fade.h"
#include "Font.h"
#include "GameUI.h"
#include "GameData.h"
#include "Anima.h"
#include "AnimaManeger.h"

/// <summary>
/// グローバル変数
/// </summary>


Camera2D g_camera2D;	//2Dカメラ



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
	//ゲームデータ
	GameData* date = new GameData;
	//エネミ
	EnemyManager m_eneMane;
	AnimaManeger m_aniMane;

	/*{Enemy* enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,200.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ -300.0f,30.0f,20.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 250.0f,30.0f,-150.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 190.0f,30.0f,-170.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);


	}*/
	Enemy* enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,200.0f });
	m_eneMane.RegistEnemy(enemy);
	Sprite g_Main;		//スプライト。

	Sprite g_sprite;		//スプライト。
	CVector3 g_spritePos = CVector3::Zero();	//スプライトの座標。

	//試し
	Fade fad;
	Font font;
	GameUI ui;
	//Effekseerマネージャ管理。
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;


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


	//レンダラーを初期化。
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3Dデバイス。
		g_graphicsEngine->GetD3DDeviceContext(),	//D3Dデバイスコンテキスト。
		20000										//板ポリの最大数。
	);
	//エフェクトマネージャを初期化。
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// 描画用インスタンスから描画機能を設定
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());


	//sprite
	g_sprite.Init(L"Assets/sprite/test.dds", 240.0f, 240.0f);
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

	//サンプルのエフェクトをロードする。
	m_sampleEffect = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)L"Assets/effect/test.efk");
	//エフェクトを再生する。
	m_playEffectHandle = m_effekseerManager->Play(m_sampleEffect, 0.0f, 0.0f, 0.0f);


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

			if (m_eneMane.GetInstance()->DeadFlag() == true) {
				Anima* anima = new Anima;
				anima->SetPosition({ m_eneMane.GetPosition() });
				m_aniMane.RegistAnima(anima);
				m_eneMane.GetInstance()->EndFlag();
			}

			//プレイヤーの更新。
			player->Update();
			//マップの描画。
			map->Update();
			//敵の描画と更新。
			m_eneMane.Update(player);
			m_aniMane.Update(player);

			//ゲームカメラの更新
			Gcamera.Update(player);

			//SpriteのUpdate関数を呼び出す。
			g_sprite.Update(g_spritePos, CQuaternion::Identity(), CVector3::One());
			g_Main.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
			g_camera2D.Update();

			ui.Update();

			//Effekseerカメラ行列を設定。
			//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
			Effekseer::Matrix44 efCameraMat;
			g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
			Effekseer::Matrix44 efProjMat;
			g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
			//カメラ行列とプロジェクション行列を設定。
			m_effekseerRenderer->SetCameraMatrix(efCameraMat);
			m_effekseerRenderer->SetProjectionMatrix(efProjMat);
			//Effekseerを更新。
			m_effekseerManager->Update();


			//フード
			/*if (g_pad[0].IsTrigger(enButtonA)) {
				fad.SetSprite(g_sprite);
				fad.SetState(Fade::Fadein);
			}
			fad.Update();*/

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
					m_aniMane.Draw(enRenderMode_Normal);
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

					float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
					//半透明合成のブレンドステートを設定する。
					d3dDeviceContext->OMSetBlendState(
						g_sprite.GetID3D11BlendState(),	//設定するブレンディングステート
						blendFactor,				//ブレンディングファクター。気にしなくてよい
						0xffffffff					//サンプリングマスク。気にしなくてよい。
					);

					//SpriteのDraw関数を呼び出す。
					/*g_sprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					g_sprite.Draw();*/
					ui.Draw();
					//エフェクトは不透明オブジェクトを描画した後で描画する。
					m_effekseerRenderer->BeginRendering();
					m_effekseerManager->Draw();
					m_effekseerRenderer->EndRendering();


					//カメラの更新。
					//g_camera3D.Update();
					//文字出してみ
					//font.Draw(L"");

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
