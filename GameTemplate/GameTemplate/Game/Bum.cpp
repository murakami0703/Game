#include "stdafx.h"
#include "Bum.h"
#include "Player.h"


Bum::Bum()
{
}


Bum::~Bum()
{
}
bool Bum::Start()
{

	//�X�L�����f���B
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/box.cmo");
	m_position = Player::GetInstance()->GetPosition();
	m_position.y += 200.0f;
	m_skinModelRender->SetPosition(m_position);

	return true;
}

void Bum::InUse()
{
	//�g�p���B
}
void Bum::EndUse()
{
	//�I���B
}
