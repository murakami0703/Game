#include "stdafx.h"
#include "GameObjectManager.h"

//GameObjectManagerクラスのインスタンス。
GameObjectManager* g_goMgr = nullptr;

void GameObjectManager::Start()
{
	//メインレンダリングターゲットの初期化。
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);
	//メインテクスチャの初期化。
	g_mainSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//深度ステンシルステート。
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
	d3ddevice->CreateDepthStencilState(&desc, &depthStencilState);
	isStartflag = true;
}

void GameObjectManager::Update()
{
	if (isStartflag == false) {
		Start();
	}
	//登録されているゲームオブジェクトの更新関数を呼ぶ。
	{
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		for (auto go : m_goList) {
			go->Update();
		}
		g_mainSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
		g_camera2D.Update();

		//シャドウマップを更新。
		m_shadowMap.Update(
			{ 0.0f, 1000.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f }
		);
	}
	//登録されているゲームオブジェクトの描画関数を呼ぶ。
		{
			//描画開始。
			g_graphicsEngine->BegineRender();

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

			// プリレンダリング。
			PreRender();
			// フォワードレンダリング。
			ForwordRender();
			// ポストレンダリング。
			PostRender();

			//描画終了。
			g_graphicsEngine->EndRender();
		}
	//全てのゲームオブジェクトの1フレーム分の処理が終わってから、削除する。
	for (auto it = m_goList.begin(); it != m_goList.end();) {
		if ((*it)->IsRequestDelete()) {
			//削除リクエストを受けているので削除。
			delete* it;
			it = m_goList.erase(it);
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}
}
/// <summary>
/// プリレンダリング。
/// </summary>
void GameObjectManager::PreRender()
{
	//シャドウマップにレンダリング
	m_shadowMap.RenderToShadowMap();
}
/// <summary>
/// フォワードレンダリング。
/// </summary>
void GameObjectManager::ForwordRender()
{
	// フォワードレンダリング。
	//メインのレンダリングターゲットに切り替える。
	g_graphicsEngine->ChangeRenderTarget(&m_mainRenderTarget, &oldViewports);

	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	//手前に描画を行うデプスステンシルステートを設定する。
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(depthStencilState, 0);

	for (auto go : m_goList) {
		go->Render();
	}
}
/// <summary>
/// ポストレンダリング。
/// </summary>
void GameObjectManager::PostRender()
{
	// ポストレンダリング。
	//レンダリングターゲットをフレームバッファに戻す
		//レンダリングターゲットをフレームバッファに戻す。
	g_graphicsEngine->ChangeRenderTarget(
		oldRenderTargetView,
		oldDepthStencilView,
		&oldViewports
	);
	//2D描画
	g_mainSprite.Draw();

	for (auto go : m_goList) {
		go->PostRender();
	}

	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();

}
