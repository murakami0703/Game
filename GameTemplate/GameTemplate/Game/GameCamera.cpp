#include "stdafx.h"
#include "GameCamera.h"
#include "player/Player.h"

GameCamera::GameCamera(){}
GameCamera::~GameCamera(){}

bool GameCamera::Start()
{
	return true;
}

void GameCamera::Update()
{
	/// <summary>
	/// �J�����̍X�V
	/// </summary>
	
	//�΂ߏォ�猩���낵�Ă���悤�ɂ���B�i�J�����̓v���C���[�Œ�B�j
	CVector3 p_pos = Player::GetInstance()->GetPosition();
	//���_�̌v�Z�B
	cameraPos.x = p_pos.x;
	cameraPos.y = p_pos.y + 600.0f;
	cameraPos.z = p_pos.z - 300.0f;
	//�����_�̌v�Z�B
	cameraTarget.x = p_pos.x;
	cameraTarget.y = p_pos.y + 200.0f;
	cameraTarget.z = p_pos.z;
	//3D�J�����ɒ����_�Ǝ��_��ݒ�B
	g_camera3D.SetTarget(cameraTarget);
	g_camera3D.SetPosition(cameraPos);

	g_camera3D.Update();
}



