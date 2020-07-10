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
	//アイテム
	return true;
}
void Item::ItemAppear()
{
	//アイテム出現
}
void Item::ItemGet()
{
	//アイテム獲得。
}
void Item::ItemDestroy()
{
	//アイテム削除。
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
}

