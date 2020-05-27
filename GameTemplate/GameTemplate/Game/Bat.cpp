#include "stdafx.h"
#include "Bat.h"


Bat::Bat()
{
	//cmoƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İB
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/ghosts.cmo");

}


Bat::~Bat()
{
}
void Bat::Loitering()
{}
void Bat::Follow()
{}
void Bat::Premove()
{}
void Bat::Attack()
{}
void Bat::Return()
{}
void Bat::Dead()
{}

void Bat::Update()
{
	switch (m_state)
	{
	case Bat::eState_Loitering:
		Loitering();		//œpœj’†
		break;
	case Bat::eState_Follow:
		Follow();			//ƒvƒŒƒCƒ„[‚ğ’ÇÕ
		break;
	case Bat::eState_Premove:
		Premove();			//—\”õ“®ì
		break;
	case Bat::eState_Attack:
		Attack();			//UŒ‚
		break;
	case Bat::eState_Return:
		Return();			//œpœjˆÊ’u‚É–ß‚é
		break;
	case Bat::eState_Dead:
		Dead();				//€
		break;
	}
}
void Bat::Render(){}
void Bat::PostRender(){}