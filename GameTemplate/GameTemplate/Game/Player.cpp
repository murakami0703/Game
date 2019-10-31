#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	//m_characon.Init(5.0f, 5.0f, m_position);

	m_position = { 0.0f,0.0f,0.0f };

}
Player::~Player()
{
}

void Player::Move()
{
	//十字移動。
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_position.x -= 4.0f;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		m_position.x += 4.0f;
	}
	if (g_pad[0].IsPress(enButtonUp)) {
		m_position.z += 4.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		m_position.z -= 4.0f;
	}
}
void Player::Update()
{
	Move();
	//ワールド行列の更新。
	//移動と回転
	m_model.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3::One());
	m_model.Update();

}
void Player::Draw(int renderMode)
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		renderMode
	);
}