#include "stdafx.h"
#include "system/system.h"
#include "Game.h"


/// ///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	g_goMgr->NewGameObject<Game>();

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		g_goMgr->Update();
	}
};
