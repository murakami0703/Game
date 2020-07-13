#include "stdafx.h"
#include "Item.h"
#include "GameData.h"

Item::Item()
{
}

Item::~Item()
{
}

bool Item::Start()
{
	m_ItemModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	//出現させるアイテムのcmoファイルの読み込み。
	if (m_itemNum == 0) {
		m_ItemModelRender->Init(L"Assets/modelData/HpRecovery.cmo");

	}
	else if(m_itemNum == 1) {
		m_ItemModelRender->Init(L"Assets/modelData/Bum.cmo");
	}
	else if (m_itemNum == 2) {
		m_ItemModelRender->Init(L"Assets/modelData/AttackUp.cmo");
	}
	else if (m_itemNum == 3) {
		m_ItemModelRender->Init(L"Assets/modelData/SpeedUp.cmo");
	}

	m_ItemModelRender->SetPosition(m_position);	//座標の設定。
	//シャドウキャスターに登録。
	m_ItemModelRender->SetShadowCaster(true);

	return  true;

}
void Item::ItemAppear()
{
	//アイテム出現
	//斜め前に出しますよお
}
void Item::ItemGet()
{
	//アイテム獲得。
	if (m_itemNum == 0) {
		GameData::GetInstance()->HPRecoveryCalc(1);
	}
	else if (m_itemNum == 1) {
		GameData::GetInstance()->BumCalc(1);
	}
	else if (m_itemNum == 2) {
		GameData::GetInstance()->AttackUpCalc(1);
	}
	else if (m_itemNum == 3) {
		GameData::GetInstance()->SpeedUpCalc(1);
	}

	g_goMgr->DeleteGameObject(m_ItemModelRender);
	g_goMgr->DeleteGameObject(this);

}
void Item::ItemDestroy()
{
	//アイテム削除。
	//時間経過のため消滅。
	g_goMgr->DeleteGameObject(m_ItemModelRender);
	g_goMgr->DeleteGameObject(this);

}

void Item::Update()
{
	switch (m_state)
	{
	case Item::Item_Appear:
		ItemAppear();
		break;
	case Item::Item_Get:
		ItemGet();
		break;
	case Item::Item_Destroy:
		ItemDestroy();
		break;
	}

	//ワールド行列の更新。
	m_ItemModelRender->SetPosition(m_position);

}

