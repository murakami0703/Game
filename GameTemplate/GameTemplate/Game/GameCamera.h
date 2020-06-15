#pragma once

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	/// <summary>
	/// 更新。
	/// </summary>
	/// <param name="player">プレイヤーの検索</param>
	bool Start();
	void Update();
	CVector3 cameraPos;			//視点。
	CVector3 cameraTarget;		//注視点。

};

