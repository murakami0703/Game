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

	//スキンモデル。
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/box.cmo");
	m_position = Player::GetInstance()->GetPosition();
	m_position.y += 200.0f;
	m_skinModelRender->SetPosition(m_position);

	return true;
}

void Bum::InUse()
{
	//使用中。
}
void Bum::EndUse()
{
	//終わり。
}
