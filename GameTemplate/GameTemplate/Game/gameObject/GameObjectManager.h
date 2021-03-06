#pragma once
#include "gameobject/IGameObject.h"


//ゲームオブジェクトのプライオリティ
enum {
	GameObjectPrio_MostHigh,	//最優先。
	GameObjectPrio_High,		//２番目の優先。
	GameObjectPrio_Middle,		//３番目の優先。
	GameObjectPrio_Low,			//４番目の優先。
	GameObjectPrio_MostLow,		//一番低い優先。
};


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
	/// <param name="prio">優先順位。値が小さいほど優先順位は高い。</param>
	template <class T>
	T* NewGameObject( int prio = GameObjectPrio_Middle)
	{
		T* newObj = new T;
		newObj->SetPriority( prio );
		m_goList.push_back(newObj);
		//優先順位を使ってリストをソートする。
		m_goList.sort([&](IGameObject* lhs, IGameObject* rhs) {
			return lhs->GetPriority() < rhs->GetPriority();
		});
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
	/// <summary>
	/// ゲームが開始されましたか？
	/// </summary>
	void SetGameFlag(bool flag) {
		m_gameStartFlag = flag;
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
	std::list< IGameObject* > m_goList;
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	ShadowMap m_shadowMap;					//シャドウマップ。
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	bool m_gameStartFlag = false;		//ゲーム開始フラグ。
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