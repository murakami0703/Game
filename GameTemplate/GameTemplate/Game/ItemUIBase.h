#pragma once
class ItemUIBase
{
public:
	ItemUIBase();
	~ItemUIBase();

	enum eItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp
	};

	virtual void SetItemMove(const eItemState& state) = 0;	//アイテム移動。
	virtual void ItemUse(eItemState& m_State) = 0;			//アイテム使用。

	void ItemMoveSet(eItemState& m_State);	//アイテムspriteの移動拡大設定。

protected:
	SpriteRender* m_itemSprite;
	FontRender* m_itemCountFont;

	//フォント関連
	CVector2 m_fontMovePos = CVector2().Zero();			//フォントの座標
	wchar_t ItemHpRecText[256];

};

