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
	//cmo�t�@�C���̓ǂݍ��݁B
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
	//�J���A�j���Đ�
	m_BoxModelRender->PlayAnimation(1);
	effect->EffectPlayer(EffectManager::open, m_position, { 1.0f,1.0f,1.0f });

	if (m_BoxModelRender->IsPlayingAnimation() == false) {
		//�A�j���Đ��I�������̂ŁA�擾����A�C�e�������߂�
		m_rand = rand() % 4;
		//1 �񕜖�
		if (m_rand == m_randNum[0]) {
			m_state = eState_HpRecovery;
		}
		//2 ���e
		else if (m_rand == m_randNum[1]) {
			m_state = eState_Bum;
		}
		//3 �U����UP
		else if (m_rand == m_randNum[2]) {
			m_state = eState_AttackUp;
		}
		//4 �ړ����xUP
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
		//�U�����ɕ󔠂ɋ߂Â��ƊJ����I�I�I
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