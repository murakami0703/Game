#include "stdafx.h"
#include "GameUI.h"
#include "GameData.h"

GameUI* GameUI::m_instance = nullptr;

GameUI::GameUI()
{
	m_instance = this;

	//HPの枠
	m_hpHartFrame.Init(L"Assets/sprite/HPWaku.dds", 200.0f, 200.0f);
	m_hpHFPos = { -610.0f,340.0f,0.0f };
	m_hpHFScale = { 0.2f,0.2f,0.2f };
	//HP
	m_hpHart1.Init(L"Assets/sprite/HP.dds", 200.0f, 200.0f);
	m_hpHPos = { -610.0f,340.0f,0.0f };
	m_hpScale = { 0.2f,0.2f,0.2f };
	//アイテム用の枠
	m_itemSetLog.Init(L"Assets/sprite/ItemSetLog.dds", 400.0f, 100.0f);
	m_itemSLPos = { 470.0f,310.0f,0.0f };
	m_itemSLScale = { 0.85f,0.85f,0.85f };

	//アイテム(炎)	
	m_itemFire.Init(L"Assets/sprite/honoo.dds", 100.0f, 100.0f);
	m_itemFPos = { 600.0f,315.0f,0.0f };
	itemFScale = m_nowSelect;
	//アイテム(木の実)
	m_itemKinomi.Init(L"Assets/sprite/kinomi.dds", 100.0f, 100.0f);
	m_itemKPos = { 520.0f,315.0f,0.0f };
	m_itemKScale = m_nowSelect;
	//アイテム(ランプ)	
	m_itemLight.Init(L"Assets/sprite/light.dds", 100.0f, 100.0f);
	m_itemLPos = { 440.0f,315.0f,0.0f };
	m_itemLScale = m_nowSelect;
	//アイテム(時間停止)	
	m_itemTimeSP.Init(L"Assets/sprite/yimestop.dds", 100.0f, 100.0f);
	m_itemTSPos = { 360.0f,315.0f,0.0f };
	m_itemTSScale = m_nowSelect;
	
}


GameUI::~GameUI()
{

}

void GameUI::ItemSelect()
{
	//あるアイテムの選択
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
	m_SIstate;
}
void GameUI::HPAdd()
{
	//HPの増減で表示を変えます
	HP = GameData::GetInstance()->GetHitPoint();
	if (HP == 1.0f) {

	}
}

void GameUI::Update()
{
	//更新
	ItemSelect();	//アイテム選択

	m_hpHartFrame.Update(m_hpHFPos, CQuaternion::Identity(), m_hpHFScale);
	m_hpHart1.Update(m_hpHPos, CQuaternion::Identity(), m_hpScale);
	m_itemSetLog.Update(m_itemSLPos, CQuaternion::Identity(), m_itemSLScale);
	//アイテム
	m_itemFire.Update(m_itemFPos, CQuaternion::Identity(), itemFScale);
	m_itemKinomi.Update(m_itemKPos, CQuaternion::Identity(), m_itemKScale);
	m_itemLight.Update(m_itemLPos, CQuaternion::Identity(), m_itemLScale);
	m_itemTimeSP.Update(m_itemTSPos, CQuaternion::Identity(), m_itemTSScale);
}
void GameUI::Draw()
{
	//描画処理
	m_hpHartFrame.Draw();
	m_hpHart1.Draw();
	m_itemSetLog.Draw();
	//アイテム
	m_itemFire.Draw();
	m_itemKinomi.Draw();
	m_itemLight.Draw();
	m_itemTimeSP.Draw();
}