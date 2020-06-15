#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	return true;
}
void GameCamera::Update()
{
	/// <summary>
	/// カメラの更新
	/// </summary>
	
	CVector3 p_pos = Player::GetInstance()->GetPosition();
	//視点の計算。
	cameraPos.x = p_pos.x;
	cameraPos.y = p_pos.y + 600.0f;
	cameraPos.z = p_pos.z - 300.0f;
	//注視点の計算。
	cameraTarget.x = p_pos.x;
	cameraTarget.y = p_pos.y + 200.0f;
	cameraTarget.z = p_pos.z;
	//3Dカメラに注視点と視点を設定。
	g_camera3D.SetTarget(cameraTarget);
	g_camera3D.SetPosition(cameraPos);

	g_camera3D.Update();
}



