#pragma once
class Item : public IActor
{
public:
	Item();
	~Item();

	bool Start();
	void Update();

	
	/// <summary>
	///前ベクトルを設定。
	/// </summary>
	void SetFowardVector(CVector3 fowVec)
	{
		m_fowardVector = fowVec;
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
	
	CVector3 m_fowardVector = CVector3().Zero();	//前ベクトル。

	

	EState m_state = Item_Appear;					//状態。
	int m_itemNum = 0;								//アイテム指定用の値

	int m_timer = 0;								//タイマー
	const int ITEM_APPEAR_TIME = 300;				//出現する時間。単位frame。
};

