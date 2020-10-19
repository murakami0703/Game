#include "stdafx.h"
#include "ItemBase.h"


ItemBase::ItemBase()
{
}


ItemBase::~ItemBase()
{
}

void ItemBase::Update() 
{
	switch (m_state)
	{
	case In_Use:
		InUse();
		break;
	case End_Use:
		EndUse();
		break;
	}
}
