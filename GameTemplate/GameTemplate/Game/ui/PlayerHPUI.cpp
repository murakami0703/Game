#include "stdafx.h"
#include "ui/PlayerHPUI.h"
#include "data/GameData.h"


/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const float HP_ADD_POS_X = 50.0f;					//HP2以上のX座標の加算値。
const CVector3 HP_SCALE = { 0.15f,0.15f,0.15f };	//HPの拡大率。

const float HP_ACTIVE_TRUE = 1.0f;					//透明度(表示)。
const float HP_ACTIVE_FALSE = 0.0f;					//透明度(非表示)。

const float HP_PLUS = 1.0f;							//HPの加算値。
const float HP_MINUS = -1.0f;						//HPの減少値。
const float HP_DECISION = 0.0f;						//HPの判定値。


PlayerHPUI::PlayerHPUI(){}
PlayerHPUI::~PlayerHPUI()
{
	//消す。
	for (int i = 0; i < m_spriteRender.size(); i++) {
		g_goMgr->DeleteGameObject(m_spriteRender[i]);
	}
}

bool PlayerHPUI::Start()
{
	//0番→HP半分。
	m_hpRender = g_goMgr->NewGameObject<SpriteRender>();
	m_hpRender->Init(L"Assets/sprite/Hp_Half.dds", 350.0f, 350.0f);
	m_hpRender->SetAlpha(HP_ACTIVE_FALSE);
	m_spriteRender.push_back(m_hpRender);

	//HP。
	{
		GameData* gamedate = GameData::GetInstance();
		m_nowHP = gamedate->GetHitPoint();					//現在のHP。
		m_hpSpriteNum = (int)gamedate->GetHitPoint();		//表示中のHPスプライトの数。

		for (int hp = 0; hp < gamedate->GetMAXHitPoint(); hp++) {
			//1番～12番→HP。
			m_hpRender = g_goMgr->NewGameObject<SpriteRender>();
			m_hpRender->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
			//現在のHP分だけ表示させる。
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
	//HPの増減計算処理。
	if (damegeValue < HP_DECISION) {
		//ダメージ受けたとき。
		m_spriteRender[m_hpSpriteNum]->SetAlpha(HP_ACTIVE_FALSE);
		m_hpSpriteNum += (int)damegeValue;
		m_nowHP += damegeValue;
	}
	else{
		//回復薬使用したとき。
		m_hpSpriteNum += (int)damegeValue;
		m_spriteRender[m_hpSpriteNum]->SetAlpha(HP_ACTIVE_TRUE);
		m_nowHP += damegeValue;

	}
}

void PlayerHPUI::Update()
{
	GameData* gamedate = GameData::GetInstance();

	//ダメージ受けたとき。
	if (gamedate->GetHitPoint() < m_nowHP) {
		HPCalc(HP_MINUS);
	}
	//回復薬使用。
	if (gamedate->GetHitPoint() > m_nowHP) {
		HPCalc(HP_PLUS);
	}
}
