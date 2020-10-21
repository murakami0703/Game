#include "stdafx.h"
#include "PlayerHPUI.h"
#include "GameData.h"


/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const float HP_ADD_POSX = 25.0f;						//HP2以上のX座標の加算値
const CVector3 HP_SCALE = { 0.15f,0.15f,0.15f };		//HPの拡大率

PlayerHPUI::PlayerHPUI()
{
}


PlayerHPUI::~PlayerHPUI()
{
}

bool PlayerHPUI::Start()
{
	//0番→HP半分
	m_hpRender = g_goMgr->NewGameObject<SpriteRender>();
	m_hpRender->Init(L"Assets/sprite/Hp_Half.dds", 350.0f, 350.0f);
	m_hpRender->SetAlpha(0.0f);
	m_spriteRender.push_back(m_hpRender);

	//HP
	GameData* m_gamedate = GameData::GetInstance();
	m_nowHP = m_gamedate->GetHitPoint();		//現在のHP。
	m_hpSpriteNum = (int)m_gamedate->GetHitPoint() + 1;		//表示中のHPスプライトの数。

	for (int hp = 0; hp < m_gamedate->GetMAXHitPoint(); hp++) {
		//1番～12番→HP
		m_hpRender = g_goMgr->NewGameObject<SpriteRender>();
		m_hpRender->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
		m_hpPos.x += HP_ADD_POSX;
		//現在のHP分だけ表示させる。
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
	//HPの増減計算処理。
}

void PlayerHPUI::Update()
{
	GameData* m_gamedate = GameData::GetInstance();
	
	//ダメージ受けたとき。



	//回復薬使用。




}
