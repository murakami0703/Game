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

	/// <summary>
	/// 上下の判定フラグを返す。
	/// </summary>
	/// <returns></returns>
	bool GetUpDounFlag() const
	{
		return m_upDounFlag;
	}

private:
	//選択状態
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
	void ItemNow();		//現在選択されているアイテム
	void ItemInUse();		//現在選択されているアイテム
	void ItemMove();
	void ItemUse(eItemState& m_State);

private:

	eSelectState m_state = Item_Now;					//選択状態
	eItemState m_itemState = Item_HpRecovery;			//アイテムの選択状態

	FontRender* m_itemCountFont;						//アイテム所持数カウント。
	CVector2 m_fontMovePos = CVector2().Zero();			//フォントの座標。

private:
/*	HpRecoveryUI* m_hprecoveryUi;
	BombUI*m_bombUi;
	AttackUpUI*m_attackUpUi;
	SpeedUpUI*m_speedUpUi;
*/
	ItemUIBase* m_uiItems[Item_Num];	//UIアイテム。

	/// <summary>
	/// 上下選択フラグ
	/// </summary>
	/// <param name="flag">true   上     false    下</param>
	bool m_upDounFlag = true;

};

