#pragma once
class ItemUI : public IGameObject
{
public:
	ItemUI();
	~ItemUI();
	bool Start();
	void Update();

	/// <summary>
	/// �㉺�̔���t���O��Ԃ��B
	/// </summary>
	/// <returns></returns>
	bool GetUpDounFlag() const
	{
		return m_upDounFlag;
	}

private:
	//�I�����
	enum eSelectState {
		Item_Use,
		Item_Move,
		Item_Now,
		Item_InUse,
	};
private:
	void ItemNow();		//���ݑI������Ă���A�C�e��
	void ItemInUse();		//���ݑI������Ă���A�C�e��

private:

	eSelectState m_state = Item_Now;			//�I�����

private:

	bool m_itemMoveEndFlag = false;		//�ړ�����
	/// <summary>
	/// �㉺�I���t���O
	/// </summary>
	/// <param name="flag">true   ��     false    ��</param>
	bool m_upDounFlag = true;

};

