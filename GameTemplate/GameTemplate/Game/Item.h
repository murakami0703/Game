#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	bool Start();
	void Update();

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void Item::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	void Item::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	///前ベクトルを設定。
	/// </summary>
	void Item::SetFowardVector(CVector3 fowVec)
	{
		m_fowardVector = fowVec;
	}

	/// <summary>
	/// アイテム使用中か？
	/// </summary>
	/// <param name="flag">false	未使用</param>
	/// <param name="flag">true		使用中</param>
	void Item::SetIsItemUse(bool flag) {
		m_ItemUseFlag = flag;
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
	CVector3 m_fowardVector = CVector3().Zero();	//前ベクトル。

	CQuaternion m_rotation = CQuaternion().Identity();	//回転。

	const CVector3 m_Scale = { 5.0f,5.0f,5.0f };	//拡大率。

	EState m_state = Item_Appear;				//状態。
	int m_itemNum = 0;		//アイテム指定用の値

	int m_timer = 0;	//タイマー
	const int ITEM_APPEAR_TIME = 300;	//タイマー

	bool m_ItemUseFlag = false;		//アイテム使用中フラグ
};

