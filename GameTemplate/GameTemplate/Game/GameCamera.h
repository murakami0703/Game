#pragma once

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	/// <summary>
	/// �X�V�B
	/// </summary>
	/// <param name="player">�v���C���[�̌���</param>
	void Update();
	CVector3 cameraPos;			//���_�B
	CVector3 cameraTarget;		//�����_�B

};

