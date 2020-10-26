#pragma once
#include "ui/itemui/item/HpRecoveryUI.h"
#include "ui/itemui/item/BombUI.h"
#include "ui/itemui/item/AttackUpUI.h"
#include "ui/itemui/item/SpeedUpUI.h"

class ItemUI : public IGameObject
{
public:
	ItemUI();
	~ItemUI();
	bool Start() override;
	void Update() override;

private:

	//�I����ԁB
	enum eSelectState {
		Item_Use,
		Item_Move,
		Item_Now,
		Item_InUse,
	};
	//�A�C�e���B
	enum eItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp,
		Item_Num,
	};

private:
	void ItemUse(const eItemState& m_State);	//�A�C�e���̎g�p�B
	void ItemMove();							//�A�C�e���̈ړ������B
	void ItemNow();								//�I�𒆂̃A�C�e��
	void ItemInUse();							//�A�C�e���̎g�p���̃��O�����B

private:
	ItemUIBase* m_uiItems[Item_Num];	//UI�A�C�e���B

	eSelectState m_state = Item_Move;					//�I����ԁB
	eItemState m_itemState = Item_HpRecovery;			//�A�C�e���̑I���B

	FontRender* m_itemCountFont;						//�A�C�e���������J�E���g�B
	CVector2 m_fontMovePos = CVector2().Zero();			//�t�H���g�̍��W�B
};

