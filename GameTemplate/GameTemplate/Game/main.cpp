#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "Sprite.h"
#include "Map.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "GameObjectManager.h"

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


	//プレイヤー
	Player* player = new Player;
	//マップ
	Map map;
	//ゲームカメラ
	GameCamera Gcamera;
	Enemy enemy;

	//sprite
	g_sprite.Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f);
	g_spritePos = { -200.0f,50.0f,0.0f };

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		//プレイヤーの更新。
		player->Update();
		//プレイヤーの描画。
		player->Draw();
		//マップの描画。
		map.Draw();
		//敵の描画と更新。
		enemy.Update();
		enemy.Draw();

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
};