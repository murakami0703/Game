#include "stdafx.h"
#include "GameUI.h"
#include "GameData.h"

GameUI* GameUI::m_instance = nullptr;

GameUI::GameUI()
{
	m_instance = this;

	//ACeg
	{
		//1Τ¨ItemCase1
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case1.dds", 275.0f, 275.0f);
		r->SetPosition(m_itemC1Pos);
		r->SetScale(m_itemC1Scale);
		m_spriteRender.push_back(r);
		//2Τ¨ItemCase2
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case2.dds", 247.0f, 247.0f);
		r->SetPosition(m_itemC2Pos);
		r->SetScale(m_itemC24Scale);
		m_spriteRender.push_back(r);
		//3Τ¨ItemCase3
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case3.dds", 204.0f, 204.0f);
		r->SetPosition(m_itemC3Pos);
		r->SetScale(m_itemC24Scale);
		m_spriteRender.push_back(r);
		//4Τ¨ItemCase4
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case4.dds", 148.0f, 148.0f);
		r->SetPosition(m_itemC4Pos);
		r->SetScale(m_itemC24Scale);
		m_spriteRender.push_back(r);
	}
	//HP
	{
		//HPπzu·ιB
		m_setHP = GameData::GetInstance()->GetHitPoint();
		for (int i = 0; i < m_setHP; i++) {
			if (i >= 1) {
				//6`16Τ¨HP2`12
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				m_hpPos.x += m_hpvAddXPos;
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
			else {
				//5Τ¨HP1
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
		}
	}
	//Σ§ρΖ
	m_font = g_goMgr->NewGameObject<FontRender>();
	m_font->SetText(L"abc");
}


GameUI::~GameUI()
{

}

void GameUI::ItemSelect()
{
	/*// ιACeΜIπ
	//IπΝε«’B»κΘOΝ¬³­Θθά·B
	switch (m_SIstate)
	{
	case GameUI::Fire:
		//Iπ
		itemFScale = m_nowSelect;
		m_itemKScale = m_NoSelect;
		m_itemLScale = m_NoSelect;
		m_itemTSScale = m_NoSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//ΆΧ
			m_SIstate = Nuts;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//EΧ
			m_SIstate = SPtime;
		}
		break;
	case GameUI::Nuts:
		//ΨΜΐ
		itemFScale = m_NoSelect;
		m_itemKScale = m_nowSelect;
		m_itemLScale = m_NoSelect;
		m_itemTSScale = m_NoSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//ΆΧ
			m_SIstate = Lanp;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//EΜACeIπ΅ά·
			m_SIstate = Fire;
		}
		break;
	case GameUI::Lanp:
		//v
		itemFScale = m_NoSelect;
		m_itemKScale = m_NoSelect;
		m_itemLScale = m_nowSelect;
		m_itemTSScale = m_NoSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//ΆΧ
			m_SIstate = SPtime;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//EΧ
			m_SIstate = Nuts;
		}
		break;
	case GameUI::SPtime:
		//Τβ~
		itemFScale = m_NoSelect;
		m_itemKScale = m_NoSelect;
		m_itemLScale = m_NoSelect;
		m_itemTSScale = m_nowSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//ΆΧ
			m_SIstate = Fire;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//EΧ
			m_SIstate = Lanp;
		}

		break;
	}
	m_SIstate;*/
}


void GameUI::HPAdd()
{
	//HPΜΈ³Ήιζ
	m_hp = GameData::GetInstance()->GetHitPoint();
	//Α¦ά[·ζ
	m_spriteRender[4 + m_hp]->SetAlpha(0.0f);
}

void GameUI::Update()
{
}
void GameUI::Render(){}
void GameUI::PostRender()
{
}