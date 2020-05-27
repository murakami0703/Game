#include "stdafx.h"
#include "Slaim.h"


Slaim::Slaim()
{
	//cmo�t�@�C���̓ǂݍ��݁B
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
		Loitering();		//�p�j��
		break;
	case Slaim::eState_Follow:
		Follow();			//�v���C���[��ǐ�
		break;
	case Slaim::eState_Premove:
		Premove();			//�\������
		break;
	case Slaim::eState_Attack:
		Attack();			//�U��
		break;
	case Slaim::eState_Vertigo:
		Vertigo();
		break;
	case Slaim::eState_Return:
		Return();			//�p�j�ʒu�ɖ߂�
		break;
	case Slaim::eState_Dead:
		Dead();				//��
		break;
	}
}

void Slaim::Render()
{
}
void Slaim::PostRender()
{}