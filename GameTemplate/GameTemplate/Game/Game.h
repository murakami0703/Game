#pragma once
#include "GameObjectManager.h"

#include "Player.h"
#include "Map.h"
#include "level/Level.h"
#include "Sprite.h"
#include "Map.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "SShadowMap.h"
#include "SRenderTarget.h"

class Game
{
public:
	Game();
	~Game();

	/// <summary>
	/// 更新処理。
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理。
	/// </summary>
	void Render();
	/// <summary>
	/// シャドウマップを取得。
	/// </summary>
	/// <returns></returns>
	SShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
private:
	//プレイヤー
	Player* player = new Player;
	//マップ
	Map* map = new Map;
	//ゲームカメラ
	GameCamera Gcamera;
	Enemy enemy;

	CVector3 m_unityChanPos = { 0.0f, 0.0f, 0.0f };	//ユニティちゃんの座標。
	SShadowMap m_shadowMap;					//シャドウマップ。
	Sprite g_sprite;		//スプライト。
	CVector3 g_spritePos = CVector3::Zero();	//スプライトの座標。
	EnRenderMode renderMode = enRenderMode_Invalid;	//レンダーモード
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
};

