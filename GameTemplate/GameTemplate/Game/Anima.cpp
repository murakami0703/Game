#include "stdafx.h"
#include "Anima.h"
#include "Player.h"
#include "GameData.h"

Anima::Anima()
{
}


Anima::~Anima()
{
}


bool Anima::Start()
{
	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Move].Load(L"Assets/animData/AnimaMove.tka");
	m_animClips[eAnimation_Move].SetLoopFlag(true);
	//cmoファイルの読み込み。
	m_animaModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_animaModelRender->Init(L"Assets/modelData/Anima.cmo", m_animClips, eAnimation_Num);
	m_animaModelRender->SetPosition(m_position);
	m_animaModelRender->SetScale(m_soulScale);

	m_animaModelRender->PlayAnimation(0);
	m_animaModelRender->SetShadowMap(true);

	return  true;
}

void Anima::Appear()
{	
	//地面から離れていたら下降させる。
	if (m_position.y <= m_GroundYPos) {
		//出現中。
		m_timer++;
		Player* player = Player::GetInstance();
		if ((player->GetPosition() - m_position).Length() < m_toPlayerPos) {
			//取得
			m_state = Anima_Get;

		}
		else if (m_timer > m_destroyTimer) {
			//消滅。
			m_state = Anima_Destroy;
		}
	}
	else {
		m_position.y -= m_moveSpeed;
	}

}

void Anima::Get()
{	//取得したよ！！
	GameData::GetInstance()->AnimaCalc(1);
	g_goMgr->DeleteGameObject(m_animaModelRender);
	g_goMgr->DeleteGameObject(this);
}
void Anima::Destroy()
{	//時間経過のため消滅。
	g_goMgr->DeleteGameObject(m_animaModelRender);
	g_goMgr->DeleteGameObject(this);
}
void Anima::Update()
{
	switch (m_state)
	{
	case Anima::Anima_Appear:
		Appear();
		break;
	case Anima::Anima_Get:
		Get();
		break;
	case Anima::Anima_Destroy:
		Destroy();
		break;
	}


	//ワールド行列の更新。
	m_animaModelRender->SetPosition(m_position);
	m_animaModelRender->SetScale(m_soulScale);

}

