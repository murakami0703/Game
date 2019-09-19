#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{

}


GameCamera::~GameCamera()
{
}

void GameCamera::Update(Player* player)
{
	/// <summary>
	/// カメラの更新
	/// </summary>
	
	CVector3 p_pos = player->GetPosition();
	//視点の計算。
	cameraPos.x = p_pos.x;
	cameraPos.y = p_pos.y + 300.0f;
	cameraPos.z = p_pos.z - 300.0f;
	//注視点の計算。
	cameraTarget.x = p_pos.x;
	cameraTarget.y = p_pos.y + 120.0f;
	cameraTarget.z = p_pos.z;
	//3Dカメラに注視点と視点を設定。
	g_camera3D.SetTarget(cameraTarget);
	g_camera3D.SetPosition(cameraPos);

	g_camera3D.Update();
}

