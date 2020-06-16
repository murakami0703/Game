#include "stdafx.h"
#include "GameUI.h"
#include "GameData.h"
#include "Item.h"

GameUI* GameUI::m_instance = nullptr;

GameUI::GameUI()
{
	m_instance = this;
}


GameUI::~GameUI()
{

}
bool GameUI::Start()
{
	//ƒAƒCƒeƒ€˜g
	{
		//1”Ô¨ItemCase1
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case1.dds", 275.0f, 275.0f);
		r->SetPosition(m_itemC1Pos);
		r->SetScale(m_itemC1Scale);
		r->SetAlpha(0.9f);
		m_spriteRender.push_back(r);
		//2”Ô¨ItemCase2
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case2.dds", 247.0f, 247.0f);
		r->SetPosition(m_itemC2Pos);
		r->SetScale(m_itemC24Scale);
		r->SetAlpha(0.6f);
		m_spriteRender.push_back(r);
		//3”Ô¨ItemCase3
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case3.dds", 204.0f, 204.0f);
		r->SetPosition(m_itemC3Pos);
		r->SetScale(m_itemC24Scale);
		r->SetAlpha(0.4f);
		m_spriteRender.push_back(r);
		//4”Ô¨ItemCase4
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case4.dds", 148.0f, 148.0f);
		r->SetPosition(m_itemC4Pos);
		r->SetScale(m_itemC24Scale);
		r->SetAlpha(0.2f);
		m_spriteRender.push_back(r);
		//5”Ô¨Itemwaku
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/waku.dds", 363.0f, 362.0f);
		r->SetPosition(m_itemSCPos);
		r->SetScale(m_itemZSCScale);
		m_spriteRender.push_back(r);
		//6”Ô¨Itemhasi
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/hasi.dds", 70.0f, 63.0f);
		r->SetPosition(m_itemHPos);
		r->SetScale(m_itemHScale);
		m_spriteRender.push_back(r);
		//7”Ô¨ItemL
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/L.dds", 100.0f, 148.0f);
		r->SetPosition(m_itemLPos);
		r->SetScale(m_itemLScale);
		m_spriteRender.push_back(r);
		//8”Ô¨ItemZL
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/ZL.dds", 102.0f, 79.0f);
		r->SetPosition(m_itemZLPos);
		r->SetScale(m_itemZSCScale);
		m_spriteRender.push_back(r);
	}
	//HP
	{
		//HP‚ð”z’u‚·‚éB
		m_setHP = GameData::GetInstance()->GetHitPoint();
		for (int i = 0; i < m_setHP; i++) {
			if (i >= 1) {
				//10`20”Ô¨HP2`12
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				m_hpPos.x += m_hpvAddXPos;
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
			else {
				//9”Ô¨HP1
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
		}
		//21”Ô¨HP”¼•ª
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/Hp_Half.dds", 350.0f, 350.0f);
		r->SetAlpha(0.0f);
		m_spriteRender.push_back(r);

	}
	//ƒAƒCƒeƒ€
	g_goMgr->NewGameObject<Item>();

	return true;
}

void GameUI::ScalingSelectCase() {
	//‘I‘ð˜g‚ÌŠg‘åk¬
	if (m_scalingCount > m_smallCountValue) {
		m_scalingCount = 0;
	}
	else if (m_scalingCount <= m_bigCountValue) {
		m_itemZSCScale += m_scalingValue;
	}
	else{
		m_itemZSCScale -= m_scalingValue;
	}
	m_scalingCount++;
	m_spriteRender[4]->SetScale(m_itemZSCScale);
}

void GameUI::HPCalc()
{
	//¡‚ÌHP—Ê‚ðŽæ“¾B
	m_nowHp = GameData::GetInstance()->GetHitPoint();
	//HP”¼•ª•\Ž¦
	if (fmod(m_nowHp, 1) <= 0.5f) {
	}
}




void GameUI::Update()
{
	HPCalc();
	ScalingSelectCase();
}
