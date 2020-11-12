#include "stdafx.h"
#include "ui/PlayerHPUI.h"
#include "data/GameData.h"


/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const float HP_ADD_POS_X = 50.0f;					//HP2�ȏ��X���W�̉��Z�l�B
const CVector3 HP_SCALE = { 0.15f,0.15f,0.15f };	//HP�̊g�嗦�B

const float HP_ACTIVE_TRUE = 1.0f;					//�����x(�\��)�B
const float HP_ACTIVE_FALSE = 0.0f;					//�����x(��\��)�B

const float HP_PLUS = 1.0f;							//HP�̉��Z�l�B
const float HP_MINUS = -1.0f;						//HP�̌����l�B
const float HP_DECISION = 0.0f;						//HP�̔���l�B


PlayerHPUI::PlayerHPUI(){}
PlayerHPUI::~PlayerHPUI()
{
	//�����B
	for (int i = 0; i < m_spriteRender.size(); i++) {
		g_goMgr->DeleteGameObject(m_spriteRender[i]);
	}
}

bool PlayerHPUI::Start()
{
	//0�ԁ�HP�����B
	m_hpRender = g_goMgr->NewGameObject<SpriteRender>();
	m_hpRender->Init(L"Assets/sprite/Hp_Half.dds", 350.0f, 350.0f);
	m_hpRender->SetAlpha(HP_ACTIVE_FALSE);
	m_spriteRender.push_back(m_hpRender);

	//HP�B
	{
		GameData* gamedate = GameData::GetInstance();
		m_nowHP = gamedate->GetHitPoint();					//���݂�HP�B
		m_hpSpriteNum = (int)gamedate->GetHitPoint();		//�\������HP�X�v���C�g�̐��B

		for (int hp = 0; hp < gamedate->GetMAXHitPoint(); hp++) {
			//1�ԁ`12�ԁ�HP�B
			m_hpRender = g_goMgr->NewGameObject<SpriteRender>();
			m_hpRender->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
			//���݂�HP�������\��������B
			if (hp < m_nowHP) {
				m_hpRender->SetAlpha(HP_ACTIVE_TRUE);
			}
			else {
				m_hpRender->SetAlpha(HP_ACTIVE_FALSE);
			}
			m_hpPos.x += HP_ADD_POS_X;
			m_hpRender->SetPosition(m_hpPos);
			m_hpRender->SetScale(HP_SCALE);
			m_spriteRender.push_back(m_hpRender);

		}
	}
	return true;
}

void PlayerHPUI::HPCalc(float damegeValue)
{
	//HP�̑����v�Z�����B
	if (damegeValue < HP_DECISION) {
		//�_���[�W�󂯂��Ƃ��B
		m_spriteRender[m_hpSpriteNum]->SetAlpha(HP_ACTIVE_FALSE);
		m_hpSpriteNum += (int)damegeValue;
		m_nowHP += damegeValue;
	}
	else{
		//�񕜖�g�p�����Ƃ��B
		m_hpSpriteNum += (int)damegeValue;
		m_spriteRender[m_hpSpriteNum]->SetAlpha(HP_ACTIVE_TRUE);
		m_nowHP += damegeValue;

	}
}

void PlayerHPUI::Update()
{
	GameData* gamedate = GameData::GetInstance();

	//�_���[�W�󂯂��Ƃ��B
	if (gamedate->GetHitPoint() < m_nowHP) {
		HPCalc(HP_MINUS);
	}
	//�񕜖�g�p�B
	if (gamedate->GetHitPoint() > m_nowHP) {
		HPCalc(HP_PLUS);
	}
}
