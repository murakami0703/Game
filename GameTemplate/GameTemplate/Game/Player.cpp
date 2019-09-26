#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
}


Player::~Player()
{

}
void Player::Move()
{
	//�\���ړ��B
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_position.x -= 2.0f;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		m_position.x += 2.0f;
	}
	if (g_pad[0].IsPress(enButtonUp)) {
		m_position.z += 2.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		m_position.z -= 2.0f;
	}
}
void Player::Update()
{
	Move();
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	//m_model.Update();
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}