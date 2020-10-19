#pragma once
#
class ItemBase : public IActor
{
public:
	enum eState {
		In_Use,
		End_Use
	};

	enum eItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp
	};

	ItemBase();
	~ItemBase();
	void Update() override;

	//void SetItemMove(const eItemState& state);

	eState GetState() {
		return m_state;
	}

	void SetState(const eState& state) {
		m_state = state;
	}

	virtual void InUse() = 0;
	virtual void EndUse() = 0;	
	
private:
	eState m_state = In_Use;		//状態。
protected:
	SpriteRender* m_itemSprite;		//スプライトレンダー。
	int m_number = 0;				//自分の位置番号
	FontRender* m_itemCountFont;

	/////////////////////////////////////////////////////////
	/// 定数
	/////////////////////////////////////////////////////////

	const CVector3 NOW_ITEM_SCALE = { 0.45f, 0.45f ,0.45f };			//選択中アイテムの拡大率
	const CVector3 NEXT1_ITEM_SCALE = { 0.35f,0.35f ,0.35f };			//次1アイテムの拡大率
	const CVector3 NEXT2_ITEM_SCALE = { 0.25f,0.25f ,0.25f };			//次2アイテムの拡大率
	const CVector3 NEXT3_ITEM_SCALE = { 0.15f,0.15f ,0.15f };			//次3アイテムの拡大率

	const CVector3 NOW_ITEM_POSITION = { 460.0f,-240.0f,0.0f };			//選択中アイテムの座標
	const CVector3 NEXT1_ITEM_POSITION = { 560.0f,-120.0f,0.0f };		//次1アイテムの座標
	const CVector3 NEXT2_ITEM_POSITION = { 475.0f,-50.0f,0.0f };		//次2アイテムの座標
	const CVector3 NEXT3_ITEM_POSITION = { 545.0f,-3.0f,0.0f };			//次3アイテムの座標


};

