#pragma once
#include "HpRecoveryUI.h"
#include "BombUI.h"
#include "AttackUpUI.h"
#include "SpeedUpUI.h"

class ItemUI : public IGameObject
{
public:
	ItemUI();
	~ItemUI();
	bool Start();
	void Update();


private:
	//�I�����
	enum eSelectState {
		Item_Use,
		Item_Move,
		Item_Now,
		Item_InUse,
	};
	enum eItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp,
		Item_Num,
	};

private:
	void ItemNow();		//���ݑI������Ă���A�C�e��
	void ItemInUse();		//���ݑI������Ă���A�C�e��
	void ItemMove();
	void ItemUse(eItemState& m_State);

private:

	eSelectState m_state = Item_Move;					//�I�����
	eItemState m_itemState = Item_HpRecovery;			//�A�C�e���̑I�����

	FontRender* m_itemCountFont;						//�A�C�e���������J�E���g�B
	CVector2 m_fontMovePos = CVector2().Zero();			//�t�H���g�̍��W�B

private:
	ItemUIBase* m_uiItems[Item_Num];	//UI�A�C�e���B
};

