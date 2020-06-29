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
	//�A�C�e���g
	{
		//0�ԁ�ItemCase1
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case1.dds", 275.0f, 275.0f);
		r->SetPosition(m_itemC1Pos);
		r->SetScale(m_itemC1Scale);
		r->SetAlpha(0.9f);
		m_spriteRender.push_back(r);
		//1�ԁ�ItemCase2
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case2.dds", 247.0f, 247.0f);
		r->SetPosition(m_itemC2Pos);
		r->SetScale(m_itemC24Scale);
		r->SetAlpha(0.6f);
		m_spriteRender.push_back(r);
		//2�ԁ�ItemCase3
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case3.dds", 204.0f, 204.0f);
		r->SetPosition(m_itemC3Pos);
		r->SetScale(m_itemC24Scale);
		r->SetAlpha(0.4f);
		m_spriteRender.push_back(r);
		//3�ԁ�ItemCase4
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case4.dds", 148.0f, 148.0f);
		r->SetPosition(m_itemC4Pos);
		r->SetScale(m_itemC24Scale);
		r->SetAlpha(0.2f);
		m_spriteRender.push_back(r);
		//4�ԁ�Itemwaku
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/waku.dds", 363.0f, 362.0f);
		r->SetPosition(m_itemSCPos);
		r->SetScale(m_itemZSCScale);
		m_spriteRender.push_back(r);
		//5�ԁ�Itemhasi
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/hasi.dds", 70.0f, 63.0f);
		r->SetPosition(m_itemHPos);
		r->SetScale(m_itemHScale);
		m_spriteRender.push_back(r);
		//6�ԁ�ItemL
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/L.dds", 100.0f, 148.0f);
		r->SetPosition(m_itemLPos);
		r->SetScale(m_itemLScale);
		m_spriteRender.push_back(r);
		//7�ԁ�ItemZL
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/ZL.dds", 102.0f, 79.0f);
		r->SetPosition(m_itemZLPos);
		r->SetScale(m_itemZSCScale);
		m_spriteRender.push_back(r);
	}
	//HP
	{
		/*//8�ԁ�HP����
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/Hp_Half.dds", 350.0f, 350.0f);
		r->SetAlpha(0.0f);
		m_spriteRender.push_back(r);
		*/
		//HP��z�u����B
		m_setHP = GameData::GetInstance()->GetHitPoint();
		for (int i = 0; i < m_setHP; i++) {
			if (i >= 1) {
				//9�`20�ԁ�HP2�`12
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				m_hpPos.x += m_hpvAddXPos;
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
			else {
				//8�ԁ�HP1
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
		}
	}
	m_spriteNum += m_setHP+1;

	//?�ԁ����l����
	r = g_goMgr->NewGameObject<SpriteRender>();
	r->Init(L"Assets/sprite/Ui_SouiFrame.dds", 800.0f, 300.0f);
	r->SetPosition(m_soulFramePos);
	r->SetScale(m_soulScale);
	r->SetAlpha(0.8f);
	m_spriteRender.push_back(r);

	r = g_goMgr->NewGameObject<SpriteRender>();
	r->Init(L"Assets/sprite/Ui_Soui.dds", 400.0f, 300.0f);
	r->SetPosition(m_soulPos);
	r->SetScale(m_soulScale);
	m_spriteRender.push_back(r);

	//���J�E���g�t�H���g�̐ݒ�B
	GameData* m_gamedate = GameData::GetInstance();
	m_soulFont = g_goMgr->NewGameObject<FontRender>();
	m_soulNowNum = m_gamedate->GetAnima();
	swprintf(soulText, L"%02d", m_soulNowNum);
	m_soulFont->SetText(soulText);
	m_soulFont->SetScale(2.0f);
	m_soulFont->SetPosition({ -490.0f,230.0f });

	m_soulSpNum += 1;
	//�A�C�e��
	g_goMgr->NewGameObject<Item>();

	return true;
}

void GameUI::ScalingSelectCase() {
	//�I��g�̊g��k��
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
	//����HP�ʂ��擾�B
	//HP�����\��
	m_spriteRender[m_spriteNum]->SetAlpha(0.0f);
	m_setHP -= 1.0f;

}



void GameUI::Update()
{
	if (GameData::GetInstance()->GetHitPoint() < m_setHP) {
		m_spriteNum -= 1;
		HPCalc();
	}
	if (GameData::GetInstance()->GetAnima() > m_soulNowNum) {
		swprintf(soulText, L"%02d", GameData::GetInstance()->GetAnima());
		m_soulFont->SetText(soulText);
		m_soulNowNum++;
	}

	ScalingSelectCase();
}
