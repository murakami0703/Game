#pragma once
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
private:
	void ItemNow();		//現在選択されているアイテム
	void ItemInUse();		//現在選択されているアイテム

private:

	eSelectState m_state = Item_Now;			//選択状態

private:

	bool m_itemMoveEndFlag = false;		//移動完了
	/// <summary>
	/// 上下選択フラグ
	/// </summary>
	/// <param name="flag">true   上     false    下</param>
	bool m_upDounFlag = true;

};

