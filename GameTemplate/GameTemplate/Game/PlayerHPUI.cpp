#include "stdafx.h"
#include "PlayerHPUI.h"
#include "GameData.h"


/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const float HP_ADD_POSX = 25.0f;						//HP2�ȏ��X���W�̉��Z�l
const CVector3 HP_SCALE = { 0.15f,0.15f,0.15f };		//HP�̊g�嗦

PlayerHPUI::PlayerHPUI()
{
}


PlayerHPUI::~PlayerHPUI()
{
}

bool PlayerHPUI::Start()
{
	//0�ԁ�HP����
	m_hpRender = g_goMgr->NewGameObject<SpriteRender>();
	m_hpRender->Init(L"Assets/sprite/Hp_Half.dds", 350.0f, 350.0f);
	m_hpRender->SetAlpha(0.0f);
	m_spriteRender.push_back(m_hpRender);

	//HP
	GameData* m_gamedate = GameData::GetInstance();
	m_nowHP = m_gamedate->GetHitPoint();		//���݂�HP�B
	m_hpSpriteNum = (int)m_gamedate->GetHitPoint() + 1;		//�\������HP�X�v���C�g�̐��B

	for (int hp = 0; hp < m_gamedate->GetMAXHitPoint(); hp++) {
		//1�ԁ`12�ԁ�HP
		m_hpRender = g_goMgr->NewGameObject<SpriteRender>();
		m_hpRender->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
		m_hpPos.x += HP_ADD_POSX;
		//���݂�HP�������\��������B
		if (hp < m_nowHP) {
			m_hpRender->SetAlpha(1.0f);
		}
		else {
			m_hpRender->SetAlpha(0.0f);
		}
		m_hpPos.x += HP_ADD_POSX;
		m_hpRender->SetPosition(m_hpPos);
		m_hpRender->SetScale(HP_SCALE);
		m_spriteRender.push_back(m_hpRender);

	}

	return true;
}

void PlayerHPUI::HPCalc()
{
	//HP�̑����v�Z�����B
}

void PlayerHPUI::Update()
{
	GameData* m_gamedate = GameData::GetInstance();
	
	//�_���[�W�󂯂��Ƃ��B



	//�񕜖�g�p�B




}
