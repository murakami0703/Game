#pragma once
#include "Player.h"

class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	/// <summary>
	/// 更新。
	/// </summary>
	/// <param name="player">プレイヤーの検索</param>
	void Update(Player* player);
	CVector3 cameraPos;			//視点。
	CVector3 cameraTarget;		//注視点。

};

