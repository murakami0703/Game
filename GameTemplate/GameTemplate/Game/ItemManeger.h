#pragma once
#include "Item.h"
class ItemManeger
{
public:
	ItemManeger();
	~ItemManeger();

	void Update();
	void Draw();

/*	void RegistEnemy(ItemManeger* ite)
	{
		m_items.push_back(ite);
	}
	void DeleteEnemy(ItemManeger* ite)
	{
		auto it = std::find(m_items.begin(), m_items.end(), ite);
		if (it != m_items.end()) {
			m_items.erase(it);
			delete ite;
		}
	}
	static ItemManeger* GetInstance()
	{
		return m_instance;
	}
private:
	static ItemManeger* m_instance;
	std::vector<Item*> m_items;
	*/
};

