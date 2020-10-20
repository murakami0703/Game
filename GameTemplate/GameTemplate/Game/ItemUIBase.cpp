#include "stdafx.h"
#include "ItemUIBase.h"


ItemUIBase::ItemUIBase()
{
}


ItemUIBase::~ItemUIBase()
{
}

void ItemUIBase::SetItemMove(const eSelectState& state)
{
	//アイテム移動。
	switch (m_selectState)
	{
	case ItemUIBase::Now_Item_Select:
		NowItemSelect();
		break;
	case ItemUIBase::First_Item_Select:
		FirstItemSelect();
		break;
	case ItemUIBase::Second_Item_Select:
		SecondItemSelect();
		break;
	case ItemUIBase::Third_Item_Select:
		ThirdItemSelect();
	}

}

void ItemUIBase::Update()
{

}
