#include "stdafx.h"
#include "TreasureBox.h"
#include "Player.h"
#include "EffectManager.h"


TreasureBox::TreasureBox()
{
}


TreasureBox::~TreasureBox()
{
}

bool TreasureBox::Start() {
	m_animClips[eAnimation_Close].Load(L"Assets/animData/stage_gimmik/close_box.tka");
	m_animClips[eAnimation_Open].Load(L"Assets/animData/stage_gimmik/open_box.tka");
	//cmoファイルの読み込み。
	m_BoxModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_BoxModelRender->Init(L"Assets/modelData/Treasure_Box.cmo", m_animClips, eAnimation_Num);
	m_BoxModelRender->SetPosition(m_position);
	m_BoxModelRender->SetRotation(m_rotation);
	m_BoxModelRender->SetScale(m_scale);
	m_BoxModelRender->PlayAnimation(0);

	return true;
}

void TreasureBox::Open()
{
	EffectManager* effect = EffectManager::GetInstance();
	//開封アニメ再生
	m_BoxModelRender->PlayAnimation(1);
	effect->EffectPlayer(EffectManager::open, m_position, { 1.0f,1.0f,1.0f });

	if (m_BoxModelRender->IsPlayingAnimation() == false) {
		//アニメ再生終了したので、取得するアイテムを決める
		m_rand = rand() % 4;
		//1 回復薬
		if (m_rand == m_randNum[0]) {
			m_state = eState_HpRecovery;
		}
		//2 爆弾
		else if (m_rand == m_randNum[1]) {
			m_state = eState_Bum;
		}
		//3 攻撃力UP
		else if (m_rand == m_randNum[2]) {
			m_state = eState_AttackUp;
		}
		//4 移動速度UP
		else if (m_rand == m_randNum[3]) {
			m_state = eState_SpeedUp;
		}
	}
}

void TreasureBox::HpRecovery()
{
}
void TreasureBox::Bum()
{

}
void TreasureBox::AttackUp()
{

}
void TreasureBox::SpeedUp() 
{

}

void TreasureBox::Update()
{
	Player* player = Player::GetInstance();
	m_toPlayerVec = player->GetPosition() - m_position;

	switch (m_state)
	{
	case TreasureBox::eState_Idle:
		//攻撃中に宝箱に近づくと開くよ！！！
		if (m_toPlayerVec.Length() <= m_openYVec) {
			if (player->GetAttackflag() == true) {
				m_state = eState_Open;
			}
		}
		break;
	case TreasureBox::eState_Open:
		Open();
		break;
	case TreasureBox::eState_HpRecovery:
		HpRecovery();
		break;
	case TreasureBox::eState_Bum:
		Bum();
		break;
	case TreasureBox::eState_AttackUp:
		AttackUp();
		break;
	case TreasureBox::eState_SpeedUp:
		SpeedUp();
		break;
	}
}