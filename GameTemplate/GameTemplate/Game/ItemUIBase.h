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

	virtual void SetItemMove(const eItemState& state) = 0;	//�A�C�e���ړ��B
	virtual void ItemUse(eItemState& m_State) = 0;			//�A�C�e���g�p�B

	void ItemMoveSet(eItemState& m_State);	//�A�C�e��sprite�̈ړ��g��ݒ�B

protected:
	SpriteRender* m_itemSprite;
	FontRender* m_itemCountFont;

	//�t�H���g�֘A
	CVector2 m_fontMovePos = CVector2().Zero();			//�t�H���g�̍��W
	wchar_t ItemHpRecText[256];

};

