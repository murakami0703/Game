#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	bool Start();
	void Update();

	//アイテムの種類
	enum ItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp,
		Item_Num
	};

	//出現アイテムの指定
	void Item::SetState(ItemState& m_State)
	{
		m_itemState = m_State;
	}
	/// <summary>
	/// 座標を設定。
	/// </summary>
	void Item::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

private:
	//状態
	enum EState {
		Item_Appear,
		Item_Get,
		Item_Destroy
	};

private:
	void ItemAppear();	//アイテム出現
	void ItemGet();		//アイテム獲得。
	void ItemDestroy();	//アイテム削除。

private:
	SkinModelRender* m_ItemModelRender;				//スキンモデル。
	CVector3 m_position = CVector3().Zero();		//座標。
	const CVector3 m_Scale = { 5.0f,5.0f,5.0f };	//拡大率。

	EState m_state = Item_Appear;				//状態。
	ItemState m_itemState = Item_Num;			//アイテム選択。

};

