#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	bool Start();
	void Update();

	//�o���A�C�e���̎w��
	void Item::SetItemNum(int Num)
	{
		//0 �񕜖�A1 ���e�A2 �U����Up�A3 �ړ����xUp
		m_itemNum = Num;
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
	int m_itemNum = 0;		//�A�C�e���w��p�̒l
};

