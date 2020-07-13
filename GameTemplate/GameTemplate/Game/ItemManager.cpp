#include "stdafx.h"
#include "ItemManager.h"
#include "Item.h"

ItemManager* ItemManager::m_instance = nullptr;

ItemManager::ItemManager()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


ItemManager::~ItemManager()
{
}
bool ItemManager::Start(){	return true;}
void ItemManager::Update() {}

void ItemManager::ItemGenerated(ItemState item, CVector3 position)
{
	//アイテムの生成
	Item* m_item = g_goMgr->NewGameObject<Item>();
	//名前を引っ張ってくる
	m_item->SetItemNum(int(item));
	m_item->SetPosition(position);

}

