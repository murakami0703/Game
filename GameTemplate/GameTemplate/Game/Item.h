#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	bool Start();
	void Update();
private:
	//選択状態
	enum eSelectState {
		Item_Use,
		Item_Move,
		Item_Now
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

private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_itemSprite;

	FontRender* m_itemCountFont;
	eSelectState m_state = Item_Now;			//選択状態
	eItemState m_itemState = Item_HpRecovery;			//選択中のアイテム
private:
	//アイテム関連
	CVector3 m_item1Pos = { 460.0f,-240.0f,0.0f };		//アイテム1の座標
	CVector3 m_item2Pos = { 560.0f,-120.0f,0.0f };		//アイテム2の座標
	CVector3 m_item3Pos = { 475.0f,-50.0f,0.0f };		//アイテム3の座標
	CVector3 m_item4Pos = { 545.0f,-3.0f,0.0f };		//アイテム4の座標

	CVector3 m_item1Scale = { 0.55f,0.55f ,0.55f };			//アイテム1の拡大率
	CVector3 m_item2Scale = { 0.35f,0.35f ,0.35f };			//アイテム2の拡大率
	CVector3 m_item3Scale = { 0.25f,0.25f ,0.25f };			//アイテム3の拡大率
	CVector3 m_item4Scale = { 0.15f,0.15f ,0.15f };			//アイテム4の拡大率

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

