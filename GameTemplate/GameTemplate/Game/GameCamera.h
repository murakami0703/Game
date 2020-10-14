#pragma once

class GameCamera final : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start() override;
	void Update() override;
private:
	CVector3 cameraPos;			//視点。
	CVector3 cameraTarget;		//注視点。
};

