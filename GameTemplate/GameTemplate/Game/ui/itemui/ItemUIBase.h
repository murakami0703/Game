#pragma once


/// <summary>
/// アイテム用のUIの基底クラス
/// </summary>
/// <remarks>
/// このクラスはTemplateMethodパターンのAbstratClass役のクラスです。
/// </remarks>
class ItemUIBase : public IActor
{
private://派生クラスで実装する必要がある関数群
	virtual void NowItemSelect() = 0;			//選択中のアイテム。
	virtual void FirstItemSelect() = 0;			//次1のアイテム。
	virtual void SecondItemSelect() = 0;		//次2のアイテム。
	virtual void ThirdItemSelect() = 0;			//次3のアイテム。
public:
	virtual void UseItem(FontRender* itemContRender) = 0;		//アイテム使用中。
	virtual void OnNowItem(FontRender* itemContRender) = 0;		//現在のアイテムになったときに呼ばれる処理。
	virtual void ItemUseEnd() = 0;								//アイテム使用後。

public:
	ItemUIBase();
	~ItemUIBase();

	//アイテムの選択
	enum eSelectState {
		Now_Item_Select,
		First_Item_Select,
		Second_Item_Select,
		Third_Item_Select,
		Item_InUse,
	};

	/// <summary>
	/// アイテムの選択状態の取得
	/// </summary>
	eSelectState GetState() {
		return m_selectState;
	}
	/// <summary>
	/// アイテムの選択状態の設定。
	/// </summary>
	void SetState(const eSelectState& state) {
		m_selectState = state;
	}

	void SetItemMove(const eSelectState& state);	//アイテム移動。
	void Update() override;
	

private:
	eSelectState m_selectState = Now_Item_Select;
protected:

	SpriteRender* m_itemSprite;
	//定数
	const CVector3 NOW_ITEM_SCALE = { 0.45f, 0.45f ,0.45f };			//選択中アイテムの拡大率
	const CVector3 NEXT1_ITEM_SCALE = { 0.35f,0.35f ,0.35f };			//次1アイテムの拡大率
	const CVector3 NEXT2_ITEM_SCALE = { 0.25f,0.25f ,0.25f };			//次2アイテムの拡大率
	const CVector3 NEXT3_ITEM_SCALE = { 0.15f,0.15f ,0.15f };			//次3アイテムの拡大率

	const CVector3 NOW_ITEM_POSITION = { 460.0f,-240.0f,0.0f };			//選択中アイテムの座標
	const CVector3 NEXT1_ITEM_POSITION = { 560.0f,-120.0f,0.0f };		//次1アイテムの座標
	const CVector3 NEXT2_ITEM_POSITION = { 475.0f,-50.0f,0.0f };		//次2アイテムの座標
	const CVector3 NEXT3_ITEM_POSITION = { 545.0f,-3.0f,0.0f };			//次3アイテムの座標
};

