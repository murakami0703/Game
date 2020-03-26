#include "stdafx.h"
#include "GameUI.h"
#include "GameData.h"

GameUI* GameUI::m_instance = nullptr;

GameUI::GameUI()
{
	m_instance = this;

	//アイテム枠
	{
		//1番→ItemCase1
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case1.dds", 275.0f, 275.0f);
		r->SetPosition(m_itemC1Pos);
		r->SetScale(m_itemC1Scale);
		m_spriteRender.push_back(r);
		//2番→ItemCase2
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case2.dds", 247.0f, 247.0f);
		r->SetPosition(m_itemC2Pos);
		r->SetScale(m_itemC24Scale);
		m_spriteRender.push_back(r);
		//3番→ItemCase3
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case3.dds", 204.0f, 204.0f);
		r->SetPosition(m_itemC3Pos);
		r->SetScale(m_itemC24Scale);
		m_spriteRender.push_back(r);
		//4番→ItemCase4
		r = g_goMgr->NewGameObject<SpriteRender>();
		r->Init(L"Assets/sprite/case4.dds", 148.0f, 148.0f);
		r->SetPosition(m_itemC4Pos);
		r->SetScale(m_itemC24Scale);
		m_spriteRender.push_back(r);
	}
	//HP
	{
		//HPを配置する。
		m_setHP = GameData::GetInstance()->GetHitPoint();
		for (int i = 0; i < m_setHP; i++) {
			if (i >= 1) {
				//6～16番→HP2～12
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				m_hpPos.x += m_hpvAddXPos;
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
			else {
				//5番→HP1
				r = g_goMgr->NewGameObject<SpriteRender>();
				r->Init(L"Assets/sprite/Hp.dds", 350.0f, 350.0f);
				r->SetPosition(m_hpPos);
				r->SetScale(m_hpScale);
				m_spriteRender.push_back(r);
			}
		}
	}
	//ふぉんと
	m_font = g_goMgr->NewGameObject<FontRender>();
	const wchar_t* str = L"「あなただけのデッサン人形」 を作成しポーズを取らせよう！\nデザインドールは3D空間の人体モデルを自在に操るソフトウェアです。\n人物モデルのポーズ集 や 3Dモデルエクスポータ としても\nご利用いただけるソフトウェアです。";
	m_font->SetText(str);
	m_font->SetPosition({ -500.0f,0.0f });

	m_font->SetPivot({ 0.2f,0.2f });
}


GameUI::~GameUI()
{

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
	//HPの増減させるよ
	m_hp = GameData::GetInstance()->GetHitPoint();
	//消えまーすよ
	m_spriteRender[4 + m_hp]->SetAlpha(0.0f);
}

void GameUI::Update()
{
}
void GameUI::Render(){}
void GameUI::PostRender()
{
}