#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	bool Start();
	void Update();

	//�A�C�e���̎��
	enum ItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp,
		Item_Num
	};

	//�o���A�C�e���̎w��
	void Item::SetState(ItemState& m_State)
	{
		m_itemState = m_State;
	}
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void Item::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

private:
	//���
	enum EState {
		Item_Appear,
		Item_Get,
		Item_Destroy
	};

private:
	void ItemAppear();	//�A�C�e���o��
	void ItemGet();		//�A�C�e���l���B
	void ItemDestroy();	//�A�C�e���폜�B

private:
	SkinModelRender* m_ItemModelRender;				//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();		//���W�B
	const CVector3 m_Scale = { 5.0f,5.0f,5.0f };	//�g�嗦�B

	EState m_state = Item_Appear;				//��ԁB
	ItemState m_itemState = Item_Num;			//�A�C�e���I���B

};

