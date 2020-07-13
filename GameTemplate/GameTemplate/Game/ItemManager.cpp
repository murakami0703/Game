#include "stdafx.h"
#include "ItemManager.h"
#include "Item.h"

ItemManager* ItemManager::m_instance = nullptr;

ItemManager::ItemManager()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


ItemManager::~ItemManager()
{
}
bool ItemManager::Start(){	return true;}
void ItemManager::Update() {}

void ItemManager::ItemGenerated(ItemState item, CVector3 position)
{
	//�A�C�e���̐���
	Item* m_item = g_goMgr->NewGameObject<Item>();
	//���O�����������Ă���
	m_item->SetItemNum(int(item));
	m_item->SetPosition(position);

}

