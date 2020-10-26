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

	//選択状態。
	enum eSelectState {
		Item_Use,
		Item_Move,
		Item_Now,
		Item_InUse,
	};
	//アイテム。
	enum eItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp,
		Item_Num,
	};

private:
	void ItemUse(const eItemState& m_State);	//アイテムの使用。
	void ItemMove();							//アイテムの移動処理。
	void ItemNow();								//選択中のアイテム
	void ItemInUse();							//アイテムの使用中のラグ処理。

private:
	ItemUIBase* m_uiItems[Item_Num];	//UIアイテム。

	eSelectState m_state = Item_Move;					//選択状態。
	eItemState m_itemState = Item_HpRecovery;			//アイテムの選択。

	FontRender* m_itemCountFont;						//アイテム所持数カウント。
	CVector2 m_fontMovePos = CVector2().Zero();			//フォントの座標。
};

