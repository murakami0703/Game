#pragma once
#include "Player.h"

class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	/// <summary>
	/// �X�V�B
	/// </summary>
	/// <param name="player">�v���C���[�̌���</param>
	void Update(Player* player);
	CVector3 cameraPos;			//���_�B
	CVector3 cameraTarget;		//�����_�B

};

