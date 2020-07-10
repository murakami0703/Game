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
	void Update();	//�X�V

	void ItemGenerated(ItemState Item, CVector3 position);	//�A�C�e���̐���
	//�C���X�^���X�̎擾
	static ItemManager* ItemManager::GetInstance() {
		return m_instance;
	}

};

