#pragma once
class ItemManager : public IGameObject
{
	static ItemManager* m_instance;
public:
	ItemManager();
	~ItemManager();

	enum ItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp
	};

	bool Start();
	void Update();	//更新

	void ItemGenerated(ItemState Item, CVector3 position);	//アイテムの生成
	//インスタンスの取得
	static ItemManager* ItemManager::GetInstance() {
		return m_instance;
	}

};

