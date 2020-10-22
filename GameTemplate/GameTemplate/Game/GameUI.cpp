#include "stdafx.h"
#include "GameUI.h"
#include "GameData.h"

//�eUI�����N���X�B
#include "PlayerHPUI.h"
#include "ItemUI.h"
#include "SoulUI.h"

GameUI* GameUI::m_instance = nullptr;

/////////////////////////////////////////////////////////
/// �萔
/////////////////////////////////////////////////////////

const CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };		//�g1�̍��W
const CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//�g2�̍��W
const CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//�g3�̍��W
const CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };		//�g4�̍��W

const CVector3 m_itemC1Scale = { 0.8f,0.8f,0.8f };		//�g1�g�嗦
const CVector3 m_itemC24Scale = { 0.7f,0.7f,0.7f };		//�g2�`4�g�嗦

const CVector3 m_itemSCPos = { 460.0f,-240.0f,0.0f };		//�I��g�̍��W
const CVector3 m_itemHPos = { 505.0f,14.0f,0.0f };		//�[�̍��W
const CVector3 m_itemLPos = { 585.0f,-250.0f,0.0f };		//L�̍��W
const CVector3 m_itemZLPos = { 605.0f,20.0f,0.0f };		//ZL�̍��W

const CVector3 m_itemLScale = { 0.8f,0.8f,0.8f };			//L�g�嗦
const CVector3 m_itemHScale = { 0.6f,0.6f,0.6f };			//�[�g�嗦

const int m_bigCountValue = 30;
const int m_smallCountValue = 60;
const CVector3 m_scalingValue = { 0.002f,0.002f,0.002f };			//�I��g�g��l
const CVector3 m_hpScale = { 0.15f,0.15f,0.15f };		//HP�̊g�嗦
const float m_hpvAddXPos = 50.0f;					//HP2�ȏ��X���W�̕ω��l
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

	//�v���C���[HPUI
	g_goMgr->NewGameObject<PlayerHPUI>();
	//�A�C�e��UI
	g_goMgr->NewGameObject<ItemUI>();
	//��UI
	g_goMgr->NewGameObject<SoulUI>();

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


void GameUI::OnlyDelete()
{
	//�S�������B
	//sprite�B
	for (int i = 0; i < m_spriteRender.size(); i++) {
		g_goMgr->DeleteGameObject(m_spriteRender[i]);
	}
	//�t�H���g

	g_goMgr->DeleteGameObject(this);
}

void GameUI::Update()
{
	GameData* m_gamedate = GameData::GetInstance();

	
	ScalingSelectCase();

	//�{�X���|���ꂽ�̂�UI�����B
	if (m_gamedate->ResultFlag() == true) {
		OnlyDelete();
	}
}
