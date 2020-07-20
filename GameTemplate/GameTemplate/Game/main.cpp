#include "stdafx.h"
#include "Engine.h"
//#include "Title.h"
#include "Game.h"


/// ///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	Engine().InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	//2D�J�������������B
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	//�r���[�{�����[���̕��ƍ������w�肷��B
	g_camera2D.SetViewVolumeHeight(FRAME_BUFFER_H);
	g_camera2D.SetViewVolumeWidth(FRAME_BUFFER_W);

	g_goMgr->NewGameObject<Game>();

	//�Q�[�����[�v�B
	while (Engine().DispatchWindowMessage() == true)
	{
		Engine().GameUpdate();
	}
};
