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

	g_goMgr->NewGameObject<Game>();

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		g_goMgr->Update();
	}
};
