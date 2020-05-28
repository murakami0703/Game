#include "stdafx.h"
#include "Slaim.h"


Slaim::Slaim()
{
	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/slaim/slaim_idle.tka");
	m_animClips[eAnimation_Idle].SetLoopFlag(true);
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/slaim/slaim_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/slaim/slaim_premove.tka");
	m_animClips[eAnimation_Premove2].Load(L"Assets/animData/slaim/slaim_premove2.tka");
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/slaim/slaim_attack.tka");
	m_animClips[eAnimation_Vertigo].Load(L"Assets/animData/slaim/slaim_vertigo.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/slaim/slaim_death.tka");

	//cmoファイルの読み込み。
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/slaim.cmo", m_animClips, eAnimation_Num);
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
		Loitering();		//徘徊中
		break;
	case Slaim::eState_Follow:
		Follow();			//プレイヤーを追跡
		break;
	case Slaim::eState_Premove:
		Premove();			//予備動作
		break;
	case Slaim::eState_Attack:
		Attack();			//攻撃
		break;
	case Slaim::eState_Vertigo:
		Vertigo();
		break;
	case Slaim::eState_Return:
		Return();			//徘徊位置に戻る
		break;
	case Slaim::eState_Dead:
		Dead();				//死
		break;
	}

	//ワールド行列の更新。
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

}

void Slaim::Render()
{
}
void Slaim::PostRender()
{}