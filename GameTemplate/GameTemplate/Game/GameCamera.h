#pragma once

class GameCamera final : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start() override;
	void Update() override;
private:
	CVector3 cameraPos;			//���_�B
	CVector3 cameraTarget;		//�����_�B
};

