#pragma once
#include "IGameObject.h"

class GameObjectManager
{
public:

	void Start();
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

private:
	std::vector< IGameObject* > m_goList;
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	ShadowMap m_shadowMap;
	Sprite g_mainSprite;		//スプライト。

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
	void PostRender();
	bool isStartflag = false;
private:
	//フレームバッファのレンダリングターゲット。
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	//フレームバッファののビューポート
	D3D11_VIEWPORT oldViewports;
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	ID3D11DepthStencilState* depthStencilState;

};
extern GameObjectManager* g_goMgr;
