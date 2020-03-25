#include "stdafx.h"
#include "GameUI.h"
#include "GameData.h"

GameUI* GameUI::m_instance = nullptr;

GameUI::GameUI()
{
	m_instance = this;

	//�A�C�e���g
	{
		//1�ԁ�ItemCase1
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case1.dds", 275.0f, 275.0f);
		r->SetPosition(m_itemC1Pos);
		r->SetScale(m_itemC1Scale);
		m_spriteRender.push_back(r);
		//2�ԁ�ItemCase2
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case2.dds", 247.0f, 247.0f);
		r->SetPosition(m_itemC2Pos);
		r->SetScale(m_itemC24Scale);
		m_spriteRender.push_back(r);
		//3�ԁ�ItemCase3
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case3.dds", 204.0f, 204.0f);
		r->SetPosition(m_itemC3Pos);
		r->SetScale(m_itemC24Scale);
		m_spriteRender.push_back(r);
		//4�ԁ�ItemCase4
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case4.dds", 148.0f, 148.0f);
		r->SetPosition(m_itemC4Pos);
		r->SetScale(m_itemC24Scale);
		m_spriteRender.push_back(r);
	}
	//HP
	{
		//HP��z�u����B
		m_setHP = GameData::GetInstance()->GetHitPoint();
		for (int i = 0; i < m_setHP; i++) {
			if (i >= 1) {
				//6�`16�ԁ�HP2�`12
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				m_hpPos.x += m_hpvAddXPos;
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
			else {
				//5�ԁ�HP1
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
		}
	}
	//�ӂ����
	m_font = g_goMgr->NewGameObject<FontRender>();
	m_font->SetText(L"abc");
}


GameUI::~GameUI()
{

}

void GameUI::ItemSelect()
{
	/*//����A�C�e���̑I��
	//�I�𒆂͑傫���B����ȊO�͏������Ȃ�܂��B
	switch (m_SIstate)
	{
	case GameUI::Fire:
		//���I��
		itemFScale = m_nowSelect;
		m_itemKScale = m_NoSelect;
		m_itemLScale = m_NoSelect;
		m_itemTSScale = m_NoSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//����
			m_SIstate = Nuts;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//�E��
			m_SIstate = SPtime;
		}
		break;
	case GameUI::Nuts:
		//�؂̎�
		itemFScale = m_NoSelect;
		m_itemKScale = m_nowSelect;
		m_itemLScale = m_NoSelect;
		m_itemTSScale = m_NoSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//����
			m_SIstate = Lanp;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//�E�̃A�C�e���I�����܂�
			m_SIstate = Fire;
		}
		break;
	case GameUI::Lanp:
		//�����v
		itemFScale = m_NoSelect;
		m_itemKScale = m_NoSelect;
		m_itemLScale = m_nowSelect;
		m_itemTSScale = m_NoSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//����
			m_SIstate = SPtime;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//�E��
			m_SIstate = Nuts;
		}
		break;
	case GameUI::SPtime:
		//���Ԓ�~
		itemFScale = m_NoSelect;
		m_itemKScale = m_NoSelect;
		m_itemLScale = m_NoSelect;
		m_itemTSScale = m_nowSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//����
			m_SIstate = Fire;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//�E��
			m_SIstate = Lanp;
		}

		break;
	}
	m_SIstate;*/
}


void GameUI::HPAdd()
{
	//HP�̑����������
	m_hp = GameData::GetInstance()->GetHitPoint();
	//�����܁[����
	m_spriteRender[4 + m_hp]->SetAlpha(0.0f);
}

void GameUI::Update()
{
}
void GameUI::Render(){}
void GameUI::PostRender()
{
}