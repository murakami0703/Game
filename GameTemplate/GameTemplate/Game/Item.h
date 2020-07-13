#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	bool Start();
	void Update();

	//出現アイテムの指定
	void Item::SetItemNum(int Num)
	{
		//0 回復薬、1 爆弾、2 攻撃力Up、3 移動速度Up
		m_itemNum = Num;
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
	int m_itemNum = 0;		//アイテム指定用の値
};

