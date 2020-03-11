#include "stdafx.h"
#include "system/system.h"
#include "Game.h"


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

	g_goMgr.NewGameObject<Game>();

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		g_goMgr.Update();
	}
};
