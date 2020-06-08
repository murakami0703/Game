#pragma once
#include "IGameObject.h"

class GameObjectManager
{
public:

	void Init();
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// ゲームオブジェクトの追加。
	/// </summary>
	template <class T>
	T* NewGameObject()
	{
		T* newObj = new T;
		m_goList.push_back(newObj);
		return newObj;
	}
	/// <summary>
	/// ゲームオブジェクトをリストから削除する。
	/// </summary>
	/// <param name="go">削除するゲームオブジェクト</param>
	void DeleteGameObject(IGameObject* go) {
		//リストから検索して。見つかったら削除。
		//リストから検索して、見つかったら削除する。
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				//削除リクエストを送る。
				go->RequestDelete();
				return;
			}
		}
	}
	/// <summary>
	/// シャドウマップを取得。
	/// </summary>
	/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
	/// <summary>
	/// メインレンダリングターゲットを取得。
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}

	void SetMainSpriteMulColor(CVector4 mul) {
		m_copyMainRtToFrameBufferSprite.SetMulColor(mul);
	}
private:
	/// <summary>
	/// プリレンダリング。
	/// </summary>
	void PreRender();
	/// <summary>
	/// フォワードレンダリング。
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// ポストレンダリング。
	/// </summary>
	void Post2DRender();

private:
	std::vector< IGameObject* > m_goList;
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	ShadowMap m_shadowMap;					//シャドウマップ。
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。

private:
	//フレームバッファのレンダリングターゲット。
	ID3D11RenderTargetView* oldRenderTargetView;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* oldDepthStencilView;	//フレームバッファのデプスステンシルビュー。
	//フレームバッファのビューポート
	D3D11_VIEWPORT oldViewports;
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	ID3D11DepthStencilState* depthStencilState;


};
extern GameObjectManager* g_goMgr;