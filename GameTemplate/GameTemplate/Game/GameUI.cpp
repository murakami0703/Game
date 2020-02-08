#include "stdafx.h"
#include "GameUI.h"

GameUI* GameUI::m_instance = nullptr;

GameUI::GameUI()
{
	m_instance = this;

	//HP‚Ì˜g
	m_hpHartFrame.Init(L"Assets/sprite/HPWaku.dds", 240.0f, 240.0f);
	m_hpHFPos = { -200.0f,50.0f,0.0f };
	/*
	//HP
	m_hpHart.Init(L"Assets/sprite/HP.dds", 240.0f, 240.0f);
	m_hpHPos = { -200.0f,50.0f,0.0f };

	//ƒAƒCƒeƒ€—p‚Ì˜g
	m_itemSetLog.Init(L"Assets/sprite/ItemSetLog.dds", 240.0f, 240.0f);
	m_itemSLPos = { -200.0f,50.0f,0.0f };
	*/
}


GameUI::~GameUI()
{
}

void GameUI::Update()
{

}
void GameUI::Render()
{

}