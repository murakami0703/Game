#include "stdafx.h"
#include "GameUI.h"
#include "GameData.h"

GameUI* GameUI::m_instance = nullptr;

GameUI::GameUI()
{
	m_instance = this;

	//1
	m_itemCase1 = g_goMgr->NewGameObject<SpriteRender>();
	m_itemCase1->Init(L"Assets/sprite/case1.dds", 275.0f, 275.0f);
	//m_itemCase1->SetPosition(m_itemC1Pos);
	//m_itemCase1->SetScale(m_itemC1Scale);

	m_font = g_goMgr->NewGameObject<FontRender>();
	m_font->SetText(L"あいう");
	//アイテム枠
	CaseSet();
}


GameUI::~GameUI()
{

}
void GameUI::CaseSet()
{
	//アイテム枠
	//2
	/*m_itemCase2.Init(L"Assets/sprite/case2.dds", 247.0f, 247.0f);
	//3
	m_itemCase3.Init(L"Assets/sprite/case3.dds", 204.0f, 204.0f);
	//4
	m_itemCase4.Init(L"Assets/sprite/case4.dds", 148.0f, 148.0f);
	*/

}

void GameUI::ItemSelect()
{
	/*//あるアイテムの選択
	//選択中は大きい。それ以外は小さくなります。
	switch (m_SIstate)
	{
	case GameUI::Fire:
		//炎選択中
		itemFScale = m_nowSelect;
		m_itemKScale = m_NoSelect;
		m_itemLScale = m_NoSelect;
		m_itemTSScale = m_NoSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//左隣
			m_SIstate = Nuts;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//右隣
			m_SIstate = SPtime;
		}
		break;
	case GameUI::Nuts:
		//木の実
		itemFScale = m_NoSelect;
		m_itemKScale = m_nowSelect;
		m_itemLScale = m_NoSelect;
		m_itemTSScale = m_NoSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//左隣
			m_SIstate = Lanp;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//右のアイテム選択します
			m_SIstate = Fire;
		}
		break;
	case GameUI::Lanp:
		//ランプ
		itemFScale = m_NoSelect;
		m_itemKScale = m_NoSelect;
		m_itemLScale = m_nowSelect;
		m_itemTSScale = m_NoSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//左隣
			m_SIstate = SPtime;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//右隣
			m_SIstate = Nuts;
		}
		break;
	case GameUI::SPtime:
		//時間停止
		itemFScale = m_NoSelect;
		m_itemKScale = m_NoSelect;
		m_itemLScale = m_NoSelect;
		m_itemTSScale = m_nowSelect;
		if (g_pad[0].IsTrigger(enButtonLB1)) {
			//左隣
			m_SIstate = Fire;
		}
		else if (g_pad[0].IsTrigger(enButtonRB1)) {
			//右隣
			m_SIstate = Lanp;
		}

		break;
	}
	m_SIstate;*/
}


void GameUI::HPAdd()
{
//	//HPの増減で表示を変えます
////最初はHP3から。最大12まで。
//	HP = GameData::GetInstance()->GetHitPoint();
//	if (m_hpCount < HP) {
//			PlayerHP* pHP = new PlayerHP;
//			m_hpPoint = HPManeger::GetInstance()->HpSetPoint(m_hpCount);
//			pHP->SetHPPosition({ m_hpPoint->position });
//			HPManeger::GetInstance()->RegistAnima(pHP);
//			m_hpCount++;
//	}

}

void GameUI::Update()
{
}
void GameUI::Render(){}
void GameUI::PostRender()
{

}