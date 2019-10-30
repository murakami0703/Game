#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	m_skinModelRender->Init(L"Assets/modelData/unityChan.cmo");
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
bool Player::Start(){
	//cmoファイルの読み込み。
	/*m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_characon.Init(5.0f, 5.0f, m_position);*/
	return true;
}
void Player::Update()
{
	Move();
	//ワールド行列の更新。
	//移動と回転
	//m_skinModelRender->SetPosition(m_position);
}
void Player::Render(int renderMode)
{
	m_skinModelRender->Draw(renderMode);
}