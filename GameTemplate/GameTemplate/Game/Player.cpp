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
	//�\���ړ��B
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
	//cmo�t�@�C���̓ǂݍ��݁B
	/*m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_characon.Init(5.0f, 5.0f, m_position);*/
	return true;
}
void Player::Update()
{
	Move();
	//���[���h�s��̍X�V�B
	//�ړ��Ɖ�]
	//m_skinModelRender->SetPosition(m_position);
}
void Player::Render(int renderMode)
{
	m_skinModelRender->Draw(renderMode);
}