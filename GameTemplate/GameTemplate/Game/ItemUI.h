#pragma once
class ItemUI : public IGameObject
{
public:
	ItemUI();
	~ItemUI();
	bool Start();
	void Update();

private:
	//選択状態
	enum eSelectState {
		Item_Use,
		Item_Move,
		Item_Now,
		Item_InUse,
	};
	//アイテムの種類
	enum eItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp
	};

private:
	void ItemMoveSet(eItemState& m_State);	//アイテムspriteの移動拡大設定。

	void ItemUse(eItemState& m_State);		//アイテム使用
	void ItemMove(eItemState& m_State);	//アイテム移動
	void ItemNow();		//現在選択されているアイテム
	void ItemInUse();		//現在選択されているアイテム

private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_itemSprite;

	FontRender* m_itemCountFont;
	eSelectState m_state = Item_Now;			//選択状態
	eItemState m_itemState = Item_HpRecovery;			//選択中のアイテム

private:

	bool m_itemMoveEndFlag = false;		//移動完了
	/// <summary>
	/// 上下選択フラグ
	/// </summary>
	/// <param name="flag">true   上     false    下</param>
	bool m_upDounFlag = true;
	//フォント関連
	CVector2 m_fontMovePos = CVector2().Zero();			//フォントの座標
	wchar_t ItemHpRecText[256];

};

