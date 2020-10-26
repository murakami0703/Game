#pragma once
class Item : public IActor
{
public:
	Item();
	~Item();

	bool Start();
	void Update();

	
	/// <summary>
	///�O�x�N�g����ݒ�B
	/// </summary>
	void SetFowardVector(CVector3 fowVec)
	{
		m_fowardVector = fowVec;
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
	
	CVector3 m_fowardVector = CVector3().Zero();	//�O�x�N�g���B

	

	EState m_state = Item_Appear;					//��ԁB
	int m_itemNum = 0;								//�A�C�e���w��p�̒l

	int m_timer = 0;								//�^�C�}�[
	const int ITEM_APPEAR_TIME = 300;				//�o�����鎞�ԁB�P��frame�B
};

