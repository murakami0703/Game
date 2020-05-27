#include "stdafx.h"
#include "Slaim.h"


Slaim::Slaim()
{
	//cmoƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İB
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/ghosts.cmo");
}


Slaim::~Slaim()
{
}
void Slaim::Idle()
{}

void Slaim::Loitering()
{}
void Slaim::Follow()
{}
void Slaim::Premove()
{}
void Slaim::Attack()
{}
void Slaim::Vertigo()
{}

void Slaim::Return()
{}
void Slaim::Dead()
{}

void Slaim::Update()
{
	switch (m_state)
	{
	case Slaim::eState_Idle:
		Idle();
		break;
	case Slaim::eState_Loitering:
		Loitering();		//œpœj’†
		break;
	case Slaim::eState_Follow:
		Follow();			//ƒvƒŒƒCƒ„[‚ğ’ÇÕ
		break;
	case Slaim::eState_Premove:
		Premove();			//—\”õ“®ì
		break;
	case Slaim::eState_Attack:
		Attack();			//UŒ‚
		break;
	case Slaim::eState_Vertigo:
		Vertigo();
		break;
	case Slaim::eState_Return:
		Return();			//œpœjˆÊ’u‚É–ß‚é
		break;
	case Slaim::eState_Dead:
		Dead();				//€
		break;
	}
}

void Slaim::Render()
{
}
void Slaim::PostRender()
{}