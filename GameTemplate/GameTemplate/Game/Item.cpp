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
	//�A�C�e��
	return true;
}
void Item::ItemAppear()
{
	//�A�C�e���o��
}
void Item::ItemGet()
{
	//�A�C�e���l���B
}
void Item::ItemDestroy()
{
	//�A�C�e���폜�B
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

	//���[���h�s��̍X�V�B
}

